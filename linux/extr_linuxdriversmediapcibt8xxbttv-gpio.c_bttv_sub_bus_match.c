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
struct device_driver {int dummy; } ;
struct device {int dummy; } ;
struct bttv_sub_driver {int /*<<< orphan*/  wanted; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct bttv_sub_driver* to_bttv_sub_drv (struct device_driver*) ; 

__attribute__((used)) static int bttv_sub_bus_match(struct device *dev, struct device_driver *drv)
{
	struct bttv_sub_driver *sub = to_bttv_sub_drv(drv);
	int len = strlen(sub->wanted);

	if (0 == strncmp(dev_name(dev), sub->wanted, len))
		return 1;
	return 0;
}