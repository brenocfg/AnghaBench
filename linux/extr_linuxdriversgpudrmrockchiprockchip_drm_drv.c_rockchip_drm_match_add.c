#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_driver {int /*<<< orphan*/  driver; } ;
struct device {int dummy; } ;
struct component_match {int dummy; } ;
struct TYPE_3__ {scalar_t__ match; } ;

/* Variables and functions */
 int /*<<< orphan*/  DL_FLAG_STATELESS ; 
 int /*<<< orphan*/  ENODEV ; 
 struct component_match* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct component_match*) ; 
 struct device* bus_find_device (TYPE_1__*,struct device*,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  compare_dev ; 
 int /*<<< orphan*/  component_match_add (struct device*,struct component_match**,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  device_link_add (struct device*,struct device*,int /*<<< orphan*/ ) ; 
 int num_rockchip_sub_drivers ; 
 TYPE_1__ platform_bus_type ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  rockchip_drm_match_remove (struct device*) ; 
 struct platform_driver** rockchip_sub_drivers ; 

__attribute__((used)) static struct component_match *rockchip_drm_match_add(struct device *dev)
{
	struct component_match *match = NULL;
	int i;

	for (i = 0; i < num_rockchip_sub_drivers; i++) {
		struct platform_driver *drv = rockchip_sub_drivers[i];
		struct device *p = NULL, *d;

		do {
			d = bus_find_device(&platform_bus_type, p, &drv->driver,
					    (void *)platform_bus_type.match);
			put_device(p);
			p = d;

			if (!d)
				break;

			device_link_add(dev, d, DL_FLAG_STATELESS);
			component_match_add(dev, &match, compare_dev, d);
		} while (true);
	}

	if (IS_ERR(match))
		rockchip_drm_match_remove(dev);

	return match ?: ERR_PTR(-ENODEV);
}