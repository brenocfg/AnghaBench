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
struct pp_hwmgr {int not_vf; int pm_en; int /*<<< orphan*/ * display_config; int /*<<< orphan*/  feature_mask; int /*<<< orphan*/  chip_id; int /*<<< orphan*/  chip_family; int /*<<< orphan*/  smu_lock; int /*<<< orphan*/  device; struct amdgpu_device* adev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * pp_funcs; struct pp_hwmgr* pp_handle; } ;
struct TYPE_3__ {int /*<<< orphan*/  pm_display_cfg; int /*<<< orphan*/  pp_feature; } ;
struct amdgpu_device {TYPE_2__ powerplay; TYPE_1__ pm; int /*<<< orphan*/  asic_type; int /*<<< orphan*/  family; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  amdgpu_cgs_create_device (struct amdgpu_device*) ; 
 scalar_t__ amdgpu_dpm ; 
 int /*<<< orphan*/  amdgpu_sriov_vf (struct amdgpu_device*) ; 
 struct pp_hwmgr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_dpm_funcs ; 

__attribute__((used)) static int amd_powerplay_create(struct amdgpu_device *adev)
{
	struct pp_hwmgr *hwmgr;

	if (adev == NULL)
		return -EINVAL;

	hwmgr = kzalloc(sizeof(struct pp_hwmgr), GFP_KERNEL);
	if (hwmgr == NULL)
		return -ENOMEM;

	hwmgr->adev = adev;
	hwmgr->not_vf = !amdgpu_sriov_vf(adev);
	hwmgr->pm_en = (amdgpu_dpm && hwmgr->not_vf) ? true : false;
	hwmgr->device = amdgpu_cgs_create_device(adev);
	mutex_init(&hwmgr->smu_lock);
	hwmgr->chip_family = adev->family;
	hwmgr->chip_id = adev->asic_type;
	hwmgr->feature_mask = adev->pm.pp_feature;
	hwmgr->display_config = &adev->pm.pm_display_cfg;
	adev->powerplay.pp_handle = hwmgr;
	adev->powerplay.pp_funcs = &pp_dpm_funcs;
	return 0;
}