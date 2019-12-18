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
struct amdgpu_device {int dummy; } ;
typedef  enum AMDGPU_UCODE_ID { ____Placeholder_AMDGPU_UCODE_ID } AMDGPU_UCODE_ID ;

/* Variables and functions */
#define  AMDGPU_UCODE_ID_CP_CE 139 
#define  AMDGPU_UCODE_ID_CP_ME 138 
#define  AMDGPU_UCODE_ID_CP_MEC1 137 
#define  AMDGPU_UCODE_ID_CP_MEC2 136 
#define  AMDGPU_UCODE_ID_CP_PFP 135 
#define  AMDGPU_UCODE_ID_MAXIMUM 134 
#define  AMDGPU_UCODE_ID_RLC_G 133 
#define  AMDGPU_UCODE_ID_SDMA0 132 
#define  AMDGPU_UCODE_ID_SDMA1 131 
#define  AMDGPU_UCODE_ID_SMC 130 
#define  AMDGPU_UCODE_ID_UVD 129 
#define  AMDGPU_UCODE_ID_VCE 128 
 int EINVAL ; 
 int /*<<< orphan*/  GC ; 
 int /*<<< orphan*/  SDMA0 ; 
 unsigned int SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCP_CE_UCODE_ADDR ; 
 int /*<<< orphan*/  mmCP_CE_UCODE_DATA ; 
 int /*<<< orphan*/  mmCP_HYP_MEC2_UCODE_ADDR ; 
 int /*<<< orphan*/  mmCP_HYP_MEC2_UCODE_DATA ; 
 int /*<<< orphan*/  mmCP_HYP_ME_UCODE_ADDR ; 
 int /*<<< orphan*/  mmCP_HYP_ME_UCODE_DATA ; 
 int /*<<< orphan*/  mmCP_MEC_ME1_UCODE_ADDR ; 
 int /*<<< orphan*/  mmCP_MEC_ME1_UCODE_DATA ; 
 int /*<<< orphan*/  mmCP_PFP_UCODE_ADDR ; 
 int /*<<< orphan*/  mmCP_PFP_UCODE_DATA ; 
 int /*<<< orphan*/  mmRLC_GPM_UCODE_ADDR ; 
 int /*<<< orphan*/  mmRLC_GPM_UCODE_DATA ; 
 int /*<<< orphan*/  mmSDMA0_UCODE_ADDR ; 
 int /*<<< orphan*/  mmSDMA0_UCODE_DATA ; 

__attribute__((used)) static int
psp_v12_0_sram_map(struct amdgpu_device *adev,
		  unsigned int *sram_offset, unsigned int *sram_addr_reg_offset,
		  unsigned int *sram_data_reg_offset,
		  enum AMDGPU_UCODE_ID ucode_id)
{
	int ret = 0;

	switch (ucode_id) {
/* TODO: needs to confirm */
#if 0
	case AMDGPU_UCODE_ID_SMC:
		*sram_offset = 0;
		*sram_addr_reg_offset = 0;
		*sram_data_reg_offset = 0;
		break;
#endif

	case AMDGPU_UCODE_ID_CP_CE:
		*sram_offset = 0x0;
		*sram_addr_reg_offset = SOC15_REG_OFFSET(GC, 0, mmCP_CE_UCODE_ADDR);
		*sram_data_reg_offset = SOC15_REG_OFFSET(GC, 0, mmCP_CE_UCODE_DATA);
		break;

	case AMDGPU_UCODE_ID_CP_PFP:
		*sram_offset = 0x0;
		*sram_addr_reg_offset = SOC15_REG_OFFSET(GC, 0, mmCP_PFP_UCODE_ADDR);
		*sram_data_reg_offset = SOC15_REG_OFFSET(GC, 0, mmCP_PFP_UCODE_DATA);
		break;

	case AMDGPU_UCODE_ID_CP_ME:
		*sram_offset = 0x0;
		*sram_addr_reg_offset = SOC15_REG_OFFSET(GC, 0, mmCP_HYP_ME_UCODE_ADDR);
		*sram_data_reg_offset = SOC15_REG_OFFSET(GC, 0, mmCP_HYP_ME_UCODE_DATA);
		break;

	case AMDGPU_UCODE_ID_CP_MEC1:
		*sram_offset = 0x10000;
		*sram_addr_reg_offset = SOC15_REG_OFFSET(GC, 0, mmCP_MEC_ME1_UCODE_ADDR);
		*sram_data_reg_offset = SOC15_REG_OFFSET(GC, 0, mmCP_MEC_ME1_UCODE_DATA);
		break;

	case AMDGPU_UCODE_ID_CP_MEC2:
		*sram_offset = 0x10000;
		*sram_addr_reg_offset = SOC15_REG_OFFSET(GC, 0, mmCP_HYP_MEC2_UCODE_ADDR);
		*sram_data_reg_offset = SOC15_REG_OFFSET(GC, 0, mmCP_HYP_MEC2_UCODE_DATA);
		break;

	case AMDGPU_UCODE_ID_RLC_G:
		*sram_offset = 0x2000;
		*sram_addr_reg_offset = SOC15_REG_OFFSET(GC, 0, mmRLC_GPM_UCODE_ADDR);
		*sram_data_reg_offset = SOC15_REG_OFFSET(GC, 0, mmRLC_GPM_UCODE_DATA);
		break;

	case AMDGPU_UCODE_ID_SDMA0:
		*sram_offset = 0x0;
		*sram_addr_reg_offset = SOC15_REG_OFFSET(SDMA0, 0, mmSDMA0_UCODE_ADDR);
		*sram_data_reg_offset = SOC15_REG_OFFSET(SDMA0, 0, mmSDMA0_UCODE_DATA);
		break;

/* TODO: needs to confirm */
#if 0
	case AMDGPU_UCODE_ID_SDMA1:
		*sram_offset = ;
		*sram_addr_reg_offset = ;
		break;

	case AMDGPU_UCODE_ID_UVD:
		*sram_offset = ;
		*sram_addr_reg_offset = ;
		break;

	case AMDGPU_UCODE_ID_VCE:
		*sram_offset = ;
		*sram_addr_reg_offset = ;
		break;
#endif

	case AMDGPU_UCODE_ID_MAXIMUM:
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}