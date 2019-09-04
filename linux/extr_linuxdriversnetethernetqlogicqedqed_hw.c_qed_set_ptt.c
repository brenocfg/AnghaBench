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
struct qed_ptt {scalar_t__ hwfn_id; int /*<<< orphan*/  idx; } ;
struct qed_hwfn {scalar_t__ my_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ PXP_EXTERNAL_BAR_PF_WINDOW_SINGLE_SIZE ; 
 scalar_t__ qed_ptt_get_bar_addr (struct qed_ptt*) ; 
 scalar_t__ qed_ptt_get_hw_addr (struct qed_hwfn*,struct qed_ptt*) ; 
 int /*<<< orphan*/  qed_ptt_set_win (struct qed_hwfn*,struct qed_ptt*,scalar_t__) ; 

__attribute__((used)) static u32 qed_set_ptt(struct qed_hwfn *p_hwfn,
		       struct qed_ptt *p_ptt, u32 hw_addr)
{
	u32 win_hw_addr = qed_ptt_get_hw_addr(p_hwfn, p_ptt);
	u32 offset;

	offset = hw_addr - win_hw_addr;

	if (p_ptt->hwfn_id != p_hwfn->my_id)
		DP_NOTICE(p_hwfn,
			  "ptt[%d] of hwfn[%02x] is used by hwfn[%02x]!\n",
			  p_ptt->idx, p_ptt->hwfn_id, p_hwfn->my_id);

	/* Verify the address is within the window */
	if (hw_addr < win_hw_addr ||
	    offset >= PXP_EXTERNAL_BAR_PF_WINDOW_SINGLE_SIZE) {
		qed_ptt_set_win(p_hwfn, p_ptt, hw_addr);
		offset = 0;
	}

	return qed_ptt_get_bar_addr(p_ptt) + offset;
}