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
struct hwrm_func_vf_cfg_input {void* async_event_cr; void* enables; int /*<<< orphan*/  member_0; void* fid; } ;
struct hwrm_func_cfg_input {void* async_event_cr; void* enables; int /*<<< orphan*/  member_0; void* fid; } ;
struct bnxt {int dummy; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 scalar_t__ BNXT_PF (struct bnxt*) ; 
 int /*<<< orphan*/  FUNC_CFG_REQ_ENABLES_ASYNC_EVENT_CR ; 
 int /*<<< orphan*/  FUNC_VF_CFG_REQ_ENABLES_ASYNC_EVENT_CR ; 
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_FUNC_CFG ; 
 int /*<<< orphan*/  HWRM_FUNC_VF_CFG ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_func_vf_cfg_input*,int /*<<< orphan*/ ,int,int) ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int hwrm_send_message (struct bnxt*,struct hwrm_func_vf_cfg_input*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_hwrm_set_async_event_cr(struct bnxt *bp, int idx)
{
	int rc;

	if (BNXT_PF(bp)) {
		struct hwrm_func_cfg_input req = {0};

		bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_CFG, -1, -1);
		req.fid = cpu_to_le16(0xffff);
		req.enables = cpu_to_le32(FUNC_CFG_REQ_ENABLES_ASYNC_EVENT_CR);
		req.async_event_cr = cpu_to_le16(idx);
		rc = hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
	} else {
		struct hwrm_func_vf_cfg_input req = {0};

		bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_VF_CFG, -1, -1);
		req.enables =
			cpu_to_le32(FUNC_VF_CFG_REQ_ENABLES_ASYNC_EVENT_CR);
		req.async_event_cr = cpu_to_le16(idx);
		rc = hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
	}
	return rc;
}