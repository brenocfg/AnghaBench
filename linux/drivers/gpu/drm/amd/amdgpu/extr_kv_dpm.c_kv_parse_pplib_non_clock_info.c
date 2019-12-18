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
typedef  scalar_t__ u8 ;
struct kv_ps {int dummy; } ;
struct amdgpu_ps {int class; void* dclk; void* vclk; void* class2; void* caps; } ;
struct TYPE_3__ {struct amdgpu_ps* uvd_ps; struct amdgpu_ps* boot_ps; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct amdgpu_device {TYPE_2__ pm; } ;
struct _ATOM_PPLIB_NONCLOCK_INFO {int /*<<< orphan*/  ulDCLK; int /*<<< orphan*/  ulVCLK; int /*<<< orphan*/  usClassification2; int /*<<< orphan*/  usClassification; int /*<<< orphan*/  ulCapsAndSettings; } ;

/* Variables and functions */
 int ATOM_PPLIB_CLASSIFICATION_BOOT ; 
 int ATOM_PPLIB_CLASSIFICATION_UVDSTATE ; 
 scalar_t__ ATOM_PPLIB_NONCLOCKINFO_VER1 ; 
 struct kv_ps* kv_get_ps (struct amdgpu_ps*) ; 
 int /*<<< orphan*/  kv_patch_boot_state (struct amdgpu_device*,struct kv_ps*) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kv_parse_pplib_non_clock_info(struct amdgpu_device *adev,
					  struct amdgpu_ps *rps,
					  struct _ATOM_PPLIB_NONCLOCK_INFO *non_clock_info,
					  u8 table_rev)
{
	struct kv_ps *ps = kv_get_ps(rps);

	rps->caps = le32_to_cpu(non_clock_info->ulCapsAndSettings);
	rps->class = le16_to_cpu(non_clock_info->usClassification);
	rps->class2 = le16_to_cpu(non_clock_info->usClassification2);

	if (ATOM_PPLIB_NONCLOCKINFO_VER1 < table_rev) {
		rps->vclk = le32_to_cpu(non_clock_info->ulVCLK);
		rps->dclk = le32_to_cpu(non_clock_info->ulDCLK);
	} else {
		rps->vclk = 0;
		rps->dclk = 0;
	}

	if (rps->class & ATOM_PPLIB_CLASSIFICATION_BOOT) {
		adev->pm.dpm.boot_ps = rps;
		kv_patch_boot_state(adev, ps);
	}
	if (rps->class & ATOM_PPLIB_CLASSIFICATION_UVDSTATE)
		adev->pm.dpm.uvd_ps = rps;
}