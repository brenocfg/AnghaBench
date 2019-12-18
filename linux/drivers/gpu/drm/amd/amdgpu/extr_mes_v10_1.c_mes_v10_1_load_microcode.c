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
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  data_fw_gpu_addr; int /*<<< orphan*/  ucode_fw_gpu_addr; scalar_t__ uc_start_addr; int /*<<< orphan*/  fw; } ;
struct amdgpu_device {int /*<<< orphan*/  srbm_mutex; TYPE_1__ mes; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP_MES_IC_OP_CNTL ; 
 int EINVAL ; 
 int /*<<< orphan*/  GC ; 
 int /*<<< orphan*/  INVALIDATE_CACHE ; 
 int /*<<< orphan*/  PRIME_ICACHE ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int mes_v10_1_allocate_ucode_buffer (struct amdgpu_device*) ; 
 int mes_v10_1_allocate_ucode_data_buffer (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mes_v10_1_enable (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  mes_v10_1_free_ucode_buffers (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmCP_MES_IC_BASE_CNTL ; 
 int /*<<< orphan*/  mmCP_MES_IC_BASE_HI ; 
 int /*<<< orphan*/  mmCP_MES_IC_BASE_LO ; 
 int /*<<< orphan*/  mmCP_MES_IC_OP_CNTL ; 
 int /*<<< orphan*/  mmCP_MES_MDBASE_HI ; 
 int /*<<< orphan*/  mmCP_MES_MDBASE_LO ; 
 int /*<<< orphan*/  mmCP_MES_MDBOUND_LO ; 
 int /*<<< orphan*/  mmCP_MES_MIBOUND_LO ; 
 int /*<<< orphan*/  mmCP_MES_PRGRM_CNTR_START ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nv_grbm_select (struct amdgpu_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mes_v10_1_load_microcode(struct amdgpu_device *adev)
{
	int r;
	uint32_t data;

	if (!adev->mes.fw)
		return -EINVAL;

	r = mes_v10_1_allocate_ucode_buffer(adev);
	if (r)
		return r;

	r = mes_v10_1_allocate_ucode_data_buffer(adev);
	if (r) {
		mes_v10_1_free_ucode_buffers(adev);
		return r;
	}

	mes_v10_1_enable(adev, false);

	WREG32_SOC15(GC, 0, mmCP_MES_IC_BASE_CNTL, 0);

	mutex_lock(&adev->srbm_mutex);
	/* me=3, pipe=0, queue=0 */
	nv_grbm_select(adev, 3, 0, 0, 0);

	/* set ucode start address */
	WREG32_SOC15(GC, 0, mmCP_MES_PRGRM_CNTR_START,
		     (uint32_t)(adev->mes.uc_start_addr) >> 2);

	/* set ucode fimrware address */
	WREG32_SOC15(GC, 0, mmCP_MES_IC_BASE_LO,
		     lower_32_bits(adev->mes.ucode_fw_gpu_addr));
	WREG32_SOC15(GC, 0, mmCP_MES_IC_BASE_HI,
		     upper_32_bits(adev->mes.ucode_fw_gpu_addr));

	/* set ucode instruction cache boundary to 2M-1 */
	WREG32_SOC15(GC, 0, mmCP_MES_MIBOUND_LO, 0x1FFFFF);

	/* set ucode data firmware address */
	WREG32_SOC15(GC, 0, mmCP_MES_MDBASE_LO,
		     lower_32_bits(adev->mes.data_fw_gpu_addr));
	WREG32_SOC15(GC, 0, mmCP_MES_MDBASE_HI,
		     upper_32_bits(adev->mes.data_fw_gpu_addr));

	/* Set 0x3FFFF (256K-1) to CP_MES_MDBOUND_LO */
	WREG32_SOC15(GC, 0, mmCP_MES_MDBOUND_LO, 0x3FFFF);

	/* invalidate ICACHE */
	data = RREG32_SOC15(GC, 0, mmCP_MES_IC_OP_CNTL);
	data = REG_SET_FIELD(data, CP_MES_IC_OP_CNTL, PRIME_ICACHE, 0);
	data = REG_SET_FIELD(data, CP_MES_IC_OP_CNTL, INVALIDATE_CACHE, 1);
	WREG32_SOC15(GC, 0, mmCP_MES_IC_OP_CNTL, data);

	/* prime the ICACHE. */
	data = RREG32_SOC15(GC, 0, mmCP_MES_IC_OP_CNTL);
	data = REG_SET_FIELD(data, CP_MES_IC_OP_CNTL, PRIME_ICACHE, 1);
	WREG32_SOC15(GC, 0, mmCP_MES_IC_OP_CNTL, data);

	nv_grbm_select(adev, 0, 0, 0, 0);
	mutex_unlock(&adev->srbm_mutex);

	return 0;
}