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
struct pp_hwmgr {unsigned int num_vce_state_tables; struct amd_vce_state* vce_states; int /*<<< orphan*/  pm_en; } ;
struct amd_vce_state {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct amd_vce_state*
pp_dpm_get_vce_clock_state(void *handle, unsigned idx)
{
	struct pp_hwmgr *hwmgr = handle;

	if (!hwmgr || !hwmgr->pm_en)
		return NULL;

	if (idx < hwmgr->num_vce_state_tables)
		return &hwmgr->vce_states[idx];
	return NULL;
}