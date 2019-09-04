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
struct TYPE_4__ {scalar_t__ evclk; scalar_t__ ecclk; } ;
struct TYPE_3__ {scalar_t__ vclk; scalar_t__ dclk; } ;
struct vega10_power_state {int performance_level_count; scalar_t__ sclk_threshold; TYPE_2__ vce_clks; TYPE_1__ uvd_clks; int /*<<< orphan*/ * performance_levels; } ;
struct pp_hwmgr {int dummy; } ;
struct pp_hw_power_state {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct vega10_power_state* cast_const_phw_vega10_power_state (struct pp_hw_power_state const*) ; 
 int /*<<< orphan*/  vega10_are_power_levels_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vega10_check_states_equal(struct pp_hwmgr *hwmgr,
				const struct pp_hw_power_state *pstate1,
			const struct pp_hw_power_state *pstate2, bool *equal)
{
	const struct vega10_power_state *psa;
	const struct vega10_power_state *psb;
	int i;

	if (pstate1 == NULL || pstate2 == NULL || equal == NULL)
		return -EINVAL;

	psa = cast_const_phw_vega10_power_state(pstate1);
	psb = cast_const_phw_vega10_power_state(pstate2);
	/* If the two states don't even have the same number of performance levels they cannot be the same state. */
	if (psa->performance_level_count != psb->performance_level_count) {
		*equal = false;
		return 0;
	}

	for (i = 0; i < psa->performance_level_count; i++) {
		if (!vega10_are_power_levels_equal(&(psa->performance_levels[i]), &(psb->performance_levels[i]))) {
			/* If we have found even one performance level pair that is different the states are different. */
			*equal = false;
			return 0;
		}
	}

	/* If all performance levels are the same try to use the UVD clocks to break the tie.*/
	*equal = ((psa->uvd_clks.vclk == psb->uvd_clks.vclk) && (psa->uvd_clks.dclk == psb->uvd_clks.dclk));
	*equal &= ((psa->vce_clks.evclk == psb->vce_clks.evclk) && (psa->vce_clks.ecclk == psb->vce_clks.ecclk));
	*equal &= (psa->sclk_threshold == psb->sclk_threshold);

	return 0;
}