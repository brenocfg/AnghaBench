#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_13__ {int gb_addr_config; } ;
struct TYPE_14__ {TYPE_6__ config; } ;
struct TYPE_12__ {TYPE_4__* inst; TYPE_1__* fw; } ;
struct TYPE_10__ {scalar_t__ load_type; TYPE_2__* ucode; } ;
struct amdgpu_device {TYPE_7__ gfx; TYPE_5__ vcn; TYPE_3__ firmware; } ;
struct TYPE_11__ {int gpu_addr; } ;
struct TYPE_9__ {int tmr_mc_addr_lo; int tmr_mc_addr_hi; } ;
struct TYPE_8__ {scalar_t__ size; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_FW_LOAD_PSP ; 
 int AMDGPU_GPU_PAGE_ALIGN (scalar_t__) ; 
 size_t AMDGPU_UCODE_ID_VCN ; 
 int AMDGPU_UVD_FIRMWARE_OFFSET ; 
 int AMDGPU_VCN_CONTEXT_SIZE ; 
 int AMDGPU_VCN_STACK_SIZE ; 
 int /*<<< orphan*/  SOC15_DPG_MODE_OFFSET_2_0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UVD ; 
 int /*<<< orphan*/  WREG32_SOC15_DPG_MODE_2_0 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int lower_32_bits (int) ; 
 int /*<<< orphan*/  mmUVD_GFX10_ADDR_CONFIG ; 
 int /*<<< orphan*/  mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_HIGH ; 
 int /*<<< orphan*/  mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_LOW ; 
 int /*<<< orphan*/  mmUVD_LMI_VCPU_CACHE2_64BIT_BAR_HIGH ; 
 int /*<<< orphan*/  mmUVD_LMI_VCPU_CACHE2_64BIT_BAR_LOW ; 
 int /*<<< orphan*/  mmUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH ; 
 int /*<<< orphan*/  mmUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW ; 
 int /*<<< orphan*/  mmUVD_LMI_VCPU_NC0_64BIT_BAR_HIGH ; 
 int /*<<< orphan*/  mmUVD_LMI_VCPU_NC0_64BIT_BAR_LOW ; 
 int /*<<< orphan*/  mmUVD_VCPU_CACHE_OFFSET0 ; 
 int /*<<< orphan*/  mmUVD_VCPU_CACHE_OFFSET1 ; 
 int /*<<< orphan*/  mmUVD_VCPU_CACHE_OFFSET2 ; 
 int /*<<< orphan*/  mmUVD_VCPU_CACHE_SIZE0 ; 
 int /*<<< orphan*/  mmUVD_VCPU_CACHE_SIZE1 ; 
 int /*<<< orphan*/  mmUVD_VCPU_CACHE_SIZE2 ; 
 int /*<<< orphan*/  mmUVD_VCPU_NONCACHE_OFFSET0 ; 
 int /*<<< orphan*/  mmUVD_VCPU_NONCACHE_SIZE0 ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static void vcn_v2_0_mc_resume_dpg_mode(struct amdgpu_device *adev, bool indirect)
{
	uint32_t size = AMDGPU_GPU_PAGE_ALIGN(adev->vcn.fw->size + 4);
	uint32_t offset;

	/* cache window 0: fw */
	if (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) {
		if (!indirect) {
			WREG32_SOC15_DPG_MODE_2_0(SOC15_DPG_MODE_OFFSET_2_0(
				UVD, 0, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW),
				(adev->firmware.ucode[AMDGPU_UCODE_ID_VCN].tmr_mc_addr_lo), 0, indirect);
			WREG32_SOC15_DPG_MODE_2_0(SOC15_DPG_MODE_OFFSET_2_0(
				UVD, 0, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH),
				(adev->firmware.ucode[AMDGPU_UCODE_ID_VCN].tmr_mc_addr_hi), 0, indirect);
			WREG32_SOC15_DPG_MODE_2_0(SOC15_DPG_MODE_OFFSET_2_0(
				UVD, 0, mmUVD_VCPU_CACHE_OFFSET0), 0, 0, indirect);
		} else {
			WREG32_SOC15_DPG_MODE_2_0(SOC15_DPG_MODE_OFFSET_2_0(
				UVD, 0, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW), 0, 0, indirect);
			WREG32_SOC15_DPG_MODE_2_0(SOC15_DPG_MODE_OFFSET_2_0(
				UVD, 0, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH), 0, 0, indirect);
			WREG32_SOC15_DPG_MODE_2_0(SOC15_DPG_MODE_OFFSET_2_0(
				UVD, 0, mmUVD_VCPU_CACHE_OFFSET0), 0, 0, indirect);
		}
		offset = 0;
	} else {
		WREG32_SOC15_DPG_MODE_2_0(SOC15_DPG_MODE_OFFSET_2_0(
			UVD, 0, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW),
			lower_32_bits(adev->vcn.inst->gpu_addr), 0, indirect);
		WREG32_SOC15_DPG_MODE_2_0(SOC15_DPG_MODE_OFFSET_2_0(
			UVD, 0, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH),
			upper_32_bits(adev->vcn.inst->gpu_addr), 0, indirect);
		offset = size;
		WREG32_SOC15_DPG_MODE_2_0(SOC15_DPG_MODE_OFFSET_2_0(
			UVD, 0, mmUVD_VCPU_CACHE_OFFSET0),
			AMDGPU_UVD_FIRMWARE_OFFSET >> 3, 0, indirect);
	}

	if (!indirect)
		WREG32_SOC15_DPG_MODE_2_0(SOC15_DPG_MODE_OFFSET_2_0(
			UVD, 0, mmUVD_VCPU_CACHE_SIZE0), size, 0, indirect);
	else
		WREG32_SOC15_DPG_MODE_2_0(SOC15_DPG_MODE_OFFSET_2_0(
			UVD, 0, mmUVD_VCPU_CACHE_SIZE0), 0, 0, indirect);

	/* cache window 1: stack */
	if (!indirect) {
		WREG32_SOC15_DPG_MODE_2_0(SOC15_DPG_MODE_OFFSET_2_0(
			UVD, 0, mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_LOW),
			lower_32_bits(adev->vcn.inst->gpu_addr + offset), 0, indirect);
		WREG32_SOC15_DPG_MODE_2_0(SOC15_DPG_MODE_OFFSET_2_0(
			UVD, 0, mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_HIGH),
			upper_32_bits(adev->vcn.inst->gpu_addr + offset), 0, indirect);
		WREG32_SOC15_DPG_MODE_2_0(SOC15_DPG_MODE_OFFSET_2_0(
			UVD, 0, mmUVD_VCPU_CACHE_OFFSET1), 0, 0, indirect);
	} else {
		WREG32_SOC15_DPG_MODE_2_0(SOC15_DPG_MODE_OFFSET_2_0(
			UVD, 0, mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_LOW), 0, 0, indirect);
		WREG32_SOC15_DPG_MODE_2_0(SOC15_DPG_MODE_OFFSET_2_0(
			UVD, 0, mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_HIGH), 0, 0, indirect);
		WREG32_SOC15_DPG_MODE_2_0(SOC15_DPG_MODE_OFFSET_2_0(
			UVD, 0, mmUVD_VCPU_CACHE_OFFSET1), 0, 0, indirect);
	}
	WREG32_SOC15_DPG_MODE_2_0(SOC15_DPG_MODE_OFFSET_2_0(
		UVD, 0, mmUVD_VCPU_CACHE_SIZE1), AMDGPU_VCN_STACK_SIZE, 0, indirect);

	/* cache window 2: context */
	WREG32_SOC15_DPG_MODE_2_0(SOC15_DPG_MODE_OFFSET_2_0(
		UVD, 0, mmUVD_LMI_VCPU_CACHE2_64BIT_BAR_LOW),
		lower_32_bits(adev->vcn.inst->gpu_addr + offset + AMDGPU_VCN_STACK_SIZE), 0, indirect);
	WREG32_SOC15_DPG_MODE_2_0(SOC15_DPG_MODE_OFFSET_2_0(
		UVD, 0, mmUVD_LMI_VCPU_CACHE2_64BIT_BAR_HIGH),
		upper_32_bits(adev->vcn.inst->gpu_addr + offset + AMDGPU_VCN_STACK_SIZE), 0, indirect);
	WREG32_SOC15_DPG_MODE_2_0(SOC15_DPG_MODE_OFFSET_2_0(
		UVD, 0, mmUVD_VCPU_CACHE_OFFSET2), 0, 0, indirect);
	WREG32_SOC15_DPG_MODE_2_0(SOC15_DPG_MODE_OFFSET_2_0(
		UVD, 0, mmUVD_VCPU_CACHE_SIZE2), AMDGPU_VCN_CONTEXT_SIZE, 0, indirect);

	/* non-cache window */
	WREG32_SOC15_DPG_MODE_2_0(SOC15_DPG_MODE_OFFSET_2_0(
		UVD, 0, mmUVD_LMI_VCPU_NC0_64BIT_BAR_LOW), 0, 0, indirect);
	WREG32_SOC15_DPG_MODE_2_0(SOC15_DPG_MODE_OFFSET_2_0(
		UVD, 0, mmUVD_LMI_VCPU_NC0_64BIT_BAR_HIGH), 0, 0, indirect);
	WREG32_SOC15_DPG_MODE_2_0(SOC15_DPG_MODE_OFFSET_2_0(
		UVD, 0, mmUVD_VCPU_NONCACHE_OFFSET0), 0, 0, indirect);
	WREG32_SOC15_DPG_MODE_2_0(SOC15_DPG_MODE_OFFSET_2_0(
		UVD, 0, mmUVD_VCPU_NONCACHE_SIZE0), 0, 0, indirect);

	/* VCN global tiling registers */
	WREG32_SOC15_DPG_MODE_2_0(SOC15_DPG_MODE_OFFSET_2_0(
		UVD, 0, mmUVD_GFX10_ADDR_CONFIG), adev->gfx.config.gb_addr_config, 0, indirect);
}