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
struct ttusbir {scalar_t__ led_on; scalar_t__ is_led_on; scalar_t__* bulk_buffer; int /*<<< orphan*/  led_complete; int /*<<< orphan*/  dev; int /*<<< orphan*/  bulk_urb; scalar_t__ udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ atomic_add_unless (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ttusbir_set_led(struct ttusbir *tt)
{
	int ret;

	smp_mb();

	if (tt->led_on != tt->is_led_on && tt->udev &&
				atomic_add_unless(&tt->led_complete, 1, 1)) {
		tt->bulk_buffer[4] = tt->is_led_on = tt->led_on;
		ret = usb_submit_urb(tt->bulk_urb, GFP_ATOMIC);
		if (ret) {
			dev_warn(tt->dev, "failed to submit bulk urb: %d\n",
									ret);
			atomic_dec(&tt->led_complete);
		}
	}
}