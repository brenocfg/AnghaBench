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
struct TYPE_4__ {int ao_cu_mask; } ;
struct TYPE_6__ {int cp_table_gpu_addr; } ;
struct TYPE_5__ {TYPE_1__ cu_info; TYPE_3__ rlc; } ;
struct amdgpu_device {scalar_t__ asic_type; TYPE_2__ gfx; } ;

/* Variables and functions */
 scalar_t__ CHIP_CARRIZO ; 
 scalar_t__ CHIP_POLARIS11 ; 
 scalar_t__ CHIP_POLARIS12 ; 
 scalar_t__ CHIP_STONEY ; 
 scalar_t__ CHIP_VEGAM ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gfx_v8_0_enable_save_restore_machine (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v8_0_init_csb (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v8_0_init_power_gating (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v8_0_init_save_restore_list (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmRLC_JUMP_TABLE_RESTORE ; 
 int /*<<< orphan*/  mmRLC_PG_ALWAYS_ON_CU_MASK ; 

__attribute__((used)) static void gfx_v8_0_init_pg(struct amdgpu_device *adev)
{
	if ((adev->asic_type == CHIP_CARRIZO) ||
	    (adev->asic_type == CHIP_STONEY)) {
		gfx_v8_0_init_csb(adev);
		gfx_v8_0_init_save_restore_list(adev);
		gfx_v8_0_enable_save_restore_machine(adev);
		WREG32(mmRLC_JUMP_TABLE_RESTORE, adev->gfx.rlc.cp_table_gpu_addr >> 8);
		gfx_v8_0_init_power_gating(adev);
		WREG32(mmRLC_PG_ALWAYS_ON_CU_MASK, adev->gfx.cu_info.ao_cu_mask);
	} else if ((adev->asic_type == CHIP_POLARIS11) ||
		   (adev->asic_type == CHIP_POLARIS12) ||
		   (adev->asic_type == CHIP_VEGAM)) {
		gfx_v8_0_init_csb(adev);
		gfx_v8_0_init_save_restore_list(adev);
		gfx_v8_0_enable_save_restore_machine(adev);
		gfx_v8_0_init_power_gating(adev);
	}

}