#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct TYPE_10__ {int /*<<< orphan*/  ucode_array_offset_bytes; } ;
struct gfx_firmware_header_v1_0 {unsigned int jt_size; int jt_offset; TYPE_5__ header; } ;
struct TYPE_8__ {int mec_fw_gpu_addr; } ;
struct TYPE_9__ {int mec_fw_version; TYPE_3__ mec; TYPE_1__* mec_fw; } ;
struct amdgpu_device {TYPE_4__ gfx; TYPE_2__* nbio_funcs; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_7__ {int /*<<< orphan*/  (* hdp_flush ) (struct amdgpu_device*,int /*<<< orphan*/ *) ;} ;
struct TYPE_6__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDRESS_CLAMP ; 
 int /*<<< orphan*/  CACHE_POLICY ; 
 int /*<<< orphan*/  CP_CPC_IC_BASE_CNTL ; 
 int /*<<< orphan*/  CP_CPC_IC_OP_CNTL ; 
 int EINVAL ; 
 int /*<<< orphan*/  EXE_DISABLE ; 
 int /*<<< orphan*/  GC ; 
 int /*<<< orphan*/  INVALIDATE_CACHE ; 
 int /*<<< orphan*/  INVALIDATE_CACHE_COMPLETE ; 
 int REG_GET_FIELD (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int REG_SET_FIELD (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int amdgpu_emu_mode ; 
 int /*<<< orphan*/  amdgpu_ucode_print_gfx_hdr (TYPE_5__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gfx_v10_0_cp_compute_enable (struct amdgpu_device*,int) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mmCP_CPC_IC_BASE_CNTL ; 
 int /*<<< orphan*/  mmCP_CPC_IC_BASE_HI ; 
 int /*<<< orphan*/  mmCP_CPC_IC_BASE_LO ; 
 int /*<<< orphan*/  mmCP_CPC_IC_OP_CNTL ; 
 int /*<<< orphan*/  mmCP_MEC_ME1_UCODE_ADDR ; 
 int /*<<< orphan*/  mmCP_MEC_ME1_UCODE_DATA ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static int gfx_v10_0_cp_compute_load_microcode(struct amdgpu_device *adev)
{
	const struct gfx_firmware_header_v1_0 *mec_hdr;
	const __le32 *fw_data;
	unsigned i;
	u32 tmp;
	u32 usec_timeout = 50000; /* Wait for 50 ms */

	if (!adev->gfx.mec_fw)
		return -EINVAL;

	gfx_v10_0_cp_compute_enable(adev, false);

	mec_hdr = (const struct gfx_firmware_header_v1_0 *)adev->gfx.mec_fw->data;
	amdgpu_ucode_print_gfx_hdr(&mec_hdr->header);

	fw_data = (const __le32 *)
		(adev->gfx.mec_fw->data +
		 le32_to_cpu(mec_hdr->header.ucode_array_offset_bytes));

	/* Trigger an invalidation of the L1 instruction caches */
	tmp = RREG32_SOC15(GC, 0, mmCP_CPC_IC_OP_CNTL);
	tmp = REG_SET_FIELD(tmp, CP_CPC_IC_OP_CNTL, INVALIDATE_CACHE, 1);
	WREG32_SOC15(GC, 0, mmCP_CPC_IC_OP_CNTL, tmp);

	/* Wait for invalidation complete */
	for (i = 0; i < usec_timeout; i++) {
		tmp = RREG32_SOC15(GC, 0, mmCP_CPC_IC_OP_CNTL);
		if (1 == REG_GET_FIELD(tmp, CP_CPC_IC_OP_CNTL,
				       INVALIDATE_CACHE_COMPLETE))
			break;
		udelay(1);
	}

	if (i >= usec_timeout) {
		dev_err(adev->dev, "failed to invalidate instruction cache\n");
		return -EINVAL;
	}

	if (amdgpu_emu_mode == 1)
		adev->nbio_funcs->hdp_flush(adev, NULL);

	tmp = RREG32_SOC15(GC, 0, mmCP_CPC_IC_BASE_CNTL);
	tmp = REG_SET_FIELD(tmp, CP_CPC_IC_BASE_CNTL, CACHE_POLICY, 0);
	tmp = REG_SET_FIELD(tmp, CP_CPC_IC_BASE_CNTL, EXE_DISABLE, 0);
	tmp = REG_SET_FIELD(tmp, CP_CPC_IC_BASE_CNTL, ADDRESS_CLAMP, 1);
	WREG32_SOC15(GC, 0, mmCP_CPC_IC_BASE_CNTL, tmp);

	WREG32_SOC15(GC, 0, mmCP_CPC_IC_BASE_LO, adev->gfx.mec.mec_fw_gpu_addr &
		     0xFFFFF000);
	WREG32_SOC15(GC, 0, mmCP_CPC_IC_BASE_HI,
		     upper_32_bits(adev->gfx.mec.mec_fw_gpu_addr));

	/* MEC1 */
	WREG32_SOC15(GC, 0, mmCP_MEC_ME1_UCODE_ADDR, 0);

	for (i = 0; i < mec_hdr->jt_size; i++)
		WREG32_SOC15(GC, 0, mmCP_MEC_ME1_UCODE_DATA,
			     le32_to_cpup(fw_data + mec_hdr->jt_offset + i));

	WREG32_SOC15(GC, 0, mmCP_MEC_ME1_UCODE_ADDR, adev->gfx.mec_fw_version);

	/*
	 * TODO: Loading MEC2 firmware is only necessary if MEC2 should run
	 * different microcode than MEC1.
	 */

	return 0;
}