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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ max_shader_engines; scalar_t__ max_sh_per_se; scalar_t__ max_cu_per_sh; } ;
struct amdgpu_cu_info {scalar_t__** bitmap; scalar_t__** ao_cu_bitmap; } ;
struct TYPE_4__ {TYPE_1__ config; struct amdgpu_cu_info cu_info; } ;
struct amdgpu_device {int flags; scalar_t__ asic_type; int /*<<< orphan*/  grbm_idx_mutex; TYPE_2__ gfx; } ;

/* Variables and functions */
 int AMD_IS_APU ; 
 scalar_t__ CHIP_VEGA12 ; 
 int /*<<< orphan*/  GC ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gfx_v9_0_select_se_sh (struct amdgpu_device*,int,int,int) ; 
 int /*<<< orphan*/  mmRLC_LB_ALWAYS_ACTIVE_CU_MASK ; 
 int /*<<< orphan*/  mmRLC_PG_ALWAYS_ON_CU_MASK ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gfx_v9_0_init_always_on_cu_mask(struct amdgpu_device *adev)
{
	struct amdgpu_cu_info *cu_info = &adev->gfx.cu_info;
	uint32_t pg_always_on_cu_num = 2;
	uint32_t always_on_cu_num;
	uint32_t i, j, k;
	uint32_t mask, cu_bitmap, counter;

	if (adev->flags & AMD_IS_APU)
		always_on_cu_num = 4;
	else if (adev->asic_type == CHIP_VEGA12)
		always_on_cu_num = 8;
	else
		always_on_cu_num = 12;

	mutex_lock(&adev->grbm_idx_mutex);
	for (i = 0; i < adev->gfx.config.max_shader_engines; i++) {
		for (j = 0; j < adev->gfx.config.max_sh_per_se; j++) {
			mask = 1;
			cu_bitmap = 0;
			counter = 0;
			gfx_v9_0_select_se_sh(adev, i, j, 0xffffffff);

			for (k = 0; k < adev->gfx.config.max_cu_per_sh; k ++) {
				if (cu_info->bitmap[i][j] & mask) {
					if (counter == pg_always_on_cu_num)
						WREG32_SOC15(GC, 0, mmRLC_PG_ALWAYS_ON_CU_MASK, cu_bitmap);
					if (counter < always_on_cu_num)
						cu_bitmap |= mask;
					else
						break;
					counter++;
				}
				mask <<= 1;
			}

			WREG32_SOC15(GC, 0, mmRLC_LB_ALWAYS_ACTIVE_CU_MASK, cu_bitmap);
			cu_info->ao_cu_bitmap[i][j] = cu_bitmap;
		}
	}
	gfx_v9_0_select_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);
	mutex_unlock(&adev->grbm_idx_mutex);
}