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
typedef  int /*<<< orphan*/  u32 ;
struct qed_ptt {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  overflow; } ;
struct qed_hwfn {int /*<<< orphan*/  db_bar_no_edpm; TYPE_1__ db_recovery_info; struct qed_ptt* p_dpc_ptt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DORQ_REG_PF_OVFL_STICKY ; 
 int /*<<< orphan*/  QED_OVERFLOW_BIT ; 
 int qed_db_rec_flush_queue (struct qed_hwfn*,struct qed_ptt*) ; 
 int /*<<< orphan*/  qed_periodic_db_rec_start (struct qed_hwfn*) ; 
 int /*<<< orphan*/  qed_rd (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qed_dorq_attn_overflow(struct qed_hwfn *p_hwfn)
{
	struct qed_ptt *p_ptt = p_hwfn->p_dpc_ptt;
	u32 overflow;
	int rc;

	overflow = qed_rd(p_hwfn, p_ptt, DORQ_REG_PF_OVFL_STICKY);
	if (!overflow)
		goto out;

	/* Run PF doorbell recovery in next periodic handler */
	set_bit(QED_OVERFLOW_BIT, &p_hwfn->db_recovery_info.overflow);

	if (!p_hwfn->db_bar_no_edpm) {
		rc = qed_db_rec_flush_queue(p_hwfn, p_ptt);
		if (rc)
			goto out;
	}

	qed_wr(p_hwfn, p_ptt, DORQ_REG_PF_OVFL_STICKY, 0x0);
out:
	/* Schedule the handler even if overflow was not detected */
	qed_periodic_db_rec_start(p_hwfn);
}