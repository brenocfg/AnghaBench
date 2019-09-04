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
typedef  int /*<<< orphan*/  u16 ;
struct qed_hwfn {int /*<<< orphan*/  p_dpc_ptt; int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DORQ_REG_DB_DROP_DETAILS ; 
 int /*<<< orphan*/  DORQ_REG_DB_DROP_DETAILS_ADDRESS ; 
 int /*<<< orphan*/  DORQ_REG_DB_DROP_REASON ; 
 int /*<<< orphan*/  DP_INFO (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int,int) ; 
 int EINVAL ; 
 int GET_FIELD (int,int /*<<< orphan*/ ) ; 
 int QED_DORQ_ATTENTION_OPAQUE_MASK ; 
 int QED_DORQ_ATTENTION_REASON_MASK ; 
 int /*<<< orphan*/  QED_DORQ_ATTENTION_SIZE ; 
 int qed_rd (struct qed_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qed_dorq_attn_cb(struct qed_hwfn *p_hwfn)
{
	u32 reason;

	reason = qed_rd(p_hwfn, p_hwfn->p_dpc_ptt, DORQ_REG_DB_DROP_REASON) &
			QED_DORQ_ATTENTION_REASON_MASK;
	if (reason) {
		u32 details = qed_rd(p_hwfn, p_hwfn->p_dpc_ptt,
				     DORQ_REG_DB_DROP_DETAILS);

		DP_INFO(p_hwfn->cdev,
			"DORQ db_drop: address 0x%08x Opaque FID 0x%04x Size [bytes] 0x%08x Reason: 0x%08x\n",
			qed_rd(p_hwfn, p_hwfn->p_dpc_ptt,
			       DORQ_REG_DB_DROP_DETAILS_ADDRESS),
			(u16)(details & QED_DORQ_ATTENTION_OPAQUE_MASK),
			GET_FIELD(details, QED_DORQ_ATTENTION_SIZE) * 4,
			reason);
	}

	return -EINVAL;
}