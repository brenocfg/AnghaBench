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
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f_acm_cfg1 ; 
 int /*<<< orphan*/  f_acm_cfg2 ; 
 int /*<<< orphan*/  f_ecm_cfg1 ; 
 int /*<<< orphan*/  f_ecm_cfg2 ; 
 int /*<<< orphan*/  f_msg_cfg1 ; 
 int /*<<< orphan*/  f_msg_cfg2 ; 
 int /*<<< orphan*/  f_obex1_cfg1 ; 
 int /*<<< orphan*/  f_obex1_cfg2 ; 
 int /*<<< orphan*/  f_obex2_cfg1 ; 
 int /*<<< orphan*/  f_obex2_cfg2 ; 
 int /*<<< orphan*/  f_phonet_cfg1 ; 
 int /*<<< orphan*/  f_phonet_cfg2 ; 
 int /*<<< orphan*/  fi_acm ; 
 int /*<<< orphan*/  fi_ecm ; 
 int /*<<< orphan*/  fi_msg ; 
 int /*<<< orphan*/  fi_obex1 ; 
 int /*<<< orphan*/  fi_obex2 ; 
 int /*<<< orphan*/  fi_phonet ; 
 int /*<<< orphan*/  usb_put_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_function_instance (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nokia_unbind(struct usb_composite_dev *cdev)
{
	if (!IS_ERR_OR_NULL(f_obex1_cfg2))
		usb_put_function(f_obex1_cfg2);
	if (!IS_ERR_OR_NULL(f_obex2_cfg2))
		usb_put_function(f_obex2_cfg2);
	if (!IS_ERR_OR_NULL(f_obex1_cfg1))
		usb_put_function(f_obex1_cfg1);
	if (!IS_ERR_OR_NULL(f_obex2_cfg1))
		usb_put_function(f_obex2_cfg1);
	if (!IS_ERR_OR_NULL(f_phonet_cfg1))
		usb_put_function(f_phonet_cfg1);
	if (!IS_ERR_OR_NULL(f_phonet_cfg2))
		usb_put_function(f_phonet_cfg2);
	usb_put_function(f_acm_cfg1);
	usb_put_function(f_acm_cfg2);
	usb_put_function(f_ecm_cfg1);
	usb_put_function(f_ecm_cfg2);
	usb_put_function(f_msg_cfg1);
	usb_put_function(f_msg_cfg2);

	usb_put_function_instance(fi_msg);
	usb_put_function_instance(fi_ecm);
	if (!IS_ERR(fi_obex2))
		usb_put_function_instance(fi_obex2);
	if (!IS_ERR(fi_obex1))
		usb_put_function_instance(fi_obex1);
	if (!IS_ERR(fi_phonet))
		usb_put_function_instance(fi_phonet);
	usb_put_function_instance(fi_acm);

	return 0;
}