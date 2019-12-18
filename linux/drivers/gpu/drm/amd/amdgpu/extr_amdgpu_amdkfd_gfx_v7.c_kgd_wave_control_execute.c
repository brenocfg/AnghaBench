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
typedef  int uint32_t ;
struct kgd_dev {int dummy; } ;
struct amdgpu_device {int /*<<< orphan*/  grbm_idx_mutex; } ;

/* Variables and functions */
 int GRBM_GFX_INDEX__INSTANCE_BROADCAST_WRITES_MASK ; 
 int GRBM_GFX_INDEX__SE_BROADCAST_WRITES_MASK ; 
 int GRBM_GFX_INDEX__SH_BROADCAST_WRITES_MASK ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 struct amdgpu_device* get_amdgpu_device (struct kgd_dev*) ; 
 int /*<<< orphan*/  mmGRBM_GFX_INDEX ; 
 int /*<<< orphan*/  mmSQ_CMD ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kgd_wave_control_execute(struct kgd_dev *kgd,
					uint32_t gfx_index_val,
					uint32_t sq_cmd)
{
	struct amdgpu_device *adev = get_amdgpu_device(kgd);
	uint32_t data;

	mutex_lock(&adev->grbm_idx_mutex);

	WREG32(mmGRBM_GFX_INDEX, gfx_index_val);
	WREG32(mmSQ_CMD, sq_cmd);

	/*  Restore the GRBM_GFX_INDEX register  */

	data = GRBM_GFX_INDEX__INSTANCE_BROADCAST_WRITES_MASK |
		GRBM_GFX_INDEX__SH_BROADCAST_WRITES_MASK |
		GRBM_GFX_INDEX__SE_BROADCAST_WRITES_MASK;

	WREG32(mmGRBM_GFX_INDEX, data);

	mutex_unlock(&adev->grbm_idx_mutex);

	return 0;
}