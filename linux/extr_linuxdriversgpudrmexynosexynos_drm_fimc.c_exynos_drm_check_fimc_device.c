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
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int BIT (int) ; 
 int ENODEV ; 
 int fimc_mask ; 
 int of_alias_get_id (int /*<<< orphan*/ ,char*) ; 

int exynos_drm_check_fimc_device(struct device *dev)
{
	int id = of_alias_get_id(dev->of_node, "fimc");

	if (id >= 0 && (BIT(id) & fimc_mask))
		return 0;
	return -ENODEV;
}