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
struct usb_composite_dev {int /*<<< orphan*/  gadget; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER () ; 
 int N_CONF ; 
 scalar_t__ can_support_ecm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f_ecm ; 
 int /*<<< orphan*/ ** f_ffs ; 
 int /*<<< orphan*/  f_geth ; 
 int /*<<< orphan*/  f_rndis ; 
 int /*<<< orphan*/  fi_ecm ; 
 int /*<<< orphan*/  fi_geth ; 
 int /*<<< orphan*/  fi_rndis ; 
 int func_num ; 
 int /*<<< orphan*/ ** gfs_otg_desc ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_put_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_function_instance (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gfs_unbind(struct usb_composite_dev *cdev)
{
	int i;

	ENTER();


#ifdef CONFIG_USB_FUNCTIONFS_RNDIS
	usb_put_function(f_rndis);
	usb_put_function_instance(fi_rndis);
#endif

#if defined CONFIG_USB_FUNCTIONFS_ETH
	if (can_support_ecm(cdev->gadget)) {
		usb_put_function(f_ecm);
		usb_put_function_instance(fi_ecm);
	} else {
		usb_put_function(f_geth);
		usb_put_function_instance(fi_geth);
	}
#endif
	for (i = 0; i < N_CONF * func_num; ++i)
		usb_put_function(*(f_ffs[0] + i));

	kfree(gfs_otg_desc[0]);
	gfs_otg_desc[0] = NULL;

	return 0;
}