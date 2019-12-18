#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint ;
struct device {int dummy; } ;
struct brcmf_sdio_dev {scalar_t__ state; struct brcmf_sdio* bus; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_ctlpkts; int /*<<< orphan*/  tx_ctlerrs; } ;
struct brcmf_sdio {unsigned char* ctrl_frame_buf; int ctrl_frame_stat; int ctrl_frame_err; TYPE_3__ sdcnt; TYPE_2__* sdiodev; int /*<<< orphan*/  ctrl_wait; int /*<<< orphan*/  ctrl_frame_len; } ;
struct TYPE_4__ {struct brcmf_sdio_dev* sdio; } ;
struct brcmf_bus {TYPE_1__ bus_priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  func1; } ;

/* Variables and functions */
 scalar_t__ BRCMF_SDIOD_DATA ; 
 int /*<<< orphan*/  CTL_DONE_TIMEOUT ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SDIO ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  brcmf_sdio_trigger_dpc (struct brcmf_sdio*) ; 
 struct brcmf_bus* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  sdio_claim_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_release_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int
brcmf_sdio_bus_txctl(struct device *dev, unsigned char *msg, uint msglen)
{
	struct brcmf_bus *bus_if = dev_get_drvdata(dev);
	struct brcmf_sdio_dev *sdiodev = bus_if->bus_priv.sdio;
	struct brcmf_sdio *bus = sdiodev->bus;
	int ret;

	brcmf_dbg(TRACE, "Enter\n");
	if (sdiodev->state != BRCMF_SDIOD_DATA)
		return -EIO;

	/* Send from dpc */
	bus->ctrl_frame_buf = msg;
	bus->ctrl_frame_len = msglen;
	wmb();
	bus->ctrl_frame_stat = true;

	brcmf_sdio_trigger_dpc(bus);
	wait_event_interruptible_timeout(bus->ctrl_wait, !bus->ctrl_frame_stat,
					 CTL_DONE_TIMEOUT);
	ret = 0;
	if (bus->ctrl_frame_stat) {
		sdio_claim_host(bus->sdiodev->func1);
		if (bus->ctrl_frame_stat) {
			brcmf_dbg(SDIO, "ctrl_frame timeout\n");
			bus->ctrl_frame_stat = false;
			ret = -ETIMEDOUT;
		}
		sdio_release_host(bus->sdiodev->func1);
	}
	if (!ret) {
		brcmf_dbg(SDIO, "ctrl_frame complete, err=%d\n",
			  bus->ctrl_frame_err);
		rmb();
		ret = bus->ctrl_frame_err;
	}

	if (ret)
		bus->sdcnt.tx_ctlerrs++;
	else
		bus->sdcnt.tx_ctlpkts++;

	return ret;
}