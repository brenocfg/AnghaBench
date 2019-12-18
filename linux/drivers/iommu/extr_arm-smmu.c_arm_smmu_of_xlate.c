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
typedef  int /*<<< orphan*/  u32 ;
struct of_phandle_args {int args_count; int /*<<< orphan*/  np; int /*<<< orphan*/ * args; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMR_ID ; 
 int /*<<< orphan*/  SMR_MASK ; 
 int iommu_fwspec_add_ids (struct device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int arm_smmu_of_xlate(struct device *dev, struct of_phandle_args *args)
{
	u32 mask, fwid = 0;

	if (args->args_count > 0)
		fwid |= FIELD_PREP(SMR_ID, args->args[0]);

	if (args->args_count > 1)
		fwid |= FIELD_PREP(SMR_MASK, args->args[1]);
	else if (!of_property_read_u32(args->np, "stream-match-mask", &mask))
		fwid |= FIELD_PREP(SMR_MASK, mask);

	return iommu_fwspec_add_ids(dev, &fwid, 1);
}