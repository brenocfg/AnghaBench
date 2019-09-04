#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct si_dte_data {int k; int max_t; int t0; int tdep_count; int* r; int* tdep_r; } ;
struct TYPE_3__ {int tdp_limit; int near_tdp_limit; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct radeon_device {TYPE_2__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int SMC_SISLANDS_DTE_MAX_TEMPERATURE_DEPENDENT_ARRAY_SIZE ; 

__attribute__((used)) static void si_update_dte_from_pl2(struct radeon_device *rdev,
				   struct si_dte_data *dte_data)
{
	u32 p_limit1 = rdev->pm.dpm.tdp_limit;
	u32 p_limit2 = rdev->pm.dpm.near_tdp_limit;
	u32 k = dte_data->k;
	u32 t_max = dte_data->max_t;
	u32 t_split[5] = { 10, 15, 20, 25, 30 };
	u32 t_0 = dte_data->t0;
	u32 i;

	if (p_limit2 != 0 && p_limit2 <= p_limit1) {
		dte_data->tdep_count = 3;

		for (i = 0; i < k; i++) {
			dte_data->r[i] =
				(t_split[i] * (t_max - t_0/(u32)1000) * (1 << 14)) /
				(p_limit2  * (u32)100);
		}

		dte_data->tdep_r[1] = dte_data->r[4] * 2;

		for (i = 2; i < SMC_SISLANDS_DTE_MAX_TEMPERATURE_DEPENDENT_ARRAY_SIZE; i++) {
			dte_data->tdep_r[i] = dte_data->r[4];
		}
	} else {
		DRM_ERROR("Invalid PL2! DTE will not be updated.\n");
	}
}