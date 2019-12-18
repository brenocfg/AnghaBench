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
struct usb_composite_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f_uac1 ; 
 int /*<<< orphan*/  f_uac2 ; 
 int /*<<< orphan*/  fi_uac1 ; 
 int /*<<< orphan*/  fi_uac2 ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** otg_desc ; 
 int /*<<< orphan*/  usb_put_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_function_instance (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int audio_unbind(struct usb_composite_dev *cdev)
{
#ifdef CONFIG_GADGET_UAC1
	if (!IS_ERR_OR_NULL(f_uac1))
		usb_put_function(f_uac1);
	if (!IS_ERR_OR_NULL(fi_uac1))
		usb_put_function_instance(fi_uac1);
#else
	if (!IS_ERR_OR_NULL(f_uac2))
		usb_put_function(f_uac2);
	if (!IS_ERR_OR_NULL(fi_uac2))
		usb_put_function_instance(fi_uac2);
#endif
	kfree(otg_desc[0]);
	otg_desc[0] = NULL;

	return 0;
}