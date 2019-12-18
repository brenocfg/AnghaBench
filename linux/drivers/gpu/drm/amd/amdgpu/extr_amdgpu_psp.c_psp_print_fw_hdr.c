#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct smc_firmware_header_v1_0 {int /*<<< orphan*/  header; } ;
struct sdma_firmware_header_v1_0 {int /*<<< orphan*/  header; } ;
struct rlc_firmware_header_v2_0 {int /*<<< orphan*/  header; } ;
struct psp_context {struct amdgpu_device* adev; } ;
struct gfx_firmware_header_v1_0 {int /*<<< orphan*/  header; } ;
struct amdgpu_firmware_info {size_t ucode_id; } ;
struct TYPE_13__ {TYPE_10__* fw; } ;
struct TYPE_22__ {TYPE_8__* rlc_fw; TYPE_7__* mec_fw; TYPE_6__* me_fw; TYPE_5__* pfp_fw; TYPE_4__* ce_fw; } ;
struct TYPE_16__ {TYPE_2__* instance; } ;
struct amdgpu_device {TYPE_11__ pm; TYPE_9__ gfx; TYPE_3__ sdma; } ;
struct TYPE_21__ {scalar_t__ data; } ;
struct TYPE_20__ {scalar_t__ data; } ;
struct TYPE_19__ {scalar_t__ data; } ;
struct TYPE_18__ {scalar_t__ data; } ;
struct TYPE_17__ {scalar_t__ data; } ;
struct TYPE_15__ {TYPE_1__* fw; } ;
struct TYPE_14__ {scalar_t__ data; } ;
struct TYPE_12__ {scalar_t__ data; } ;

/* Variables and functions */
#define  AMDGPU_UCODE_ID_CP_CE 141 
#define  AMDGPU_UCODE_ID_CP_ME 140 
#define  AMDGPU_UCODE_ID_CP_MEC1 139 
#define  AMDGPU_UCODE_ID_CP_PFP 138 
#define  AMDGPU_UCODE_ID_RLC_G 137 
#define  AMDGPU_UCODE_ID_SDMA0 136 
#define  AMDGPU_UCODE_ID_SDMA1 135 
#define  AMDGPU_UCODE_ID_SDMA2 134 
#define  AMDGPU_UCODE_ID_SDMA3 133 
#define  AMDGPU_UCODE_ID_SDMA4 132 
#define  AMDGPU_UCODE_ID_SDMA5 131 
#define  AMDGPU_UCODE_ID_SDMA6 130 
#define  AMDGPU_UCODE_ID_SDMA7 129 
#define  AMDGPU_UCODE_ID_SMC 128 
 int /*<<< orphan*/  amdgpu_ucode_print_gfx_hdr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_ucode_print_rlc_hdr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_ucode_print_sdma_hdr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_ucode_print_smc_hdr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void psp_print_fw_hdr(struct psp_context *psp,
			     struct amdgpu_firmware_info *ucode)
{
	struct amdgpu_device *adev = psp->adev;
	const struct sdma_firmware_header_v1_0 *sdma_hdr =
		(const struct sdma_firmware_header_v1_0 *)
		adev->sdma.instance[ucode->ucode_id - AMDGPU_UCODE_ID_SDMA0].fw->data;
	const struct gfx_firmware_header_v1_0 *ce_hdr =
		(const struct gfx_firmware_header_v1_0 *)adev->gfx.ce_fw->data;
	const struct gfx_firmware_header_v1_0 *pfp_hdr =
		(const struct gfx_firmware_header_v1_0 *)adev->gfx.pfp_fw->data;
	const struct gfx_firmware_header_v1_0 *me_hdr =
		(const struct gfx_firmware_header_v1_0 *)adev->gfx.me_fw->data;
	const struct gfx_firmware_header_v1_0 *mec_hdr =
		(const struct gfx_firmware_header_v1_0 *)adev->gfx.mec_fw->data;
	const struct rlc_firmware_header_v2_0 *rlc_hdr =
		(const struct rlc_firmware_header_v2_0 *)adev->gfx.rlc_fw->data;
	const struct smc_firmware_header_v1_0 *smc_hdr =
		(const struct smc_firmware_header_v1_0 *)adev->pm.fw->data;

	switch (ucode->ucode_id) {
	case AMDGPU_UCODE_ID_SDMA0:
	case AMDGPU_UCODE_ID_SDMA1:
	case AMDGPU_UCODE_ID_SDMA2:
	case AMDGPU_UCODE_ID_SDMA3:
	case AMDGPU_UCODE_ID_SDMA4:
	case AMDGPU_UCODE_ID_SDMA5:
	case AMDGPU_UCODE_ID_SDMA6:
	case AMDGPU_UCODE_ID_SDMA7:
		amdgpu_ucode_print_sdma_hdr(&sdma_hdr->header);
		break;
	case AMDGPU_UCODE_ID_CP_CE:
		amdgpu_ucode_print_gfx_hdr(&ce_hdr->header);
		break;
	case AMDGPU_UCODE_ID_CP_PFP:
		amdgpu_ucode_print_gfx_hdr(&pfp_hdr->header);
		break;
	case AMDGPU_UCODE_ID_CP_ME:
		amdgpu_ucode_print_gfx_hdr(&me_hdr->header);
		break;
	case AMDGPU_UCODE_ID_CP_MEC1:
		amdgpu_ucode_print_gfx_hdr(&mec_hdr->header);
		break;
	case AMDGPU_UCODE_ID_RLC_G:
		amdgpu_ucode_print_rlc_hdr(&rlc_hdr->header);
		break;
	case AMDGPU_UCODE_ID_SMC:
		amdgpu_ucode_print_smc_hdr(&smc_hdr->header);
		break;
	default:
		break;
	}
}