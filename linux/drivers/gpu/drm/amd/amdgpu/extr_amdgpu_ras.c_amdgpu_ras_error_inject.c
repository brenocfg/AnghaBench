#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ta_ras_trigger_error_input {int /*<<< orphan*/  value; int /*<<< orphan*/  address; int /*<<< orphan*/  sub_block_index; int /*<<< orphan*/  inject_error_type; int /*<<< orphan*/  block_id; } ;
struct ras_manager {int dummy; } ;
struct TYPE_6__ {int block; int /*<<< orphan*/  sub_block_index; int /*<<< orphan*/  type; } ;
struct ras_inject_if {TYPE_3__ head; int /*<<< orphan*/  value; int /*<<< orphan*/  address; } ;
struct TYPE_5__ {TYPE_1__* funcs; } ;
struct amdgpu_device {int /*<<< orphan*/  psp; TYPE_2__ gfx; } ;
struct TYPE_4__ {int (* ras_error_inject ) (struct amdgpu_device*,struct ras_inject_if*) ;} ;

/* Variables and functions */
#define  AMDGPU_RAS_BLOCK__GFX 130 
#define  AMDGPU_RAS_BLOCK__MMHUB 129 
#define  AMDGPU_RAS_BLOCK__UMC 128 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_INFO (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  amdgpu_ras_block_to_ta (int) ; 
 int /*<<< orphan*/  amdgpu_ras_error_to_ta (int /*<<< orphan*/ ) ; 
 struct ras_manager* amdgpu_ras_find_obj (struct amdgpu_device*,TYPE_3__*) ; 
 int psp_ras_trigger_error (int /*<<< orphan*/ *,struct ta_ras_trigger_error_input*) ; 
 int /*<<< orphan*/  ras_block_str (int) ; 
 int stub1 (struct amdgpu_device*,struct ras_inject_if*) ; 

int amdgpu_ras_error_inject(struct amdgpu_device *adev,
		struct ras_inject_if *info)
{
	struct ras_manager *obj = amdgpu_ras_find_obj(adev, &info->head);
	struct ta_ras_trigger_error_input block_info = {
		.block_id =  amdgpu_ras_block_to_ta(info->head.block),
		.inject_error_type = amdgpu_ras_error_to_ta(info->head.type),
		.sub_block_index = info->head.sub_block_index,
		.address = info->address,
		.value = info->value,
	};
	int ret = 0;

	if (!obj)
		return -EINVAL;

	switch (info->head.block) {
	case AMDGPU_RAS_BLOCK__GFX:
		if (adev->gfx.funcs->ras_error_inject)
			ret = adev->gfx.funcs->ras_error_inject(adev, info);
		else
			ret = -EINVAL;
		break;
	case AMDGPU_RAS_BLOCK__UMC:
	case AMDGPU_RAS_BLOCK__MMHUB:
		ret = psp_ras_trigger_error(&adev->psp, &block_info);
		break;
	default:
		DRM_INFO("%s error injection is not supported yet\n",
			 ras_block_str(info->head.block));
		ret = -EINVAL;
	}

	if (ret)
		DRM_ERROR("RAS ERROR: inject %s error failed ret %d\n",
				ras_block_str(info->head.block),
				ret);

	return ret;
}