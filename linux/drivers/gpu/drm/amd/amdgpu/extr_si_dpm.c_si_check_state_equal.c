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
struct si_ps {int performance_level_count; int /*<<< orphan*/ * performance_levels; } ;
struct amdgpu_ps {scalar_t__ vclk; scalar_t__ dclk; scalar_t__ evclk; scalar_t__ ecclk; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  si_are_power_levels_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct si_ps* si_get_ps (struct amdgpu_ps*) ; 

__attribute__((used)) static int si_check_state_equal(void *handle,
				void *current_ps,
				void *request_ps,
				bool *equal)
{
	struct si_ps *si_cps;
	struct si_ps *si_rps;
	int i;
	struct amdgpu_ps *cps = (struct amdgpu_ps *)current_ps;
	struct amdgpu_ps *rps = (struct amdgpu_ps *)request_ps;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	if (adev == NULL || cps == NULL || rps == NULL || equal == NULL)
		return -EINVAL;

	si_cps = si_get_ps((struct amdgpu_ps *)cps);
	si_rps = si_get_ps((struct amdgpu_ps *)rps);

	if (si_cps == NULL) {
		printk("si_cps is NULL\n");
		*equal = false;
		return 0;
	}

	if (si_cps->performance_level_count != si_rps->performance_level_count) {
		*equal = false;
		return 0;
	}

	for (i = 0; i < si_cps->performance_level_count; i++) {
		if (!si_are_power_levels_equal(&(si_cps->performance_levels[i]),
					&(si_rps->performance_levels[i]))) {
			*equal = false;
			return 0;
		}
	}

	/* If all performance levels are the same try to use the UVD clocks to break the tie.*/
	*equal = ((cps->vclk == rps->vclk) && (cps->dclk == rps->dclk));
	*equal &= ((cps->evclk == rps->evclk) && (cps->ecclk == rps->ecclk));

	return 0;
}