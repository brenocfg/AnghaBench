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
struct kv_ps {int num_levels; int /*<<< orphan*/ * levels; } ;
struct amdgpu_ps {scalar_t__ vclk; scalar_t__ dclk; scalar_t__ evclk; scalar_t__ ecclk; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  kv_are_power_levels_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct kv_ps* kv_get_ps (struct amdgpu_ps*) ; 

__attribute__((used)) static int kv_check_state_equal(void *handle,
				void *current_ps,
				void *request_ps,
				bool *equal)
{
	struct kv_ps *kv_cps;
	struct kv_ps *kv_rps;
	int i;
	struct amdgpu_ps *cps = (struct amdgpu_ps *)current_ps;
	struct amdgpu_ps *rps = (struct amdgpu_ps *)request_ps;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	if (adev == NULL || cps == NULL || rps == NULL || equal == NULL)
		return -EINVAL;

	kv_cps = kv_get_ps(cps);
	kv_rps = kv_get_ps(rps);

	if (kv_cps == NULL) {
		*equal = false;
		return 0;
	}

	if (kv_cps->num_levels != kv_rps->num_levels) {
		*equal = false;
		return 0;
	}

	for (i = 0; i < kv_cps->num_levels; i++) {
		if (!kv_are_power_levels_equal(&(kv_cps->levels[i]),
					&(kv_rps->levels[i]))) {
			*equal = false;
			return 0;
		}
	}

	/* If all performance levels are the same try to use the UVD clocks to break the tie.*/
	*equal = ((cps->vclk == rps->vclk) && (cps->dclk == rps->dclk));
	*equal &= ((cps->evclk == rps->evclk) && (cps->ecclk == rps->ecclk));

	return 0;
}