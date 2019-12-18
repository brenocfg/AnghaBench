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
typedef  scalar_t__ u16 ;
struct hwrm_func_cfg_input {int /*<<< orphan*/  evb_mode; int /*<<< orphan*/  enables; int /*<<< orphan*/  fid; int /*<<< orphan*/  member_0; } ;
struct bnxt {int dummy; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 scalar_t__ BRIDGE_MODE_VEB ; 
 scalar_t__ BRIDGE_MODE_VEPA ; 
 int EINVAL ; 
 int /*<<< orphan*/  FUNC_CFG_REQ_ENABLES_EVB_MODE ; 
 int /*<<< orphan*/  FUNC_CFG_REQ_EVB_MODE_VEB ; 
 int /*<<< orphan*/  FUNC_CFG_REQ_EVB_MODE_VEPA ; 
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_FUNC_CFG ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_func_cfg_input*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int hwrm_send_message (struct bnxt*,struct hwrm_func_cfg_input*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_hwrm_set_br_mode(struct bnxt *bp, u16 br_mode)
{
	struct hwrm_func_cfg_input req = {0};
	int rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_CFG, -1, -1);
	req.fid = cpu_to_le16(0xffff);
	req.enables = cpu_to_le32(FUNC_CFG_REQ_ENABLES_EVB_MODE);
	if (br_mode == BRIDGE_MODE_VEB)
		req.evb_mode = FUNC_CFG_REQ_EVB_MODE_VEB;
	else if (br_mode == BRIDGE_MODE_VEPA)
		req.evb_mode = FUNC_CFG_REQ_EVB_MODE_VEPA;
	else
		return -EINVAL;
	rc = hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
	return rc;
}