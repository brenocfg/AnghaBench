#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ta_ras_trigger_error_input {int /*<<< orphan*/  value; int /*<<< orphan*/  address; int /*<<< orphan*/  inject_error_type; int /*<<< orphan*/  sub_block_index; int /*<<< orphan*/  block_id; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {size_t sub_block_index; int type; int /*<<< orphan*/  block; } ;
struct ras_inject_if {int /*<<< orphan*/  value; int /*<<< orphan*/  address; TYPE_1__ head; } ;
struct amdgpu_device {scalar_t__ asic_type; int /*<<< orphan*/  grbm_idx_mutex; int /*<<< orphan*/  psp; } ;
struct TYPE_5__ {int hw_supported_error_type; int sw_supported_error_type; int /*<<< orphan*/  ta_subblock; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_2__*) ; 
 scalar_t__ CHIP_VEGA20 ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  amdgpu_ras_block_to_ta (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ras_error_to_ta (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int psp_ras_trigger_error (int /*<<< orphan*/ *,struct ta_ras_trigger_error_input*) ; 
 TYPE_2__* ras_gfx_subblocks ; 

__attribute__((used)) static int gfx_v9_0_ras_error_inject(struct amdgpu_device *adev,
				     void *inject_if)
{
	struct ras_inject_if *info = (struct ras_inject_if *)inject_if;
	int ret;
	struct ta_ras_trigger_error_input block_info = { 0 };

	if (adev->asic_type != CHIP_VEGA20)
		return -EINVAL;

	if (info->head.sub_block_index >= ARRAY_SIZE(ras_gfx_subblocks))
		return -EINVAL;

	if (!ras_gfx_subblocks[info->head.sub_block_index].name)
		return -EPERM;

	if (!(ras_gfx_subblocks[info->head.sub_block_index].hw_supported_error_type &
	      info->head.type)) {
		DRM_ERROR("GFX Subblock %s, hardware do not support type 0x%x\n",
			ras_gfx_subblocks[info->head.sub_block_index].name,
			info->head.type);
		return -EPERM;
	}

	if (!(ras_gfx_subblocks[info->head.sub_block_index].sw_supported_error_type &
	      info->head.type)) {
		DRM_ERROR("GFX Subblock %s, driver do not support type 0x%x\n",
			ras_gfx_subblocks[info->head.sub_block_index].name,
			info->head.type);
		return -EPERM;
	}

	block_info.block_id = amdgpu_ras_block_to_ta(info->head.block);
	block_info.sub_block_index =
		ras_gfx_subblocks[info->head.sub_block_index].ta_subblock;
	block_info.inject_error_type = amdgpu_ras_error_to_ta(info->head.type);
	block_info.address = info->address;
	block_info.value = info->value;

	mutex_lock(&adev->grbm_idx_mutex);
	ret = psp_ras_trigger_error(&adev->psp, &block_info);
	mutex_unlock(&adev->grbm_idx_mutex);

	return ret;
}