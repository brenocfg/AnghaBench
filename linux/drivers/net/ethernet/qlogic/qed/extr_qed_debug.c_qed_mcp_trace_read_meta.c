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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;
typedef  int /*<<< orphan*/  signature ;
typedef  enum dbg_status { ____Placeholder_dbg_status } dbg_status ;

/* Variables and functions */
 int DBG_STATUS_INVALID_TRACE_SIGNATURE ; 
 int DBG_STATUS_OK ; 
 scalar_t__ NVM_MAGIC_VALUE ; 
 int qed_nvram_read (struct qed_hwfn*,struct qed_ptt*,scalar_t__,scalar_t__,scalar_t__*) ; 
 scalar_t__ qed_read_unaligned_dword (scalar_t__*) ; 

__attribute__((used)) static enum dbg_status qed_mcp_trace_read_meta(struct qed_hwfn *p_hwfn,
					       struct qed_ptt *p_ptt,
					       u32 nvram_offset_in_bytes,
					       u32 size_in_bytes, u32 *buf)
{
	u8 modules_num, module_len, i, *byte_buf = (u8 *)buf;
	enum dbg_status status;
	u32 signature;

	/* Read meta data from NVRAM */
	status = qed_nvram_read(p_hwfn,
				p_ptt,
				nvram_offset_in_bytes, size_in_bytes, buf);
	if (status != DBG_STATUS_OK)
		return status;

	/* Extract and check first signature */
	signature = qed_read_unaligned_dword(byte_buf);
	byte_buf += sizeof(signature);
	if (signature != NVM_MAGIC_VALUE)
		return DBG_STATUS_INVALID_TRACE_SIGNATURE;

	/* Extract number of modules */
	modules_num = *(byte_buf++);

	/* Skip all modules */
	for (i = 0; i < modules_num; i++) {
		module_len = *(byte_buf++);
		byte_buf += module_len;
	}

	/* Extract and check second signature */
	signature = qed_read_unaligned_dword(byte_buf);
	byte_buf += sizeof(signature);
	if (signature != NVM_MAGIC_VALUE)
		return DBG_STATUS_INVALID_TRACE_SIGNATURE;

	return DBG_STATUS_OK;
}