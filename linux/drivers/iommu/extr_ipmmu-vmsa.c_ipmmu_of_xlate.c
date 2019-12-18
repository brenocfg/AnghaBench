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
struct of_phandle_args {int /*<<< orphan*/  args; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  iommu_fwspec_add_ids (struct device*,int /*<<< orphan*/ ,int) ; 
 int ipmmu_init_platform_device (struct device*,struct of_phandle_args*) ; 
 int /*<<< orphan*/  ipmmu_slave_whitelist (struct device*) ; 
 scalar_t__ to_ipmmu (struct device*) ; 

__attribute__((used)) static int ipmmu_of_xlate(struct device *dev,
			  struct of_phandle_args *spec)
{
	if (!ipmmu_slave_whitelist(dev))
		return -ENODEV;

	iommu_fwspec_add_ids(dev, spec->args, 1);

	/* Initialize once - xlate() will call multiple times */
	if (to_ipmmu(dev))
		return 0;

	return ipmmu_init_platform_device(dev, spec);
}