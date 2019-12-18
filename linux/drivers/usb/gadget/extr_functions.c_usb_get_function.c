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
struct usb_function_instance {TYPE_1__* fd; } ;
struct usb_function {struct usb_function_instance* fi; } ;
struct TYPE_2__ {struct usb_function* (* alloc_func ) (struct usb_function_instance*) ;} ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct usb_function*) ; 
 struct usb_function* stub1 (struct usb_function_instance*) ; 

struct usb_function *usb_get_function(struct usb_function_instance *fi)
{
	struct usb_function *f;

	f = fi->fd->alloc_func(fi);
	if (IS_ERR(f))
		return f;
	f->fi = fi;
	return f;
}