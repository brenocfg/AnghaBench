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
typedef  int u32 ;
struct TYPE_3__ {int max_shader_engines; int max_sh_per_se; int max_cu_per_sh; } ;
struct TYPE_4__ {TYPE_1__ config; } ;
struct amdgpu_device {int /*<<< orphan*/  grbm_idx_mutex; TYPE_2__ gfx; } ;
struct amdgpu_cu_info {int** bitmap; int** ao_cu_bitmap; int number; int ao_cu_mask; int /*<<< orphan*/  simd_per_cu; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NUM_SIMD_PER_CU ; 
 int /*<<< orphan*/  amdgpu_gfx_parse_disable_cu (unsigned int*,int,int) ; 
 int gfx_v9_0_get_cu_active_bitmap (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v9_0_select_se_sh (struct amdgpu_device*,int,int,int) ; 
 int /*<<< orphan*/  gfx_v9_0_set_user_cu_inactive_bitmap (struct amdgpu_device*,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gfx_v9_0_get_cu_info(struct amdgpu_device *adev,
				 struct amdgpu_cu_info *cu_info)
{
	int i, j, k, counter, active_cu_number = 0;
	u32 mask, bitmap, ao_bitmap, ao_cu_mask = 0;
	unsigned disable_masks[4 * 4];

	if (!adev || !cu_info)
		return -EINVAL;

	/*
	 * 16 comes from bitmap array size 4*4, and it can cover all gfx9 ASICs
	 */
	if (adev->gfx.config.max_shader_engines *
		adev->gfx.config.max_sh_per_se > 16)
		return -EINVAL;

	amdgpu_gfx_parse_disable_cu(disable_masks,
				    adev->gfx.config.max_shader_engines,
				    adev->gfx.config.max_sh_per_se);

	mutex_lock(&adev->grbm_idx_mutex);
	for (i = 0; i < adev->gfx.config.max_shader_engines; i++) {
		for (j = 0; j < adev->gfx.config.max_sh_per_se; j++) {
			mask = 1;
			ao_bitmap = 0;
			counter = 0;
			gfx_v9_0_select_se_sh(adev, i, j, 0xffffffff);
			gfx_v9_0_set_user_cu_inactive_bitmap(
				adev, disable_masks[i * adev->gfx.config.max_sh_per_se + j]);
			bitmap = gfx_v9_0_get_cu_active_bitmap(adev);

			/*
			 * The bitmap(and ao_cu_bitmap) in cu_info structure is
			 * 4x4 size array, and it's usually suitable for Vega
			 * ASICs which has 4*2 SE/SH layout.
			 * But for Arcturus, SE/SH layout is changed to 8*1.
			 * To mostly reduce the impact, we make it compatible
			 * with current bitmap array as below:
			 *    SE4,SH0 --> bitmap[0][1]
			 *    SE5,SH0 --> bitmap[1][1]
			 *    SE6,SH0 --> bitmap[2][1]
			 *    SE7,SH0 --> bitmap[3][1]
			 */
			cu_info->bitmap[i % 4][j + i / 4] = bitmap;

			for (k = 0; k < adev->gfx.config.max_cu_per_sh; k ++) {
				if (bitmap & mask) {
					if (counter < adev->gfx.config.max_cu_per_sh)
						ao_bitmap |= mask;
					counter ++;
				}
				mask <<= 1;
			}
			active_cu_number += counter;
			if (i < 2 && j < 2)
				ao_cu_mask |= (ao_bitmap << (i * 16 + j * 8));
			cu_info->ao_cu_bitmap[i % 4][j + i / 4] = ao_bitmap;
		}
	}
	gfx_v9_0_select_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);
	mutex_unlock(&adev->grbm_idx_mutex);

	cu_info->number = active_cu_number;
	cu_info->ao_cu_mask = ao_cu_mask;
	cu_info->simd_per_cu = NUM_SIMD_PER_CU;

	return 0;
}