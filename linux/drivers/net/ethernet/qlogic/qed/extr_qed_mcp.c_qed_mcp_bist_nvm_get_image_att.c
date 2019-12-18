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
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;
struct bist_nvm_image_att {int return_code; } ;

/* Variables and functions */
 int DRV_MB_PARAM_BIST_NVM_TEST_IMAGE_BY_INDEX ; 
 int DRV_MB_PARAM_BIST_TEST_IMAGE_INDEX_SHIFT ; 
 int DRV_MB_PARAM_BIST_TEST_INDEX_SHIFT ; 
 int /*<<< orphan*/  DRV_MSG_CODE_BIST_TEST ; 
 int EINVAL ; 
 int FW_MSG_CODE_MASK ; 
 int FW_MSG_CODE_OK ; 
 int qed_mcp_nvm_rd_cmd (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int,int*,int*,int*,int*) ; 

int qed_mcp_bist_nvm_get_image_att(struct qed_hwfn *p_hwfn,
				   struct qed_ptt *p_ptt,
				   struct bist_nvm_image_att *p_image_att,
				   u32 image_index)
{
	u32 buf_size = 0, param, resp = 0, resp_param = 0;
	int rc;

	param = DRV_MB_PARAM_BIST_NVM_TEST_IMAGE_BY_INDEX <<
		DRV_MB_PARAM_BIST_TEST_INDEX_SHIFT;
	param |= image_index << DRV_MB_PARAM_BIST_TEST_IMAGE_INDEX_SHIFT;

	rc = qed_mcp_nvm_rd_cmd(p_hwfn, p_ptt,
				DRV_MSG_CODE_BIST_TEST, param,
				&resp, &resp_param,
				&buf_size,
				(u32 *)p_image_att);
	if (rc)
		return rc;

	if (((resp & FW_MSG_CODE_MASK) != FW_MSG_CODE_OK) ||
	    (p_image_att->return_code != 1))
		rc = -EINVAL;

	return rc;
}