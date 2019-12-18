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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_4__ {int rlc_autoload_gpu_addr; } ;
struct TYPE_5__ {TYPE_1__ rlc; } ;
struct amdgpu_device {TYPE_2__ gfx; } ;
struct TYPE_6__ {int offset; int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 size_t FIRMWARE_ID_RLC_G_UCODE ; 
 int /*<<< orphan*/  GC ; 
 int RLC_CNTL__RLC_ENABLE_F32_MASK ; 
 int RLC_HYP_RESET_VECTOR__COLD_BOOT_EXIT_MASK ; 
 int RLC_HYP_RESET_VECTOR__VDDGFX_EXIT_MASK ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gfx_v10_0_rlc_backdoor_autoload_copy_gfx_ucode (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v10_0_rlc_backdoor_autoload_copy_sdma_ucode (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v10_0_rlc_backdoor_autoload_copy_toc_ucode (struct amdgpu_device*) ; 
 int lower_32_bits (int) ; 
 int /*<<< orphan*/  mmRLC_CNTL ; 
 int /*<<< orphan*/  mmRLC_HYP_BOOTLOAD_ADDR_HI ; 
 int /*<<< orphan*/  mmRLC_HYP_BOOTLOAD_ADDR_LO ; 
 int /*<<< orphan*/  mmRLC_HYP_BOOTLOAD_SIZE ; 
 int /*<<< orphan*/  mmRLC_HYP_RESET_VECTOR ; 
 TYPE_3__* rlc_autoload_info ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static int gfx_v10_0_rlc_backdoor_autoload_enable(struct amdgpu_device *adev)
{
	uint32_t rlc_g_offset, rlc_g_size, tmp;
	uint64_t gpu_addr;

	gfx_v10_0_rlc_backdoor_autoload_copy_toc_ucode(adev);
	gfx_v10_0_rlc_backdoor_autoload_copy_sdma_ucode(adev);
	gfx_v10_0_rlc_backdoor_autoload_copy_gfx_ucode(adev);

	rlc_g_offset = rlc_autoload_info[FIRMWARE_ID_RLC_G_UCODE].offset;
	rlc_g_size = rlc_autoload_info[FIRMWARE_ID_RLC_G_UCODE].size;
	gpu_addr = adev->gfx.rlc.rlc_autoload_gpu_addr + rlc_g_offset;

	WREG32_SOC15(GC, 0, mmRLC_HYP_BOOTLOAD_ADDR_HI, upper_32_bits(gpu_addr));
	WREG32_SOC15(GC, 0, mmRLC_HYP_BOOTLOAD_ADDR_LO, lower_32_bits(gpu_addr));
	WREG32_SOC15(GC, 0, mmRLC_HYP_BOOTLOAD_SIZE, rlc_g_size);

	tmp = RREG32_SOC15(GC, 0, mmRLC_HYP_RESET_VECTOR);
	if (!(tmp & (RLC_HYP_RESET_VECTOR__COLD_BOOT_EXIT_MASK |
		   RLC_HYP_RESET_VECTOR__VDDGFX_EXIT_MASK))) {
		DRM_ERROR("Neither COLD_BOOT_EXIT nor VDDGFX_EXIT is set\n");
		return -EINVAL;
	}

	tmp = RREG32_SOC15(GC, 0, mmRLC_CNTL);
	if (tmp & RLC_CNTL__RLC_ENABLE_F32_MASK) {
		DRM_ERROR("RLC ROM should halt itself\n");
		return -EINVAL;
	}

	return 0;
}