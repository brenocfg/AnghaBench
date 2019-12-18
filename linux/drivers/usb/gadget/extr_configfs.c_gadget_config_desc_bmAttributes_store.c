#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_3__ {int bmAttributes; } ;
struct TYPE_4__ {TYPE_1__ c; } ;

/* Variables and functions */
 int EINVAL ; 
 int USB_CONFIG_ATT_ONE ; 
 int USB_CONFIG_ATT_SELFPOWER ; 
 int USB_CONFIG_ATT_WAKEUP ; 
 int kstrtou8 (char const*,int /*<<< orphan*/ ,int*) ; 
 TYPE_2__* to_config_usb_cfg (struct config_item*) ; 

__attribute__((used)) static ssize_t gadget_config_desc_bmAttributes_store(struct config_item *item,
		const char *page, size_t len)
{
	u8 val;
	int ret;
	ret = kstrtou8(page, 0, &val);
	if (ret)
		return ret;
	if (!(val & USB_CONFIG_ATT_ONE))
		return -EINVAL;
	if (val & ~(USB_CONFIG_ATT_ONE | USB_CONFIG_ATT_SELFPOWER |
				USB_CONFIG_ATT_WAKEUP))
		return -EINVAL;
	to_config_usb_cfg(item)->c.bmAttributes = val;
	return len;
}