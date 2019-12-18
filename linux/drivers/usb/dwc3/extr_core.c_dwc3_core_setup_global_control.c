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
typedef  int u32 ;
struct TYPE_2__ {int hwparams4; int hwparams6; int /*<<< orphan*/  hwparams1; } ;
struct dwc3 {scalar_t__ revision; int is_fpga; int /*<<< orphan*/  regs; scalar_t__ u2exit_lfps_quirk; scalar_t__ disable_scramble_quirk; int /*<<< orphan*/  dev; TYPE_1__ hwparams; int /*<<< orphan*/  nr_scratch; int /*<<< orphan*/  dr_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_GCTL ; 
 int DWC3_GCTL_DISSCRAMBLE ; 
 int DWC3_GCTL_DSBLCLKGTNG ; 
 int DWC3_GCTL_GBLHIBERNATIONEN ; 
 int DWC3_GCTL_SCALEDOWN_MASK ; 
 int DWC3_GCTL_SOFITPSYNC ; 
 int DWC3_GCTL_U2EXIT_LFPS ; 
 int DWC3_GCTL_U2RSTECN ; 
 int DWC3_GHWPARAMS1_EN_PWROPT (int /*<<< orphan*/ ) ; 
#define  DWC3_GHWPARAMS1_EN_PWROPT_CLK 129 
#define  DWC3_GHWPARAMS1_EN_PWROPT_HIB 128 
 int /*<<< orphan*/  DWC3_GHWPARAMS4_HIBER_SCRATCHBUFS (int) ; 
 int DWC3_GHWPARAMS6_EN_FPGA ; 
 scalar_t__ DWC3_REVISION_190A ; 
 scalar_t__ DWC3_REVISION_210A ; 
 scalar_t__ DWC3_REVISION_250A ; 
 int /*<<< orphan*/  USB_DR_MODE_HOST ; 
 int /*<<< orphan*/  USB_DR_MODE_OTG ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int dwc3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dwc3_core_setup_global_control(struct dwc3 *dwc)
{
	u32 hwparams4 = dwc->hwparams.hwparams4;
	u32 reg;

	reg = dwc3_readl(dwc->regs, DWC3_GCTL);
	reg &= ~DWC3_GCTL_SCALEDOWN_MASK;

	switch (DWC3_GHWPARAMS1_EN_PWROPT(dwc->hwparams.hwparams1)) {
	case DWC3_GHWPARAMS1_EN_PWROPT_CLK:
		/**
		 * WORKAROUND: DWC3 revisions between 2.10a and 2.50a have an
		 * issue which would cause xHCI compliance tests to fail.
		 *
		 * Because of that we cannot enable clock gating on such
		 * configurations.
		 *
		 * Refers to:
		 *
		 * STAR#9000588375: Clock Gating, SOF Issues when ref_clk-Based
		 * SOF/ITP Mode Used
		 */
		if ((dwc->dr_mode == USB_DR_MODE_HOST ||
				dwc->dr_mode == USB_DR_MODE_OTG) &&
				(dwc->revision >= DWC3_REVISION_210A &&
				dwc->revision <= DWC3_REVISION_250A))
			reg |= DWC3_GCTL_DSBLCLKGTNG | DWC3_GCTL_SOFITPSYNC;
		else
			reg &= ~DWC3_GCTL_DSBLCLKGTNG;
		break;
	case DWC3_GHWPARAMS1_EN_PWROPT_HIB:
		/* enable hibernation here */
		dwc->nr_scratch = DWC3_GHWPARAMS4_HIBER_SCRATCHBUFS(hwparams4);

		/*
		 * REVISIT Enabling this bit so that host-mode hibernation
		 * will work. Device-mode hibernation is not yet implemented.
		 */
		reg |= DWC3_GCTL_GBLHIBERNATIONEN;
		break;
	default:
		/* nothing */
		break;
	}

	/* check if current dwc3 is on simulation board */
	if (dwc->hwparams.hwparams6 & DWC3_GHWPARAMS6_EN_FPGA) {
		dev_info(dwc->dev, "Running with FPGA optimizations\n");
		dwc->is_fpga = true;
	}

	WARN_ONCE(dwc->disable_scramble_quirk && !dwc->is_fpga,
			"disable_scramble cannot be used on non-FPGA builds\n");

	if (dwc->disable_scramble_quirk && dwc->is_fpga)
		reg |= DWC3_GCTL_DISSCRAMBLE;
	else
		reg &= ~DWC3_GCTL_DISSCRAMBLE;

	if (dwc->u2exit_lfps_quirk)
		reg |= DWC3_GCTL_U2EXIT_LFPS;

	/*
	 * WORKAROUND: DWC3 revisions <1.90a have a bug
	 * where the device can fail to connect at SuperSpeed
	 * and falls back to high-speed mode which causes
	 * the device to enter a Connect/Disconnect loop
	 */
	if (dwc->revision < DWC3_REVISION_190A)
		reg |= DWC3_GCTL_U2RSTECN;

	dwc3_writel(dwc->regs, DWC3_GCTL, reg);
}