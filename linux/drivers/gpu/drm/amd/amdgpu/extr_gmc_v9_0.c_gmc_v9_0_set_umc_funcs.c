#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * funcs; int /*<<< orphan*/ * channel_idx_tbl; int /*<<< orphan*/  channel_offs; int /*<<< orphan*/  umc_inst_num; int /*<<< orphan*/  channel_inst_num; int /*<<< orphan*/  max_ras_err_cnt_per_query; } ;
struct amdgpu_device {int asic_type; TYPE_1__ umc; } ;

/* Variables and functions */
#define  CHIP_VEGA20 128 
 int /*<<< orphan*/  UMC_V6_1_CHANNEL_INSTANCE_NUM ; 
 int /*<<< orphan*/  UMC_V6_1_PER_CHANNEL_OFFSET ; 
 int /*<<< orphan*/  UMC_V6_1_TOTAL_CHANNEL_NUM ; 
 int /*<<< orphan*/  UMC_V6_1_UMC_INSTANCE_NUM ; 
 int /*<<< orphan*/ ** umc_v6_1_channel_idx_tbl ; 
 int /*<<< orphan*/  umc_v6_1_funcs ; 

__attribute__((used)) static void gmc_v9_0_set_umc_funcs(struct amdgpu_device *adev)
{
	switch (adev->asic_type) {
	case CHIP_VEGA20:
		adev->umc.max_ras_err_cnt_per_query = UMC_V6_1_TOTAL_CHANNEL_NUM;
		adev->umc.channel_inst_num = UMC_V6_1_CHANNEL_INSTANCE_NUM;
		adev->umc.umc_inst_num = UMC_V6_1_UMC_INSTANCE_NUM;
		adev->umc.channel_offs = UMC_V6_1_PER_CHANNEL_OFFSET;
		adev->umc.channel_idx_tbl = &umc_v6_1_channel_idx_tbl[0][0];
		adev->umc.funcs = &umc_v6_1_funcs;
		break;
	default:
		break;
	}
}