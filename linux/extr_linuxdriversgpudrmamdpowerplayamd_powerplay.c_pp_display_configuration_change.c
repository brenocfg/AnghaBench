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
struct pp_hwmgr {int /*<<< orphan*/  smu_lock; int /*<<< orphan*/  pm_en; } ;
struct amd_pp_display_configuration {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phm_store_dal_configuration_data (struct pp_hwmgr*,struct amd_pp_display_configuration const*) ; 

__attribute__((used)) static int pp_display_configuration_change(void *handle,
	const struct amd_pp_display_configuration *display_config)
{
	struct pp_hwmgr *hwmgr = handle;

	if (!hwmgr || !hwmgr->pm_en)
		return -EINVAL;

	mutex_lock(&hwmgr->smu_lock);
	phm_store_dal_configuration_data(hwmgr, display_config);
	mutex_unlock(&hwmgr->smu_lock);
	return 0;
}