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
struct mcp_file_att {int nvm_start_addr; int len; } ;
typedef  enum dbg_status { ____Placeholder_dbg_status } dbg_status ;

/* Variables and functions */
 int DBG_STATUS_NON_ALIGNED_NVRAM_IMAGE ; 
 int DBG_STATUS_NVRAM_GET_IMAGE_FAILED ; 
 int DBG_STATUS_OK ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  DRV_MSG_CODE_NVM_GET_FILE_ATT ; 
 int FW_MSG_CODE_MASK ; 
 int FW_MSG_CODE_NVM_OK ; 
 int /*<<< orphan*/  QED_MSG_DEBUG ; 
 int qed_mcp_nvm_rd_cmd (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int,int*,int*,int*,int*) ; 

__attribute__((used)) static enum dbg_status qed_find_nvram_image(struct qed_hwfn *p_hwfn,
					    struct qed_ptt *p_ptt,
					    u32 image_type,
					    u32 *nvram_offset_bytes,
					    u32 *nvram_size_bytes)
{
	u32 ret_mcp_resp, ret_mcp_param, ret_txn_size;
	struct mcp_file_att file_att;
	int nvm_result;

	/* Call NVRAM get file command */
	nvm_result = qed_mcp_nvm_rd_cmd(p_hwfn,
					p_ptt,
					DRV_MSG_CODE_NVM_GET_FILE_ATT,
					image_type,
					&ret_mcp_resp,
					&ret_mcp_param,
					&ret_txn_size, (u32 *)&file_att);

	/* Check response */
	if (nvm_result ||
	    (ret_mcp_resp & FW_MSG_CODE_MASK) != FW_MSG_CODE_NVM_OK)
		return DBG_STATUS_NVRAM_GET_IMAGE_FAILED;

	/* Update return values */
	*nvram_offset_bytes = file_att.nvm_start_addr;
	*nvram_size_bytes = file_att.len;

	DP_VERBOSE(p_hwfn,
		   QED_MSG_DEBUG,
		   "find_nvram_image: found NVRAM image of type %d in NVRAM offset %d bytes with size %d bytes\n",
		   image_type, *nvram_offset_bytes, *nvram_size_bytes);

	/* Check alignment */
	if (*nvram_size_bytes & 0x3)
		return DBG_STATUS_NON_ALIGNED_NVRAM_IMAGE;

	return DBG_STATUS_OK;
}