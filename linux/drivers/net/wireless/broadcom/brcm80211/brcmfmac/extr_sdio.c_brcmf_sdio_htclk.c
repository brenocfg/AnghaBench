#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct brcmf_sdio {scalar_t__ clkstate; int /*<<< orphan*/  sdiodev; int /*<<< orphan*/  alp_only; scalar_t__ sr_enabled; } ;

/* Variables and functions */
 void* CLK_AVAIL ; 
 scalar_t__ CLK_PENDING ; 
 void* CLK_SDONLY ; 
 int EBADE ; 
 int PMU_MAX_TRANSITION_DLY ; 
 scalar_t__ SBSDIO_ALPONLY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SBSDIO_ALP_AVAIL_REQ ; 
 int /*<<< orphan*/  SBSDIO_CLKAV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SBSDIO_DEVCTL_CA_INT_ONLY ; 
 int /*<<< orphan*/  SBSDIO_DEVICE_CTL ; 
 int /*<<< orphan*/  SBSDIO_FUNC1_CHIPCLKCSR ; 
 int /*<<< orphan*/  SBSDIO_HT_AVAIL_REQ ; 
 int /*<<< orphan*/  SDIO ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_err (char*,...) ; 
 int /*<<< orphan*/  brcmf_sdiod_readb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  brcmf_sdiod_writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int brcmf_sdio_htclk(struct brcmf_sdio *bus, bool on, bool pendok)
{
	int err;
	u8 clkctl, clkreq, devctl;
	unsigned long timeout;

	brcmf_dbg(SDIO, "Enter\n");

	clkctl = 0;

	if (bus->sr_enabled) {
		bus->clkstate = (on ? CLK_AVAIL : CLK_SDONLY);
		return 0;
	}

	if (on) {
		/* Request HT Avail */
		clkreq =
		    bus->alp_only ? SBSDIO_ALP_AVAIL_REQ : SBSDIO_HT_AVAIL_REQ;

		brcmf_sdiod_writeb(bus->sdiodev, SBSDIO_FUNC1_CHIPCLKCSR,
				   clkreq, &err);
		if (err) {
			brcmf_err("HT Avail request error: %d\n", err);
			return -EBADE;
		}

		/* Check current status */
		clkctl = brcmf_sdiod_readb(bus->sdiodev,
					   SBSDIO_FUNC1_CHIPCLKCSR, &err);
		if (err) {
			brcmf_err("HT Avail read error: %d\n", err);
			return -EBADE;
		}

		/* Go to pending and await interrupt if appropriate */
		if (!SBSDIO_CLKAV(clkctl, bus->alp_only) && pendok) {
			/* Allow only clock-available interrupt */
			devctl = brcmf_sdiod_readb(bus->sdiodev,
						   SBSDIO_DEVICE_CTL, &err);
			if (err) {
				brcmf_err("Devctl error setting CA: %d\n", err);
				return -EBADE;
			}

			devctl |= SBSDIO_DEVCTL_CA_INT_ONLY;
			brcmf_sdiod_writeb(bus->sdiodev, SBSDIO_DEVICE_CTL,
					   devctl, &err);
			brcmf_dbg(SDIO, "CLKCTL: set PENDING\n");
			bus->clkstate = CLK_PENDING;

			return 0;
		} else if (bus->clkstate == CLK_PENDING) {
			/* Cancel CA-only interrupt filter */
			devctl = brcmf_sdiod_readb(bus->sdiodev,
						   SBSDIO_DEVICE_CTL, &err);
			devctl &= ~SBSDIO_DEVCTL_CA_INT_ONLY;
			brcmf_sdiod_writeb(bus->sdiodev, SBSDIO_DEVICE_CTL,
					   devctl, &err);
		}

		/* Otherwise, wait here (polling) for HT Avail */
		timeout = jiffies +
			  msecs_to_jiffies(PMU_MAX_TRANSITION_DLY/1000);
		while (!SBSDIO_CLKAV(clkctl, bus->alp_only)) {
			clkctl = brcmf_sdiod_readb(bus->sdiodev,
						   SBSDIO_FUNC1_CHIPCLKCSR,
						   &err);
			if (time_after(jiffies, timeout))
				break;
			else
				usleep_range(5000, 10000);
		}
		if (err) {
			brcmf_err("HT Avail request error: %d\n", err);
			return -EBADE;
		}
		if (!SBSDIO_CLKAV(clkctl, bus->alp_only)) {
			brcmf_err("HT Avail timeout (%d): clkctl 0x%02x\n",
				  PMU_MAX_TRANSITION_DLY, clkctl);
			return -EBADE;
		}

		/* Mark clock available */
		bus->clkstate = CLK_AVAIL;
		brcmf_dbg(SDIO, "CLKCTL: turned ON\n");

#if defined(DEBUG)
		if (!bus->alp_only) {
			if (SBSDIO_ALPONLY(clkctl))
				brcmf_err("HT Clock should be on\n");
		}
#endif				/* defined (DEBUG) */

	} else {
		clkreq = 0;

		if (bus->clkstate == CLK_PENDING) {
			/* Cancel CA-only interrupt filter */
			devctl = brcmf_sdiod_readb(bus->sdiodev,
						   SBSDIO_DEVICE_CTL, &err);
			devctl &= ~SBSDIO_DEVCTL_CA_INT_ONLY;
			brcmf_sdiod_writeb(bus->sdiodev, SBSDIO_DEVICE_CTL,
					   devctl, &err);
		}

		bus->clkstate = CLK_SDONLY;
		brcmf_sdiod_writeb(bus->sdiodev, SBSDIO_FUNC1_CHIPCLKCSR,
				   clkreq, &err);
		brcmf_dbg(SDIO, "CLKCTL: turned OFF\n");
		if (err) {
			brcmf_err("Failed access turning clock off: %d\n",
				  err);
			return -EBADE;
		}
	}
	return 0;
}