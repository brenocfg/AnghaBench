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
typedef  scalar_t__ u32 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;
typedef  enum dbg_status { ____Placeholder_dbg_status } dbg_status ;

/* Variables and functions */
 int DBG_STATUS_OK ; 
 int qed_dbg_dev_init (struct qed_hwfn*,struct qed_ptt*) ; 
 scalar_t__ qed_fw_asserts_dump (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  qed_update_blocks_reset_state (struct qed_hwfn*,struct qed_ptt*) ; 

enum dbg_status qed_dbg_fw_asserts_get_dump_buf_size(struct qed_hwfn *p_hwfn,
						     struct qed_ptt *p_ptt,
						     u32 *buf_size)
{
	enum dbg_status status = qed_dbg_dev_init(p_hwfn, p_ptt);

	*buf_size = 0;

	if (status != DBG_STATUS_OK)
		return status;

	/* Update reset state */
	qed_update_blocks_reset_state(p_hwfn, p_ptt);

	*buf_size = qed_fw_asserts_dump(p_hwfn, p_ptt, NULL, false);

	return DBG_STATUS_OK;
}