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
struct usb_function_instance {int /*<<< orphan*/  (* free_func_inst ) (struct usb_function_instance*) ;TYPE_1__* fd; } ;
struct module {int dummy; } ;
struct TYPE_2__ {struct module* mod; } ;

/* Variables and functions */
 int /*<<< orphan*/  module_put (struct module*) ; 
 int /*<<< orphan*/  stub1 (struct usb_function_instance*) ; 

void usb_put_function_instance(struct usb_function_instance *fi)
{
	struct module *mod;

	if (!fi)
		return;

	mod = fi->fd->mod;
	fi->free_func_inst(fi);
	module_put(mod);
}