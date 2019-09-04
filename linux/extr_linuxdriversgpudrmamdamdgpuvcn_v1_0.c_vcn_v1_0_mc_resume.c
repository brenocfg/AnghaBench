#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_11__ {int gb_addr_config; } ;
struct TYPE_12__ {TYPE_5__ config; } ;
struct TYPE_10__ {int gpu_addr; TYPE_1__* fw; } ;
struct TYPE_9__ {scalar_t__ load_type; TYPE_2__* ucode; } ;
struct amdgpu_device {TYPE_6__ gfx; TYPE_4__ vcn; TYPE_3__ firmware; } ;
struct TYPE_8__ {int tmr_mc_addr_lo; int tmr_mc_addr_hi; } ;
struct TYPE_7__ {scalar_t__ size; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_FW_LOAD_PSP ; 
 int AMDGPU_GPU_PAGE_ALIGN (scalar_t__) ; 
 size_t AMDGPU_UCODE_ID_VCN ; 
 int AMDGPU_UVD_FIRMWARE_OFFSET ; 
 int AMDGPU_VCN_HEAP_SIZE ; 
 int AMDGPU_VCN_SESSION_SIZE ; 
 int AMDGPU_VCN_STACK_SIZE ; 
 int /*<<< orphan*/  UVD ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int lower_32_bits (int) ; 
 int /*<<< orphan*/  mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_HIGH ; 
 int /*<<< orphan*/  mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_LOW ; 
 int /*<<< orphan*/  mmUVD_LMI_VCPU_CACHE2_64BIT_BAR_HIGH ; 
 int /*<<< orphan*/  mmUVD_LMI_VCPU_CACHE2_64BIT_BAR_LOW ; 
 int /*<<< orphan*/  mmUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH ; 
 int /*<<< orphan*/  mmUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW ; 
 int /*<<< orphan*/  mmUVD_UDEC_ADDR_CONFIG ; 
 int /*<<< orphan*/  mmUVD_UDEC_DBW_ADDR_CONFIG ; 
 int /*<<< orphan*/  mmUVD_UDEC_DB_ADDR_CONFIG ; 
 int /*<<< orphan*/  mmUVD_VCPU_CACHE_OFFSET0 ; 
 int /*<<< orphan*/  mmUVD_VCPU_CACHE_OFFSET1 ; 
 int /*<<< orphan*/  mmUVD_VCPU_CACHE_OFFSET2 ; 
 int /*<<< orphan*/  mmUVD_VCPU_CACHE_SIZE0 ; 
 int /*<<< orphan*/  mmUVD_VCPU_CACHE_SIZE1 ; 
 int /*<<< orphan*/  mmUVD_VCPU_CACHE_SIZE2 ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static void vcn_v1_0_mc_resume(struct amdgpu_device *adev)
{
	uint32_t size = AMDGPU_GPU_PAGE_ALIGN(adev->vcn.fw->size + 4);
	uint32_t offset;

	if (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) {
		WREG32_SOC15(UVD, 0, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW,
			     (adev->firmware.ucode[AMDGPU_UCODE_ID_VCN].tmr_mc_addr_lo));
		WREG32_SOC15(UVD, 0, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH,
			     (adev->firmware.ucode[AMDGPU_UCODE_ID_VCN].tmr_mc_addr_hi));
		WREG32_SOC15(UVD, 0, mmUVD_VCPU_CACHE_OFFSET0, 0);
		offset = 0;
	} else {
		WREG32_SOC15(UVD, 0, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW,
			lower_32_bits(adev->vcn.gpu_addr));
		WREG32_SOC15(UVD, 0, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH,
			upper_32_bits(adev->vcn.gpu_addr));
		offset = size;
		WREG32_SOC15(UVD, 0, mmUVD_VCPU_CACHE_OFFSET0,
			     AMDGPU_UVD_FIRMWARE_OFFSET >> 3);
	}

	WREG32_SOC15(UVD, 0, mmUVD_VCPU_CACHE_SIZE0, size);

	WREG32_SOC15(UVD, 0, mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_LOW,
		     lower_32_bits(adev->vcn.gpu_addr + offset));
	WREG32_SOC15(UVD, 0, mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_HIGH,
		     upper_32_bits(adev->vcn.gpu_addr + offset));
	WREG32_SOC15(UVD, 0, mmUVD_VCPU_CACHE_OFFSET1, 0);
	WREG32_SOC15(UVD, 0, mmUVD_VCPU_CACHE_SIZE1, AMDGPU_VCN_HEAP_SIZE);

	WREG32_SOC15(UVD, 0, mmUVD_LMI_VCPU_CACHE2_64BIT_BAR_LOW,
		     lower_32_bits(adev->vcn.gpu_addr + offset + AMDGPU_VCN_HEAP_SIZE));
	WREG32_SOC15(UVD, 0, mmUVD_LMI_VCPU_CACHE2_64BIT_BAR_HIGH,
		     upper_32_bits(adev->vcn.gpu_addr + offset + AMDGPU_VCN_HEAP_SIZE));
	WREG32_SOC15(UVD, 0, mmUVD_VCPU_CACHE_OFFSET2, 0);
	WREG32_SOC15(UVD, 0, mmUVD_VCPU_CACHE_SIZE2,
			AMDGPU_VCN_STACK_SIZE + (AMDGPU_VCN_SESSION_SIZE * 40));

	WREG32_SOC15(UVD, 0, mmUVD_UDEC_ADDR_CONFIG,
			adev->gfx.config.gb_addr_config);
	WREG32_SOC15(UVD, 0, mmUVD_UDEC_DB_ADDR_CONFIG,
			adev->gfx.config.gb_addr_config);
	WREG32_SOC15(UVD, 0, mmUVD_UDEC_DBW_ADDR_CONFIG,
			adev->gfx.config.gb_addr_config);
}