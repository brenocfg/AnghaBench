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
struct usb_os_desc_ext_prop {int data_len; scalar_t__ type; int /*<<< orphan*/  data; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ USB_EXT_PROP_UNICODE ; 
 scalar_t__ USB_EXT_PROP_UNICODE_ENV ; 
 scalar_t__ USB_EXT_PROP_UNICODE_LINK ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 struct usb_os_desc_ext_prop* to_usb_os_desc_ext_prop (struct config_item*) ; 

__attribute__((used)) static ssize_t ext_prop_data_show(struct config_item *item, char *page)
{
	struct usb_os_desc_ext_prop *ext_prop = to_usb_os_desc_ext_prop(item);
	int len = ext_prop->data_len;

	if (ext_prop->type == USB_EXT_PROP_UNICODE ||
	    ext_prop->type == USB_EXT_PROP_UNICODE_ENV ||
	    ext_prop->type == USB_EXT_PROP_UNICODE_LINK)
		len >>= 1;
	memcpy(page, ext_prop->data, len);

	return len;
}