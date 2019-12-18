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
 int /*<<< orphan*/  autoresume_timer ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  func_inst_lb ; 
 int /*<<< orphan*/  func_inst_ss ; 
 int /*<<< orphan*/  func_lb ; 
 int /*<<< orphan*/  func_ss ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** otg_desc ; 
 int /*<<< orphan*/  usb_put_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_function_instance (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zero_unbind(struct usb_composite_dev *cdev)
{
	del_timer_sync(&autoresume_timer);
	if (!IS_ERR_OR_NULL(func_ss))
		usb_put_function(func_ss);
	usb_put_function_instance(func_inst_ss);
	if (!IS_ERR_OR_NULL(func_lb))
		usb_put_function(func_lb);
	usb_put_function_instance(func_inst_lb);
	kfree(otg_desc[0]);
	otg_desc[0] = NULL;

	return 0;
}