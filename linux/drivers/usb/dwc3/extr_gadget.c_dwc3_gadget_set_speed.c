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
struct usb_gadget {int dummy; } ;
struct dwc3 {scalar_t__ revision; int /*<<< orphan*/  lock; int /*<<< orphan*/  regs; int /*<<< orphan*/  dev; int /*<<< orphan*/  dis_metastability_quirk; } ;
typedef  enum usb_device_speed { ____Placeholder_usb_device_speed } usb_device_speed ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_DCFG ; 
 int /*<<< orphan*/  DWC3_DCFG_FULLSPEED ; 
 int /*<<< orphan*/  DWC3_DCFG_HIGHSPEED ; 
 int /*<<< orphan*/  DWC3_DCFG_LOWSPEED ; 
 int /*<<< orphan*/  DWC3_DCFG_SPEED_MASK ; 
 int /*<<< orphan*/  DWC3_DCFG_SUPERSPEED ; 
 int /*<<< orphan*/  DWC3_DCFG_SUPERSPEED_PLUS ; 
 scalar_t__ DWC3_REVISION_220A ; 
 int DWC3_REVISION_IS_DWC31 ; 
#define  USB_SPEED_FULL 132 
#define  USB_SPEED_HIGH 131 
#define  USB_SPEED_LOW 130 
#define  USB_SPEED_SUPER 129 
#define  USB_SPEED_SUPER_PLUS 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dwc3_is_usb31 (struct dwc3*) ; 
 int /*<<< orphan*/  dwc3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dwc3* gadget_to_dwc (struct usb_gadget*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void dwc3_gadget_set_speed(struct usb_gadget *g,
				  enum usb_device_speed speed)
{
	struct dwc3		*dwc = gadget_to_dwc(g);
	unsigned long		flags;
	u32			reg;

	spin_lock_irqsave(&dwc->lock, flags);
	reg = dwc3_readl(dwc->regs, DWC3_DCFG);
	reg &= ~(DWC3_DCFG_SPEED_MASK);

	/*
	 * WORKAROUND: DWC3 revision < 2.20a have an issue
	 * which would cause metastability state on Run/Stop
	 * bit if we try to force the IP to USB2-only mode.
	 *
	 * Because of that, we cannot configure the IP to any
	 * speed other than the SuperSpeed
	 *
	 * Refers to:
	 *
	 * STAR#9000525659: Clock Domain Crossing on DCTL in
	 * USB 2.0 Mode
	 */
	if (dwc->revision < DWC3_REVISION_220A &&
	    !dwc->dis_metastability_quirk) {
		reg |= DWC3_DCFG_SUPERSPEED;
	} else {
		switch (speed) {
		case USB_SPEED_LOW:
			reg |= DWC3_DCFG_LOWSPEED;
			break;
		case USB_SPEED_FULL:
			reg |= DWC3_DCFG_FULLSPEED;
			break;
		case USB_SPEED_HIGH:
			reg |= DWC3_DCFG_HIGHSPEED;
			break;
		case USB_SPEED_SUPER:
			reg |= DWC3_DCFG_SUPERSPEED;
			break;
		case USB_SPEED_SUPER_PLUS:
			if (dwc3_is_usb31(dwc))
				reg |= DWC3_DCFG_SUPERSPEED_PLUS;
			else
				reg |= DWC3_DCFG_SUPERSPEED;
			break;
		default:
			dev_err(dwc->dev, "invalid speed (%d)\n", speed);

			if (dwc->revision & DWC3_REVISION_IS_DWC31)
				reg |= DWC3_DCFG_SUPERSPEED_PLUS;
			else
				reg |= DWC3_DCFG_SUPERSPEED;
		}
	}
	dwc3_writel(dwc->regs, DWC3_DCFG, reg);

	spin_unlock_irqrestore(&dwc->lock, flags);
}