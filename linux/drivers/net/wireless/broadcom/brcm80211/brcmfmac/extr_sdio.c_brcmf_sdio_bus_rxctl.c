#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint ;
typedef  int /*<<< orphan*/  u8 ;
struct device {int dummy; } ;
struct brcmf_sdio_dev {scalar_t__ state; struct brcmf_sdio* bus; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_ctlerrs; int /*<<< orphan*/  rx_ctlpkts; } ;
struct brcmf_sdio {TYPE_2__ sdcnt; int /*<<< orphan*/  rxctl_lock; scalar_t__ rxlen; int /*<<< orphan*/ * rxctl_orig; int /*<<< orphan*/ * rxctl; } ;
struct TYPE_3__ {struct brcmf_sdio_dev* sdio; } ;
struct brcmf_bus {TYPE_1__ bus_priv; } ;

/* Variables and functions */
 scalar_t__ BRCMF_SDIOD_DATA ; 
 int /*<<< orphan*/  CTL ; 
 int EIO ; 
 int ERESTARTSYS ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  brcmf_err (char*) ; 
 int /*<<< orphan*/  brcmf_sdio_checkdied (struct brcmf_sdio*) ; 
 int brcmf_sdio_dcmd_resp_wait (struct brcmf_sdio*,scalar_t__*,int*) ; 
 struct brcmf_bus* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
brcmf_sdio_bus_rxctl(struct device *dev, unsigned char *msg, uint msglen)
{
	int timeleft;
	uint rxlen = 0;
	bool pending;
	u8 *buf;
	struct brcmf_bus *bus_if = dev_get_drvdata(dev);
	struct brcmf_sdio_dev *sdiodev = bus_if->bus_priv.sdio;
	struct brcmf_sdio *bus = sdiodev->bus;

	brcmf_dbg(TRACE, "Enter\n");
	if (sdiodev->state != BRCMF_SDIOD_DATA)
		return -EIO;

	/* Wait until control frame is available */
	timeleft = brcmf_sdio_dcmd_resp_wait(bus, &bus->rxlen, &pending);

	spin_lock_bh(&bus->rxctl_lock);
	rxlen = bus->rxlen;
	memcpy(msg, bus->rxctl, min(msglen, rxlen));
	bus->rxctl = NULL;
	buf = bus->rxctl_orig;
	bus->rxctl_orig = NULL;
	bus->rxlen = 0;
	spin_unlock_bh(&bus->rxctl_lock);
	vfree(buf);

	if (rxlen) {
		brcmf_dbg(CTL, "resumed on rxctl frame, got %d expected %d\n",
			  rxlen, msglen);
	} else if (timeleft == 0) {
		brcmf_err("resumed on timeout\n");
		brcmf_sdio_checkdied(bus);
	} else if (pending) {
		brcmf_dbg(CTL, "cancelled\n");
		return -ERESTARTSYS;
	} else {
		brcmf_dbg(CTL, "resumed for unknown reason?\n");
		brcmf_sdio_checkdied(bus);
	}

	if (rxlen)
		bus->sdcnt.rx_ctlpkts++;
	else
		bus->sdcnt.rx_ctlerrs++;

	return rxlen ? (int)rxlen : -ETIMEDOUT;
}