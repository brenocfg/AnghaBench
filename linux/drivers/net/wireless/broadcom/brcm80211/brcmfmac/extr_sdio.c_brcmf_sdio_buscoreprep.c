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
typedef  int u8 ;
struct brcmf_sdio_dev {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 int EBUSY ; 
 int /*<<< orphan*/  PMU_MAX_TRANSITION_DLY ; 
 int /*<<< orphan*/  SBSDIO_ALPAV (int) ; 
 int SBSDIO_ALP_AVAIL_REQ ; 
 int SBSDIO_AVBITS ; 
 int SBSDIO_FORCE_ALP ; 
 int SBSDIO_FORCE_HW_CLKREQ_OFF ; 
 int /*<<< orphan*/  SBSDIO_FUNC1_CHIPCLKCSR ; 
 int /*<<< orphan*/  SBSDIO_FUNC1_SDIOPULLUP ; 
 int /*<<< orphan*/  SPINWAIT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_err (char*,...) ; 
 int brcmf_sdiod_readb (struct brcmf_sdio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brcmf_sdiod_writeb (struct brcmf_sdio_dev*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int brcmf_sdio_buscoreprep(void *ctx)
{
	struct brcmf_sdio_dev *sdiodev = ctx;
	int err = 0;
	u8 clkval, clkset;

	/* Try forcing SDIO core to do ALPAvail request only */
	clkset = SBSDIO_FORCE_HW_CLKREQ_OFF | SBSDIO_ALP_AVAIL_REQ;
	brcmf_sdiod_writeb(sdiodev, SBSDIO_FUNC1_CHIPCLKCSR, clkset, &err);
	if (err) {
		brcmf_err("error writing for HT off\n");
		return err;
	}

	/* If register supported, wait for ALPAvail and then force ALP */
	/* This may take up to 15 milliseconds */
	clkval = brcmf_sdiod_readb(sdiodev, SBSDIO_FUNC1_CHIPCLKCSR, NULL);

	if ((clkval & ~SBSDIO_AVBITS) != clkset) {
		brcmf_err("ChipClkCSR access: wrote 0x%02x read 0x%02x\n",
			  clkset, clkval);
		return -EACCES;
	}

	SPINWAIT(((clkval = brcmf_sdiod_readb(sdiodev, SBSDIO_FUNC1_CHIPCLKCSR,
					      NULL)),
		 !SBSDIO_ALPAV(clkval)),
		 PMU_MAX_TRANSITION_DLY);

	if (!SBSDIO_ALPAV(clkval)) {
		brcmf_err("timeout on ALPAV wait, clkval 0x%02x\n",
			  clkval);
		return -EBUSY;
	}

	clkset = SBSDIO_FORCE_HW_CLKREQ_OFF | SBSDIO_FORCE_ALP;
	brcmf_sdiod_writeb(sdiodev, SBSDIO_FUNC1_CHIPCLKCSR, clkset, &err);
	udelay(65);

	/* Also, disable the extra SDIO pull-ups */
	brcmf_sdiod_writeb(sdiodev, SBSDIO_FUNC1_SDIOPULLUP, 0, NULL);

	return 0;
}