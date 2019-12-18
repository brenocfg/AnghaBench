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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u16 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int /*<<< orphan*/  hw_init_done; } ;
struct cau_sb_entry {int /*<<< orphan*/  params; } ;

/* Variables and functions */
 scalar_t__ CAU_REG_SB_VAR_MEMORY ; 
 int /*<<< orphan*/  CAU_SB_ENTRY_TIMER_RES0 ; 
 int /*<<< orphan*/  CAU_SB_ENTRY_TIMER_RES1 ; 
 int /*<<< orphan*/  DP_ERR (struct qed_hwfn*,char*,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qed_dmae_grc2host (struct qed_hwfn*,struct qed_ptt*,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int qed_dmae_host2grc (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *) ; 

int qed_int_set_timer_res(struct qed_hwfn *p_hwfn, struct qed_ptt *p_ptt,
			  u8 timer_res, u16 sb_id, bool tx)
{
	struct cau_sb_entry sb_entry;
	int rc;

	if (!p_hwfn->hw_init_done) {
		DP_ERR(p_hwfn, "hardware not initialized yet\n");
		return -EINVAL;
	}

	rc = qed_dmae_grc2host(p_hwfn, p_ptt, CAU_REG_SB_VAR_MEMORY +
			       sb_id * sizeof(u64),
			       (u64)(uintptr_t)&sb_entry, 2, NULL);
	if (rc) {
		DP_ERR(p_hwfn, "dmae_grc2host failed %d\n", rc);
		return rc;
	}

	if (tx)
		SET_FIELD(sb_entry.params, CAU_SB_ENTRY_TIMER_RES1, timer_res);
	else
		SET_FIELD(sb_entry.params, CAU_SB_ENTRY_TIMER_RES0, timer_res);

	rc = qed_dmae_host2grc(p_hwfn, p_ptt,
			       (u64)(uintptr_t)&sb_entry,
			       CAU_REG_SB_VAR_MEMORY +
			       sb_id * sizeof(u64), 2, NULL);
	if (rc) {
		DP_ERR(p_hwfn, "dmae_host2grc failed %d\n", rc);
		return rc;
	}

	return rc;
}