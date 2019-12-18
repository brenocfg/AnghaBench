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
typedef  int /*<<< orphan*/  u32 ;
struct dwc3 {scalar_t__ speed; int /*<<< orphan*/  regs; scalar_t__ dis_u2_entry_quirk; } ;
typedef  enum usb_device_state { ____Placeholder_usb_device_state } usb_device_state ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_DCTL ; 
 int /*<<< orphan*/  DWC3_DCTL_INITU2ENA ; 
 scalar_t__ DWC3_DSTS_SUPERSPEED ; 
 scalar_t__ DWC3_DSTS_SUPERSPEED_PLUS ; 
 int EINVAL ; 
 int USB_STATE_CONFIGURED ; 
 int /*<<< orphan*/  dwc3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dwc3_ep0_handle_u2(struct dwc3 *dwc, enum usb_device_state state,
		int set)
{
	u32 reg;


	if (state != USB_STATE_CONFIGURED)
		return -EINVAL;
	if ((dwc->speed != DWC3_DSTS_SUPERSPEED) &&
			(dwc->speed != DWC3_DSTS_SUPERSPEED_PLUS))
		return -EINVAL;
	if (set && dwc->dis_u2_entry_quirk)
		return -EINVAL;

	reg = dwc3_readl(dwc->regs, DWC3_DCTL);
	if (set)
		reg |= DWC3_DCTL_INITU2ENA;
	else
		reg &= ~DWC3_DCTL_INITU2ENA;
	dwc3_writel(dwc->regs, DWC3_DCTL, reg);

	return 0;
}