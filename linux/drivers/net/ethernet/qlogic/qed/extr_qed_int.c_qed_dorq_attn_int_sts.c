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
struct qed_hwfn {int /*<<< orphan*/  cdev; struct qed_ptt* p_dpc_ptt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DORQ_REG_DB_DROP_DETAILS ; 
 int /*<<< orphan*/  DORQ_REG_DB_DROP_DETAILS_ADDRESS ; 
 int /*<<< orphan*/  DORQ_REG_DB_DROP_DETAILS_REASON ; 
 int /*<<< orphan*/  DORQ_REG_DB_DROP_DETAILS_REL ; 
 int /*<<< orphan*/  DORQ_REG_DB_DROP_REASON ; 
 int /*<<< orphan*/  DORQ_REG_INT_STS ; 
 int DORQ_REG_INT_STS_DB_DROP ; 
 int DORQ_REG_INT_STS_DORQ_FIFO_AFULL ; 
 int DORQ_REG_INT_STS_DORQ_FIFO_OVFL_ERR ; 
 int /*<<< orphan*/  DORQ_REG_INT_STS_WR ; 
 int /*<<< orphan*/  DP_INFO (struct qed_hwfn*,char*) ; 
 int /*<<< orphan*/  DP_NOTICE (int /*<<< orphan*/ ,char*,int,...) ; 
 int EINVAL ; 
 int GET_FIELD (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QED_DORQ_ATTENTION_OPAQUE ; 
 int QED_DORQ_ATTENTION_REASON_MASK ; 
 int /*<<< orphan*/  QED_DORQ_ATTENTION_SIZE ; 
 int qed_rd (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qed_dorq_attn_int_sts(struct qed_hwfn *p_hwfn)
{
	u32 int_sts, first_drop_reason, details, address, all_drops_reason;
	struct qed_ptt *p_ptt = p_hwfn->p_dpc_ptt;

	/* int_sts may be zero since all PFs were interrupted for doorbell
	 * overflow but another one already handled it. Can abort here. If
	 * This PF also requires overflow recovery we will be interrupted again.
	 * The masked almost full indication may also be set. Ignoring.
	 */
	int_sts = qed_rd(p_hwfn, p_ptt, DORQ_REG_INT_STS);
	if (!(int_sts & ~DORQ_REG_INT_STS_DORQ_FIFO_AFULL))
		return 0;

	DP_NOTICE(p_hwfn->cdev, "DORQ attention. int_sts was %x\n", int_sts);

	/* check if db_drop or overflow happened */
	if (int_sts & (DORQ_REG_INT_STS_DB_DROP |
		       DORQ_REG_INT_STS_DORQ_FIFO_OVFL_ERR)) {
		/* Obtain data about db drop/overflow */
		first_drop_reason = qed_rd(p_hwfn, p_ptt,
					   DORQ_REG_DB_DROP_REASON) &
		    QED_DORQ_ATTENTION_REASON_MASK;
		details = qed_rd(p_hwfn, p_ptt, DORQ_REG_DB_DROP_DETAILS);
		address = qed_rd(p_hwfn, p_ptt,
				 DORQ_REG_DB_DROP_DETAILS_ADDRESS);
		all_drops_reason = qed_rd(p_hwfn, p_ptt,
					  DORQ_REG_DB_DROP_DETAILS_REASON);

		/* Log info */
		DP_NOTICE(p_hwfn->cdev,
			  "Doorbell drop occurred\n"
			  "Address\t\t0x%08x\t(second BAR address)\n"
			  "FID\t\t0x%04x\t\t(Opaque FID)\n"
			  "Size\t\t0x%04x\t\t(in bytes)\n"
			  "1st drop reason\t0x%08x\t(details on first drop since last handling)\n"
			  "Sticky reasons\t0x%08x\t(all drop reasons since last handling)\n",
			  address,
			  GET_FIELD(details, QED_DORQ_ATTENTION_OPAQUE),
			  GET_FIELD(details, QED_DORQ_ATTENTION_SIZE) * 4,
			  first_drop_reason, all_drops_reason);

		/* Clear the doorbell drop details and prepare for next drop */
		qed_wr(p_hwfn, p_ptt, DORQ_REG_DB_DROP_DETAILS_REL, 0);

		/* Mark interrupt as handled (note: even if drop was due to a different
		 * reason than overflow we mark as handled)
		 */
		qed_wr(p_hwfn,
		       p_ptt,
		       DORQ_REG_INT_STS_WR,
		       DORQ_REG_INT_STS_DB_DROP |
		       DORQ_REG_INT_STS_DORQ_FIFO_OVFL_ERR);

		/* If there are no indications other than drop indications, success */
		if ((int_sts & ~(DORQ_REG_INT_STS_DB_DROP |
				 DORQ_REG_INT_STS_DORQ_FIFO_OVFL_ERR |
				 DORQ_REG_INT_STS_DORQ_FIFO_AFULL)) == 0)
			return 0;
	}

	/* Some other indication was present - non recoverable */
	DP_INFO(p_hwfn, "DORQ fatal attention\n");

	return -EINVAL;
}