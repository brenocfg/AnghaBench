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
struct wdm_device {scalar_t__ resp_count; int /*<<< orphan*/  flags; TYPE_1__* intf; int /*<<< orphan*/  iuspin; int /*<<< orphan*/  response; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WDM_RESPONDING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int service_outstanding_interrupt(struct wdm_device *desc)
{
	int rv = 0;

	/* submit read urb only if the device is waiting for it */
	if (!desc->resp_count || !--desc->resp_count)
		goto out;

	set_bit(WDM_RESPONDING, &desc->flags);
	spin_unlock_irq(&desc->iuspin);
	rv = usb_submit_urb(desc->response, GFP_KERNEL);
	spin_lock_irq(&desc->iuspin);
	if (rv) {
		dev_err(&desc->intf->dev,
			"usb_submit_urb failed with result %d\n", rv);

		/* make sure the next notification trigger a submit */
		clear_bit(WDM_RESPONDING, &desc->flags);
		desc->resp_count = 0;
	}
out:
	return rv;
}