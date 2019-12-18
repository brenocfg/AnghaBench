#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct device {int dummy; } ;
struct brcmf_sdio_dev {scalar_t__ state; int /*<<< orphan*/  func1; int /*<<< orphan*/  func2; struct brcmf_sdio* bus; } ;
struct brcmf_sdio {int rxskip; scalar_t__ rx_seq; scalar_t__ tx_seq; int /*<<< orphan*/  rxctl_lock; scalar_t__ rxlen; int /*<<< orphan*/  glomd; int /*<<< orphan*/  txq; int /*<<< orphan*/  ci; scalar_t__ hostintmask; int /*<<< orphan*/ * watchdog_tsk; struct brcmf_core* sdio_core; } ;
struct brcmf_core {scalar_t__ base; } ;
struct TYPE_2__ {struct brcmf_sdio_dev* sdio; } ;
struct brcmf_bus {TYPE_1__ bus_priv; } ;

/* Variables and functions */
 scalar_t__ BRCMF_SDIOD_NOMEDIUM ; 
 int /*<<< orphan*/  INTR ; 
 int /*<<< orphan*/  SBSDIO_FORCE_HT ; 
 int /*<<< orphan*/  SBSDIO_FUNC1_CHIPCLKCSR ; 
 int /*<<< orphan*/  SBSDIO_HT_AVAIL_REQ ; 
 scalar_t__ SD_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  TRACE ; 
 scalar_t__ brcmf_chip_is_ulp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_err (char*,int) ; 
 int /*<<< orphan*/  brcmf_sdio_bus_sleep (struct brcmf_sdio*,int,int) ; 
 int /*<<< orphan*/  brcmf_sdio_dcmd_resp_wake (struct brcmf_sdio*) ; 
 int /*<<< orphan*/  brcmf_sdio_free_glom (struct brcmf_sdio*) ; 
 int /*<<< orphan*/  brcmf_sdiod_readb (struct brcmf_sdio_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  brcmf_sdiod_writeb (struct brcmf_sdio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  brcmf_sdiod_writel (struct brcmf_sdio_dev*,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brcmu_pkt_buf_free_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmu_pktq_flush (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct brcmf_bus* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  hostintmask ; 
 int /*<<< orphan*/  intstatus ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdio_claim_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_disable_func (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_release_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_sig (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void brcmf_sdio_bus_stop(struct device *dev)
{
	struct brcmf_bus *bus_if = dev_get_drvdata(dev);
	struct brcmf_sdio_dev *sdiodev = bus_if->bus_priv.sdio;
	struct brcmf_sdio *bus = sdiodev->bus;
	struct brcmf_core *core = bus->sdio_core;
	u32 local_hostintmask;
	u8 saveclk, bpreq;
	int err;

	brcmf_dbg(TRACE, "Enter\n");

	if (bus->watchdog_tsk) {
		send_sig(SIGTERM, bus->watchdog_tsk, 1);
		kthread_stop(bus->watchdog_tsk);
		bus->watchdog_tsk = NULL;
	}

	if (sdiodev->state != BRCMF_SDIOD_NOMEDIUM) {
		sdio_claim_host(sdiodev->func1);

		/* Enable clock for device interrupts */
		brcmf_sdio_bus_sleep(bus, false, false);

		/* Disable and clear interrupts at the chip level also */
		brcmf_sdiod_writel(sdiodev, core->base + SD_REG(hostintmask),
				   0, NULL);

		local_hostintmask = bus->hostintmask;
		bus->hostintmask = 0;

		/* Force backplane clocks to assure F2 interrupt propagates */
		saveclk = brcmf_sdiod_readb(sdiodev, SBSDIO_FUNC1_CHIPCLKCSR,
					    &err);
		if (!err) {
			bpreq = saveclk;
			bpreq |= brcmf_chip_is_ulp(bus->ci) ?
				SBSDIO_HT_AVAIL_REQ : SBSDIO_FORCE_HT;
			brcmf_sdiod_writeb(sdiodev,
					   SBSDIO_FUNC1_CHIPCLKCSR,
					   bpreq, &err);
		}
		if (err)
			brcmf_err("Failed to force clock for F2: err %d\n",
				  err);

		/* Turn off the bus (F2), free any pending packets */
		brcmf_dbg(INTR, "disable SDIO interrupts\n");
		sdio_disable_func(sdiodev->func2);

		/* Clear any pending interrupts now that F2 is disabled */
		brcmf_sdiod_writel(sdiodev, core->base + SD_REG(intstatus),
				   local_hostintmask, NULL);

		sdio_release_host(sdiodev->func1);
	}
	/* Clear the data packet queues */
	brcmu_pktq_flush(&bus->txq, true, NULL, NULL);

	/* Clear any held glomming stuff */
	brcmu_pkt_buf_free_skb(bus->glomd);
	brcmf_sdio_free_glom(bus);

	/* Clear rx control and wake any waiters */
	spin_lock_bh(&bus->rxctl_lock);
	bus->rxlen = 0;
	spin_unlock_bh(&bus->rxctl_lock);
	brcmf_sdio_dcmd_resp_wake(bus);

	/* Reset some F2 state stuff */
	bus->rxskip = false;
	bus->tx_seq = bus->rx_seq = 0;
}