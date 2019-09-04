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
typedef  int u32 ;
typedef  int u16 ;
struct of_phandle_args {int args_count; int /*<<< orphan*/  np; scalar_t__* args; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int SMR_MASK_SHIFT ; 
 int iommu_fwspec_add_ids (struct device*,int*,int) ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 

__attribute__((used)) static int arm_smmu_of_xlate(struct device *dev, struct of_phandle_args *args)
{
	u32 mask, fwid = 0;

	if (args->args_count > 0)
		fwid |= (u16)args->args[0];

	if (args->args_count > 1)
		fwid |= (u16)args->args[1] << SMR_MASK_SHIFT;
	else if (!of_property_read_u32(args->np, "stream-match-mask", &mask))
		fwid |= (u16)mask << SMR_MASK_SHIFT;

	return iommu_fwspec_add_ids(dev, &fwid, 1);
}