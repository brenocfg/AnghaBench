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
struct TYPE_3__ {struct device* controller; } ;
struct TYPE_4__ {TYPE_1__ self; } ;
struct wusbhc {TYPE_2__ usb_hcd; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int sysfs_create_group (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wusbhc_attr_group ; 
 int /*<<< orphan*/  wusbhc_kobj (struct wusbhc*) ; 

int wusbhc_b_create(struct wusbhc *wusbhc)
{
	int result = 0;
	struct device *dev = wusbhc->usb_hcd.self.controller;

	result = sysfs_create_group(wusbhc_kobj(wusbhc), &wusbhc_attr_group);
	if (result < 0) {
		dev_err(dev, "Cannot register WUSBHC attributes: %d\n",
			result);
		goto error_create_attr_group;
	}

	return 0;
error_create_attr_group:
	return result;
}