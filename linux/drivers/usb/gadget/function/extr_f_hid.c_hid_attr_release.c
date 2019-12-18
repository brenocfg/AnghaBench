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
struct f_hid_opts {int /*<<< orphan*/  func_inst; } ;
struct config_item {int dummy; } ;

/* Variables and functions */
 struct f_hid_opts* to_f_hid_opts (struct config_item*) ; 
 int /*<<< orphan*/  usb_put_function_instance (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hid_attr_release(struct config_item *item)
{
	struct f_hid_opts *opts = to_f_hid_opts(item);

	usb_put_function_instance(&opts->func_inst);
}