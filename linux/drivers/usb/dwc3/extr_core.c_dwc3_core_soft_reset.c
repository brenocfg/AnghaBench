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
struct dwc3 {scalar_t__ current_dr_role; scalar_t__ revision; int /*<<< orphan*/  usb2_generic_phy; int /*<<< orphan*/  usb3_generic_phy; int /*<<< orphan*/  regs; int /*<<< orphan*/  usb3_phy; int /*<<< orphan*/  usb2_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_DCTL ; 
 int DWC3_DCTL_CSFTRST ; 
 scalar_t__ DWC3_GCTL_PRTCAP_HOST ; 
 scalar_t__ DWC3_USB31_REVISION_180A ; 
 scalar_t__ DWC3_USB31_REVISION_190A ; 
 int ETIMEDOUT ; 
 scalar_t__ dwc3_is_usb31 (struct dwc3*) ; 
 int dwc3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  phy_exit (int /*<<< orphan*/ ) ; 
 int phy_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usb_phy_init (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dwc3_core_soft_reset(struct dwc3 *dwc)
{
	u32		reg;
	int		retries = 1000;
	int		ret;

	usb_phy_init(dwc->usb2_phy);
	usb_phy_init(dwc->usb3_phy);
	ret = phy_init(dwc->usb2_generic_phy);
	if (ret < 0)
		return ret;

	ret = phy_init(dwc->usb3_generic_phy);
	if (ret < 0) {
		phy_exit(dwc->usb2_generic_phy);
		return ret;
	}

	/*
	 * We're resetting only the device side because, if we're in host mode,
	 * XHCI driver will reset the host block. If dwc3 was configured for
	 * host-only mode, then we can return early.
	 */
	if (dwc->current_dr_role == DWC3_GCTL_PRTCAP_HOST)
		return 0;

	reg = dwc3_readl(dwc->regs, DWC3_DCTL);
	reg |= DWC3_DCTL_CSFTRST;
	dwc3_writel(dwc->regs, DWC3_DCTL, reg);

	/*
	 * For DWC_usb31 controller 1.90a and later, the DCTL.CSFRST bit
	 * is cleared only after all the clocks are synchronized. This can
	 * take a little more than 50ms. Set the polling rate at 20ms
	 * for 10 times instead.
	 */
	if (dwc3_is_usb31(dwc) && dwc->revision >= DWC3_USB31_REVISION_190A)
		retries = 10;

	do {
		reg = dwc3_readl(dwc->regs, DWC3_DCTL);
		if (!(reg & DWC3_DCTL_CSFTRST))
			goto done;

		if (dwc3_is_usb31(dwc) &&
		    dwc->revision >= DWC3_USB31_REVISION_190A)
			msleep(20);
		else
			udelay(1);
	} while (--retries);

	phy_exit(dwc->usb3_generic_phy);
	phy_exit(dwc->usb2_generic_phy);

	return -ETIMEDOUT;

done:
	/*
	 * For DWC_usb31 controller 1.80a and prior, once DCTL.CSFRST bit
	 * is cleared, we must wait at least 50ms before accessing the PHY
	 * domain (synchronization delay).
	 */
	if (dwc3_is_usb31(dwc) && dwc->revision <= DWC3_USB31_REVISION_180A)
		msleep(50);

	return 0;
}