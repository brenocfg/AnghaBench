#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct qed_ptt {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  overflow; } ;
struct qed_hwfn {int /*<<< orphan*/  db_bar_no_edpm; TYPE_1__ db_recovery_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DORQ_REG_PF_OVFL_STICKY ; 
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  QED_OVERFLOW_BIT ; 
 int qed_db_rec_flush_queue (struct qed_hwfn*,struct qed_ptt*) ; 
 int /*<<< orphan*/  qed_db_recovery_execute (struct qed_hwfn*) ; 
 scalar_t__ qed_rd (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int qed_db_rec_handler(struct qed_hwfn *p_hwfn, struct qed_ptt *p_ptt)
{
	u32 attn_ovfl, cur_ovfl;
	int rc;

	attn_ovfl = test_and_clear_bit(QED_OVERFLOW_BIT,
				       &p_hwfn->db_recovery_info.overflow);
	cur_ovfl = qed_rd(p_hwfn, p_ptt, DORQ_REG_PF_OVFL_STICKY);
	if (!cur_ovfl && !attn_ovfl)
		return 0;

	DP_NOTICE(p_hwfn, "PF Overflow sticky: attn %u current %u\n",
		  attn_ovfl, cur_ovfl);

	if (cur_ovfl && !p_hwfn->db_bar_no_edpm) {
		rc = qed_db_rec_flush_queue(p_hwfn, p_ptt);
		if (rc)
			return rc;
	}

	/* Release overflow sticky indication (stop silently dropping everything) */
	qed_wr(p_hwfn, p_ptt, DORQ_REG_PF_OVFL_STICKY, 0x0);

	/* Repeat all last doorbells (doorbell drop recovery) */
	qed_db_recovery_execute(p_hwfn);

	return 0;
}