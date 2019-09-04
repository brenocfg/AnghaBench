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
typedef  int u32 ;
typedef  int u16 ;
struct hwrm_func_drv_rgtr_output {int flags; } ;
struct hwrm_func_drv_rgtr_input {int enables; int flags; int* vf_req_fwd; void* ver_upd; void* ver_min; void* ver_maj; void* ver_upd_8b; void* ver_min_8b; void* ver_maj_8b; void* os_type; int /*<<< orphan*/  member_0; } ;
struct bnxt {int /*<<< orphan*/  hwrm_cmd_lock; int /*<<< orphan*/  fw_cap; struct hwrm_func_drv_rgtr_output* hwrm_cmd_resp_addr; } ;
typedef  int /*<<< orphan*/  req ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  BNXT_FW_CAP_IF_CHANGE ; 
 scalar_t__ BNXT_PF (struct bnxt*) ; 
 void* DRV_VER_MAJ ; 
 void* DRV_VER_MIN ; 
 void* DRV_VER_UPD ; 
 int EIO ; 
 int FUNC_DRV_RGTR_REQ_ENABLES_OS_TYPE ; 
 int FUNC_DRV_RGTR_REQ_ENABLES_VER ; 
 int FUNC_DRV_RGTR_REQ_ENABLES_VF_REQ_FWD ; 
 int FUNC_DRV_RGTR_REQ_FLAGS_16BIT_VER_MODE ; 
 void* FUNC_DRV_RGTR_REQ_OS_TYPE_LINUX ; 
 int FUNC_DRV_RGTR_RESP_FLAGS_IF_CHANGE_SUPPORTED ; 
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_FUNC_DRV_RGTR ; 
 int _hwrm_send_message (struct bnxt*,struct hwrm_func_drv_rgtr_input*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_func_drv_rgtr_input*,int /*<<< orphan*/ ,int,int) ; 
 int* bnxt_vf_req_snif ; 
 void* cpu_to_le16 (void*) ; 
 int cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnxt_hwrm_func_drv_rgtr(struct bnxt *bp)
{
	struct hwrm_func_drv_rgtr_output *resp = bp->hwrm_cmd_resp_addr;
	struct hwrm_func_drv_rgtr_input req = {0};
	int rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_DRV_RGTR, -1, -1);

	req.enables =
		cpu_to_le32(FUNC_DRV_RGTR_REQ_ENABLES_OS_TYPE |
			    FUNC_DRV_RGTR_REQ_ENABLES_VER);

	req.os_type = cpu_to_le16(FUNC_DRV_RGTR_REQ_OS_TYPE_LINUX);
	req.flags = cpu_to_le32(FUNC_DRV_RGTR_REQ_FLAGS_16BIT_VER_MODE);
	req.ver_maj_8b = DRV_VER_MAJ;
	req.ver_min_8b = DRV_VER_MIN;
	req.ver_upd_8b = DRV_VER_UPD;
	req.ver_maj = cpu_to_le16(DRV_VER_MAJ);
	req.ver_min = cpu_to_le16(DRV_VER_MIN);
	req.ver_upd = cpu_to_le16(DRV_VER_UPD);

	if (BNXT_PF(bp)) {
		u32 data[8];
		int i;

		memset(data, 0, sizeof(data));
		for (i = 0; i < ARRAY_SIZE(bnxt_vf_req_snif); i++) {
			u16 cmd = bnxt_vf_req_snif[i];
			unsigned int bit, idx;

			idx = cmd / 32;
			bit = cmd % 32;
			data[idx] |= 1 << bit;
		}

		for (i = 0; i < 8; i++)
			req.vf_req_fwd[i] = cpu_to_le32(data[i]);

		req.enables |=
			cpu_to_le32(FUNC_DRV_RGTR_REQ_ENABLES_VF_REQ_FWD);
	}

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
	if (rc)
		rc = -EIO;
	else if (resp->flags &
		 cpu_to_le32(FUNC_DRV_RGTR_RESP_FLAGS_IF_CHANGE_SUPPORTED))
		bp->fw_cap |= BNXT_FW_CAP_IF_CHANGE;
	mutex_unlock(&bp->hwrm_cmd_lock);
	return rc;
}