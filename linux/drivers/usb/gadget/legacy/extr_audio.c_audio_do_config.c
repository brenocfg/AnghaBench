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
struct usb_configuration {int /*<<< orphan*/  bmAttributes; int /*<<< orphan*/  descriptors; TYPE_1__* cdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  gadget; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_CONFIG_ATT_WAKEUP ; 
 int /*<<< orphan*/  f_uac1 ; 
 int /*<<< orphan*/  f_uac2 ; 
 int /*<<< orphan*/  fi_uac1 ; 
 int /*<<< orphan*/  fi_uac2 ; 
 scalar_t__ gadget_is_otg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  otg_desc ; 
 int usb_add_function (struct usb_configuration*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_get_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_function (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int audio_do_config(struct usb_configuration *c)
{
	int status;

	/* FIXME alloc iConfiguration string, set it in c->strings */

	if (gadget_is_otg(c->cdev->gadget)) {
		c->descriptors = otg_desc;
		c->bmAttributes |= USB_CONFIG_ATT_WAKEUP;
	}

#ifdef CONFIG_GADGET_UAC1
	f_uac1 = usb_get_function(fi_uac1);
	if (IS_ERR(f_uac1)) {
		status = PTR_ERR(f_uac1);
		return status;
	}

	status = usb_add_function(c, f_uac1);
	if (status < 0) {
		usb_put_function(f_uac1);
		return status;
	}
#else
	f_uac2 = usb_get_function(fi_uac2);
	if (IS_ERR(f_uac2)) {
		status = PTR_ERR(f_uac2);
		return status;
	}

	status = usb_add_function(c, f_uac2);
	if (status < 0) {
		usb_put_function(f_uac2);
		return status;
	}
#endif

	return 0;
}