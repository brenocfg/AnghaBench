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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_MB_PARAM_NVM_CFG_OPTION_ENTITY_ID ; 
 int /*<<< orphan*/  DRV_MB_PARAM_NVM_CFG_OPTION_ENTITY_SEL ; 
 int /*<<< orphan*/  DRV_MB_PARAM_NVM_CFG_OPTION_FREE ; 
 int /*<<< orphan*/  DRV_MB_PARAM_NVM_CFG_OPTION_ID ; 
 int /*<<< orphan*/  DRV_MB_PARAM_NVM_CFG_OPTION_INIT ; 
 int /*<<< orphan*/  DRV_MSG_CODE_GET_NVM_CFG_OPTION ; 
 int /*<<< orphan*/  QED_MFW_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int QED_NVM_CFG_OPTION_ENTITY_SEL ; 
 int QED_NVM_CFG_OPTION_FREE ; 
 int QED_NVM_CFG_OPTION_INIT ; 
 int qed_mcp_nvm_rd_cmd (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int qed_mcp_nvm_get_cfg(struct qed_hwfn *p_hwfn, struct qed_ptt *p_ptt,
			u16 option_id, u8 entity_id, u16 flags, u8 *p_buf,
			u32 *p_len)
{
	u32 mb_param = 0, resp, param;
	int rc;

	QED_MFW_SET_FIELD(mb_param, DRV_MB_PARAM_NVM_CFG_OPTION_ID, option_id);
	if (flags & QED_NVM_CFG_OPTION_INIT)
		QED_MFW_SET_FIELD(mb_param,
				  DRV_MB_PARAM_NVM_CFG_OPTION_INIT, 1);
	if (flags & QED_NVM_CFG_OPTION_FREE)
		QED_MFW_SET_FIELD(mb_param,
				  DRV_MB_PARAM_NVM_CFG_OPTION_FREE, 1);
	if (flags & QED_NVM_CFG_OPTION_ENTITY_SEL) {
		QED_MFW_SET_FIELD(mb_param,
				  DRV_MB_PARAM_NVM_CFG_OPTION_ENTITY_SEL, 1);
		QED_MFW_SET_FIELD(mb_param,
				  DRV_MB_PARAM_NVM_CFG_OPTION_ENTITY_ID,
				  entity_id);
	}

	rc = qed_mcp_nvm_rd_cmd(p_hwfn, p_ptt,
				DRV_MSG_CODE_GET_NVM_CFG_OPTION,
				mb_param, &resp, &param, p_len, (u32 *)p_buf);

	return rc;
}