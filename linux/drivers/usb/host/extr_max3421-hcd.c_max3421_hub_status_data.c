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
struct TYPE_2__ {int /*<<< orphan*/  controller; } ;
struct usb_hcd {TYPE_1__ self; } ;
struct max3421_hcd {int port_status; scalar_t__ rh_state; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCD_HW_ACCESSIBLE (struct usb_hcd*) ; 
 scalar_t__ MAX3421_RH_SUSPENDED ; 
 int PORT_C_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 struct max3421_hcd* hcd_to_max3421 (struct usb_hcd*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_hcd_resume_root_hub (struct usb_hcd*) ; 

__attribute__((used)) static int
max3421_hub_status_data(struct usb_hcd *hcd, char *buf)
{
	struct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	unsigned long flags;
	int retval = 0;

	spin_lock_irqsave(&max3421_hcd->lock, flags);
	if (!HCD_HW_ACCESSIBLE(hcd))
		goto done;

	*buf = 0;
	if ((max3421_hcd->port_status & PORT_C_MASK) != 0) {
		*buf = (1 << 1); /* a hub over-current condition exists */
		dev_dbg(hcd->self.controller,
			"port status 0x%08x has changes\n",
			max3421_hcd->port_status);
		retval = 1;
		if (max3421_hcd->rh_state == MAX3421_RH_SUSPENDED)
			usb_hcd_resume_root_hub(hcd);
	}
done:
	spin_unlock_irqrestore(&max3421_hcd->lock, flags);
	return retval;
}