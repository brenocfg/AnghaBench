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
struct device {int dummy; } ;
typedef  void backlight_device ;

/* Variables and functions */

__attribute__((used)) static int devm_backlight_device_match(struct device *dev, void *res,
					void *data)
{
	struct backlight_device **r = res;

	return *r == data;
}