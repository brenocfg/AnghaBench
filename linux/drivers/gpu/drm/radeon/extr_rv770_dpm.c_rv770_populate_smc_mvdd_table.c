#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rv7xx_power_info {int /*<<< orphan*/  mvdd_mask_low; int /*<<< orphan*/ * mvdd_low_smio; scalar_t__ mvdd_control; } ;
struct radeon_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * lowMask; scalar_t__* highMask; } ;
struct TYPE_5__ {TYPE_1__ voltageMaskTable; int /*<<< orphan*/ * lowSMIO; } ;
typedef  TYPE_2__ RV770_SMC_STATETABLE ;

/* Variables and functions */
 size_t MVDD_HIGH_INDEX ; 
 size_t MVDD_LOW_INDEX ; 
 size_t RV770_SMC_VOLTAGEMASK_MVDD ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 

__attribute__((used)) static int rv770_populate_smc_mvdd_table(struct radeon_device *rdev,
					 RV770_SMC_STATETABLE *table)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);

	if (pi->mvdd_control) {
		table->lowSMIO[MVDD_HIGH_INDEX] |=
			cpu_to_be32(pi->mvdd_low_smio[MVDD_HIGH_INDEX]);
		table->lowSMIO[MVDD_LOW_INDEX] |=
			cpu_to_be32(pi->mvdd_low_smio[MVDD_LOW_INDEX]);

		table->voltageMaskTable.highMask[RV770_SMC_VOLTAGEMASK_MVDD] = 0;
		table->voltageMaskTable.lowMask[RV770_SMC_VOLTAGEMASK_MVDD] =
			cpu_to_be32(pi->mvdd_mask_low);
	}

	return 0;
}