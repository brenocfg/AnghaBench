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
struct pp_hwmgr {int /*<<< orphan*/  smu_lock; scalar_t__ pm_en; } ;
struct TYPE_4__ {scalar_t__ smu_prv_buffer_size; } ;
struct TYPE_3__ {struct pp_hwmgr* pp_handle; } ;
struct amdgpu_device {TYPE_2__ pm; TYPE_1__ powerplay; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_PP_TASK_COMPLETE_INIT ; 
 int /*<<< orphan*/  hwmgr_handle_task (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_reserve_vram_for_smu (struct amdgpu_device*) ; 

__attribute__((used)) static int pp_late_init(void *handle)
{
	struct amdgpu_device *adev = handle;
	struct pp_hwmgr *hwmgr = adev->powerplay.pp_handle;

	if (hwmgr && hwmgr->pm_en) {
		mutex_lock(&hwmgr->smu_lock);
		hwmgr_handle_task(hwmgr,
					AMD_PP_TASK_COMPLETE_INIT, NULL);
		mutex_unlock(&hwmgr->smu_lock);
	}
	if (adev->pm.smu_prv_buffer_size != 0)
		pp_reserve_vram_for_smu(adev);

	return 0;
}