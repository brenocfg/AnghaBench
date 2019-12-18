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
struct usb_interface {int dummy; } ;
struct ttusbir {int is_led_on; int /*<<< orphan*/  dev; int /*<<< orphan*/ * urb; int /*<<< orphan*/  led; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NUM_URBS ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  led_classdev_resume (int /*<<< orphan*/ *) ; 
 struct ttusbir* usb_get_intfdata (struct usb_interface*) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ttusbir_resume(struct usb_interface *intf)
{
	struct ttusbir *tt = usb_get_intfdata(intf);
	int i, rc;

	tt->is_led_on = true;
	led_classdev_resume(&tt->led);

	for (i = 0; i < NUM_URBS; i++) {
		rc = usb_submit_urb(tt->urb[i], GFP_KERNEL);
		if (rc) {
			dev_warn(tt->dev, "failed to submit urb: %d\n", rc);
			break;
		}
	}

	return rc;
}