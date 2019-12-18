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
struct tegra_pmc {TYPE_1__* soc; struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ reset_levels; scalar_t__ reset_sources; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_reset_level ; 
 int /*<<< orphan*/  dev_attr_reset_reason ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 int device_create_file (struct device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tegra_pmc_reset_sysfs_init(struct tegra_pmc *pmc)
{
	struct device *dev = pmc->dev;
	int err = 0;

	if (pmc->soc->reset_sources) {
		err = device_create_file(dev, &dev_attr_reset_reason);
		if (err < 0)
			dev_warn(dev,
				 "failed to create attr \"reset_reason\": %d\n",
				 err);
	}

	if (pmc->soc->reset_levels) {
		err = device_create_file(dev, &dev_attr_reset_level);
		if (err < 0)
			dev_warn(dev,
				 "failed to create attr \"reset_level\": %d\n",
				 err);
	}
}