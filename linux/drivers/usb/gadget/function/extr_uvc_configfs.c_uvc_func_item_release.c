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
struct f_uvc_opts {int /*<<< orphan*/  func_inst; } ;
struct config_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  to_config_group (struct config_item*) ; 
 struct f_uvc_opts* to_f_uvc_opts (struct config_item*) ; 
 int /*<<< orphan*/  usb_put_function_instance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uvcg_config_remove_children (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uvc_func_item_release(struct config_item *item)
{
	struct f_uvc_opts *opts = to_f_uvc_opts(item);

	uvcg_config_remove_children(to_config_group(item));
	usb_put_function_instance(&opts->func_inst);
}