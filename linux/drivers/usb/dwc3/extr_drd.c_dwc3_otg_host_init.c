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
typedef  int u32 ;
struct dwc3 {int /*<<< orphan*/  regs; int /*<<< orphan*/  dis_u2_susphy_quirk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_GUSB2PHYCFG (int /*<<< orphan*/ ) ; 
 int DWC3_GUSB2PHYCFG_SUSPHY ; 
 int /*<<< orphan*/  DWC3_OCFG ; 
 int DWC3_OCFG_DISPWRCUTTOFF ; 
 int /*<<< orphan*/  DWC3_OCTL ; 
 int DWC3_OCTL_DEVSETHNPEN ; 
 int DWC3_OCTL_HSTSETHNPEN ; 
 int DWC3_OCTL_PERIMODE ; 
 int DWC3_OCTL_PRTPWRCTL ; 
 int DWC3_OCTL_TERMSELIDPULSE ; 
 int dwc3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void dwc3_otg_host_init(struct dwc3 *dwc)
{
	u32 reg;

	/* As per Figure 11-10 A-Device Flow Diagram */
	/* OCFG.HNPCap = 0, OCFG.SRPCap = 0. Already 0 */

	/*
	 * OCTL.PeriMode=0, OCTL.TermSelDLPulse = 0,
	 * OCTL.DevSetHNPEn = 0, OCTL.HstSetHNPEn = 0
	 */
	reg = dwc3_readl(dwc->regs, DWC3_OCTL);
	reg &= ~(DWC3_OCTL_PERIMODE | DWC3_OCTL_TERMSELIDPULSE |
			DWC3_OCTL_DEVSETHNPEN | DWC3_OCTL_HSTSETHNPEN);
	dwc3_writel(dwc->regs, DWC3_OCTL, reg);

	/*
	 * OCFG.DisPrtPwrCutoff = 0/1
	 */
	reg = dwc3_readl(dwc->regs, DWC3_OCFG);
	reg &= ~DWC3_OCFG_DISPWRCUTTOFF;
	dwc3_writel(dwc->regs, DWC3_OCFG, reg);

	/*
	 * OCFG.SRPCap = 1, OCFG.HNPCap = GHWPARAMS6.HNP_CAP
	 * We don't want SRP/HNP for simple dual-role so leave
	 * these disabled.
	 */

	/*
	 * OEVTEN.OTGADevHostEvntEn = 1
	 * OEVTEN.OTGADevSessEndDetEvntEn = 1
	 * We don't want HNP/role-swap so leave these disabled.
	 */

	/* GUSB2PHYCFG.ULPIAutoRes = 1/0, GUSB2PHYCFG.SusPHY = 1 */
	if (!dwc->dis_u2_susphy_quirk) {
		reg = dwc3_readl(dwc->regs, DWC3_GUSB2PHYCFG(0));
		reg |= DWC3_GUSB2PHYCFG_SUSPHY;
		dwc3_writel(dwc->regs, DWC3_GUSB2PHYCFG(0), reg);
	}

	/* Set Port Power to enable VBUS: OCTL.PrtPwrCtl = 1 */
	reg = dwc3_readl(dwc->regs, DWC3_OCTL);
	reg |= DWC3_OCTL_PRTPWRCTL;
	dwc3_writel(dwc->regs, DWC3_OCTL, reg);
}