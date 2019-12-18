#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rv7xx_power_info {int valid_vddc_entries; scalar_t__ max_vddc_in_table; TYPE_2__* vddc_table; int /*<<< orphan*/  vddc_mask_low; } ;
struct radeon_device {int dummy; } ;
struct TYPE_5__ {void** lowMask; scalar_t__* highMask; } ;
struct TYPE_7__ {size_t maxVDDCIndexInPPTable; TYPE_1__ voltageMaskTable; void** lowSMIO; int /*<<< orphan*/ * highSMIO; } ;
struct TYPE_6__ {size_t vddc_index; scalar_t__ vddc; int /*<<< orphan*/  low_smio; int /*<<< orphan*/  high_smio; } ;
typedef  TYPE_3__ RV770_SMC_STATETABLE ;

/* Variables and functions */
 size_t RV770_SMC_VOLTAGEMASK_VDDC ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 

__attribute__((used)) static int rv770_populate_smc_vddc_table(struct radeon_device *rdev,
					 RV770_SMC_STATETABLE *table)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	int i;

	for (i = 0; i < pi->valid_vddc_entries; i++) {
		table->highSMIO[pi->vddc_table[i].vddc_index] =
			pi->vddc_table[i].high_smio;
		table->lowSMIO[pi->vddc_table[i].vddc_index] =
			cpu_to_be32(pi->vddc_table[i].low_smio);
	}

	table->voltageMaskTable.highMask[RV770_SMC_VOLTAGEMASK_VDDC] = 0;
	table->voltageMaskTable.lowMask[RV770_SMC_VOLTAGEMASK_VDDC] =
		cpu_to_be32(pi->vddc_mask_low);

	for (i = 0;
	     ((i < pi->valid_vddc_entries) &&
	      (pi->max_vddc_in_table >
	       pi->vddc_table[i].vddc));
	     i++);

	table->maxVDDCIndexInPPTable =
		pi->vddc_table[i].vddc_index;

	return 0;
}