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
typedef  int u32 ;
struct TYPE_10__ {int /*<<< orphan*/  ucode_size_bytes; int /*<<< orphan*/  ucode_array_offset_bytes; int /*<<< orphan*/  ucode_version; } ;
struct rlc_firmware_header_v1_0 {TYPE_5__ header; int /*<<< orphan*/  ucode_feature_version; } ;
struct TYPE_8__ {TYPE_2__* funcs; } ;
struct TYPE_9__ {int rlc_fw_version; int rlc_feature_version; TYPE_3__ rlc; TYPE_1__* rlc_fw; } ;
struct amdgpu_device {scalar_t__ asic_type; TYPE_4__ gfx; int /*<<< orphan*/  grbm_idx_mutex; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_7__ {int /*<<< orphan*/  (* start ) (struct amdgpu_device*) ;int /*<<< orphan*/  (* reset ) (struct amdgpu_device*) ;int /*<<< orphan*/  (* stop ) (struct amdgpu_device*) ;} ;
struct TYPE_6__ {scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ CHIP_BONAIRE ; 
 int EINVAL ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  amdgpu_ucode_print_rlc_hdr (TYPE_5__*) ; 
 int /*<<< orphan*/  gfx_v7_0_enable_lbpw (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gfx_v7_0_init_pg (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v7_0_select_se_sh (struct amdgpu_device*,int,int,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmRLC_CGCG_CGLS_CTRL ; 
 int /*<<< orphan*/  mmRLC_DRIVER_CPDMA_STATUS ; 
 int /*<<< orphan*/  mmRLC_GPM_UCODE_ADDR ; 
 int /*<<< orphan*/  mmRLC_GPM_UCODE_DATA ; 
 int /*<<< orphan*/  mmRLC_LB_CNTL ; 
 int /*<<< orphan*/  mmRLC_LB_CNTR_INIT ; 
 int /*<<< orphan*/  mmRLC_LB_CNTR_MAX ; 
 int /*<<< orphan*/  mmRLC_LB_INIT_CU_MASK ; 
 int /*<<< orphan*/  mmRLC_LB_PARAMS ; 
 int /*<<< orphan*/  mmRLC_MC_CNTL ; 
 int /*<<< orphan*/  mmRLC_UCODE_CNTL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_device*) ; 
 int /*<<< orphan*/  stub2 (struct amdgpu_device*) ; 
 int /*<<< orphan*/  stub3 (struct amdgpu_device*) ; 

__attribute__((used)) static int gfx_v7_0_rlc_resume(struct amdgpu_device *adev)
{
	const struct rlc_firmware_header_v1_0 *hdr;
	const __le32 *fw_data;
	unsigned i, fw_size;
	u32 tmp;

	if (!adev->gfx.rlc_fw)
		return -EINVAL;

	hdr = (const struct rlc_firmware_header_v1_0 *)adev->gfx.rlc_fw->data;
	amdgpu_ucode_print_rlc_hdr(&hdr->header);
	adev->gfx.rlc_fw_version = le32_to_cpu(hdr->header.ucode_version);
	adev->gfx.rlc_feature_version = le32_to_cpu(
					hdr->ucode_feature_version);

	adev->gfx.rlc.funcs->stop(adev);

	/* disable CG */
	tmp = RREG32(mmRLC_CGCG_CGLS_CTRL) & 0xfffffffc;
	WREG32(mmRLC_CGCG_CGLS_CTRL, tmp);

	adev->gfx.rlc.funcs->reset(adev);

	gfx_v7_0_init_pg(adev);

	WREG32(mmRLC_LB_CNTR_INIT, 0);
	WREG32(mmRLC_LB_CNTR_MAX, 0x00008000);

	mutex_lock(&adev->grbm_idx_mutex);
	gfx_v7_0_select_se_sh(adev, 0xffffffff, 0xffffffff, 0xffffffff);
	WREG32(mmRLC_LB_INIT_CU_MASK, 0xffffffff);
	WREG32(mmRLC_LB_PARAMS, 0x00600408);
	WREG32(mmRLC_LB_CNTL, 0x80000004);
	mutex_unlock(&adev->grbm_idx_mutex);

	WREG32(mmRLC_MC_CNTL, 0);
	WREG32(mmRLC_UCODE_CNTL, 0);

	fw_data = (const __le32 *)
		(adev->gfx.rlc_fw->data + le32_to_cpu(hdr->header.ucode_array_offset_bytes));
	fw_size = le32_to_cpu(hdr->header.ucode_size_bytes) / 4;
	WREG32(mmRLC_GPM_UCODE_ADDR, 0);
	for (i = 0; i < fw_size; i++)
		WREG32(mmRLC_GPM_UCODE_DATA, le32_to_cpup(fw_data++));
	WREG32(mmRLC_GPM_UCODE_ADDR, adev->gfx.rlc_fw_version);

	/* XXX - find out what chips support lbpw */
	gfx_v7_0_enable_lbpw(adev, false);

	if (adev->asic_type == CHIP_BONAIRE)
		WREG32(mmRLC_DRIVER_CPDMA_STATUS, 0);

	adev->gfx.rlc.funcs->start(adev);

	return 0;
}