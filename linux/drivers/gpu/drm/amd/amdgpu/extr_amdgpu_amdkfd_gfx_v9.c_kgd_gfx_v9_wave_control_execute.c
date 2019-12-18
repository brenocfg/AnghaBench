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
typedef  int /*<<< orphan*/  uint32_t ;
struct kgd_dev {int dummy; } ;
struct amdgpu_device {int /*<<< orphan*/  grbm_idx_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  GC ; 
 int /*<<< orphan*/  GRBM_GFX_INDEX ; 
 int /*<<< orphan*/  INSTANCE_BROADCAST_WRITES ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SE_BROADCAST_WRITES ; 
 int /*<<< orphan*/  SH_BROADCAST_WRITES ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15_RLC_SHADOW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct amdgpu_device* get_amdgpu_device (struct kgd_dev*) ; 
 int /*<<< orphan*/  mmGRBM_GFX_INDEX ; 
 int /*<<< orphan*/  mmSQ_CMD ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int kgd_gfx_v9_wave_control_execute(struct kgd_dev *kgd,
					uint32_t gfx_index_val,
					uint32_t sq_cmd)
{
	struct amdgpu_device *adev = get_amdgpu_device(kgd);
	uint32_t data = 0;

	mutex_lock(&adev->grbm_idx_mutex);

	WREG32_SOC15_RLC_SHADOW(GC, 0, mmGRBM_GFX_INDEX, gfx_index_val);
	WREG32(SOC15_REG_OFFSET(GC, 0, mmSQ_CMD), sq_cmd);

	data = REG_SET_FIELD(data, GRBM_GFX_INDEX,
		INSTANCE_BROADCAST_WRITES, 1);
	data = REG_SET_FIELD(data, GRBM_GFX_INDEX,
		SH_BROADCAST_WRITES, 1);
	data = REG_SET_FIELD(data, GRBM_GFX_INDEX,
		SE_BROADCAST_WRITES, 1);

	WREG32_SOC15_RLC_SHADOW(GC, 0, mmGRBM_GFX_INDEX, data);
	mutex_unlock(&adev->grbm_idx_mutex);

	return 0;
}