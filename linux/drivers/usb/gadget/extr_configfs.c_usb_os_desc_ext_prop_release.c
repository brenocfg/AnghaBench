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
struct usb_os_desc_ext_prop {int dummy; } ;
struct config_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct usb_os_desc_ext_prop*) ; 
 struct usb_os_desc_ext_prop* to_usb_os_desc_ext_prop (struct config_item*) ; 

__attribute__((used)) static void usb_os_desc_ext_prop_release(struct config_item *item)
{
	struct usb_os_desc_ext_prop *ext_prop = to_usb_os_desc_ext_prop(item);

	kfree(ext_prop); /* frees a whole chunk */
}