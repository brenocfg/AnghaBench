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
struct kgd_dev {int dummy; } ;
struct kfd_cu_info {int /*<<< orphan*/  lds_size; int /*<<< orphan*/  max_scratch_slots_per_cu; int /*<<< orphan*/  wave_front_size; int /*<<< orphan*/  max_waves_per_simd; int /*<<< orphan*/  simd_per_cu; int /*<<< orphan*/  num_cu_per_sh; int /*<<< orphan*/  num_shader_arrays_per_engine; int /*<<< orphan*/  num_shader_engines; int /*<<< orphan*/ * cu_bitmap; int /*<<< orphan*/  cu_ao_mask; int /*<<< orphan*/  cu_active_number; } ;
struct TYPE_3__ {int /*<<< orphan*/  max_cu_per_sh; int /*<<< orphan*/  max_sh_per_se; int /*<<< orphan*/  max_shader_engines; } ;
struct amdgpu_cu_info {int /*<<< orphan*/  lds_size; int /*<<< orphan*/  max_scratch_slots_per_cu; int /*<<< orphan*/  wave_front_size; int /*<<< orphan*/  max_waves_per_simd; int /*<<< orphan*/  simd_per_cu; int /*<<< orphan*/ * bitmap; int /*<<< orphan*/  ao_cu_mask; int /*<<< orphan*/  number; } ;
struct TYPE_4__ {TYPE_1__ config; struct amdgpu_cu_info cu_info; } ;
struct amdgpu_device {TYPE_2__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct kfd_cu_info*,int /*<<< orphan*/ ,int) ; 

void amdgpu_amdkfd_get_cu_info(struct kgd_dev *kgd, struct kfd_cu_info *cu_info)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)kgd;
	struct amdgpu_cu_info acu_info = adev->gfx.cu_info;

	memset(cu_info, 0, sizeof(*cu_info));
	if (sizeof(cu_info->cu_bitmap) != sizeof(acu_info.bitmap))
		return;

	cu_info->cu_active_number = acu_info.number;
	cu_info->cu_ao_mask = acu_info.ao_cu_mask;
	memcpy(&cu_info->cu_bitmap[0], &acu_info.bitmap[0],
	       sizeof(acu_info.bitmap));
	cu_info->num_shader_engines = adev->gfx.config.max_shader_engines;
	cu_info->num_shader_arrays_per_engine = adev->gfx.config.max_sh_per_se;
	cu_info->num_cu_per_sh = adev->gfx.config.max_cu_per_sh;
	cu_info->simd_per_cu = acu_info.simd_per_cu;
	cu_info->max_waves_per_simd = acu_info.max_waves_per_simd;
	cu_info->wave_front_size = acu_info.wave_front_size;
	cu_info->max_scratch_slots_per_cu = acu_info.max_scratch_slots_per_cu;
	cu_info->lds_size = acu_info.lds_size;
}