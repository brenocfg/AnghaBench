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
typedef  int u16 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int /*<<< orphan*/  rel_pf_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int,int) ; 
 int EBUSY ; 
 int FINAL_CLEANUP_POLL_CNT ; 
 int /*<<< orphan*/  FINAL_CLEANUP_POLL_TIME ; 
 int GTT_BAR0_MAP_REG_USDM_RAM ; 
 int /*<<< orphan*/  QED_MSG_IOV ; 
 scalar_t__ REG_RD (struct qed_hwfn*,int) ; 
 int /*<<< orphan*/  REG_WR (struct qed_hwfn*,int,int /*<<< orphan*/ ) ; 
 int SDM_AGG_INT_COMP_PARAMS_AGG_INT_INDEX_SHIFT ; 
 int SDM_AGG_INT_COMP_PARAMS_AGG_VECTOR_BIT_SHIFT ; 
 int SDM_AGG_INT_COMP_PARAMS_AGG_VECTOR_ENABLE_SHIFT ; 
 int SDM_COMP_TYPE_AGG_INT ; 
 int SDM_OP_GEN_COMP_TYPE_SHIFT ; 
 int USTORM_FLR_FINAL_ACK_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSDM_REG_OPERATION_GEN ; 
 int X_FINAL_CLEANUP_AGG_INT ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int) ; 

int qed_final_cleanup(struct qed_hwfn *p_hwfn,
		      struct qed_ptt *p_ptt, u16 id, bool is_vf)
{
	u32 command = 0, addr, count = FINAL_CLEANUP_POLL_CNT;
	int rc = -EBUSY;

	addr = GTT_BAR0_MAP_REG_USDM_RAM +
		USTORM_FLR_FINAL_ACK_OFFSET(p_hwfn->rel_pf_id);

	if (is_vf)
		id += 0x10;

	command |= X_FINAL_CLEANUP_AGG_INT <<
		SDM_AGG_INT_COMP_PARAMS_AGG_INT_INDEX_SHIFT;
	command |= 1 << SDM_AGG_INT_COMP_PARAMS_AGG_VECTOR_ENABLE_SHIFT;
	command |= id << SDM_AGG_INT_COMP_PARAMS_AGG_VECTOR_BIT_SHIFT;
	command |= SDM_COMP_TYPE_AGG_INT << SDM_OP_GEN_COMP_TYPE_SHIFT;

	/* Make sure notification is not set before initiating final cleanup */
	if (REG_RD(p_hwfn, addr)) {
		DP_NOTICE(p_hwfn,
			  "Unexpected; Found final cleanup notification before initiating final cleanup\n");
		REG_WR(p_hwfn, addr, 0);
	}

	DP_VERBOSE(p_hwfn, QED_MSG_IOV,
		   "Sending final cleanup for PFVF[%d] [Command %08x]\n",
		   id, command);

	qed_wr(p_hwfn, p_ptt, XSDM_REG_OPERATION_GEN, command);

	/* Poll until completion */
	while (!REG_RD(p_hwfn, addr) && count--)
		msleep(FINAL_CLEANUP_POLL_TIME);

	if (REG_RD(p_hwfn, addr))
		rc = 0;
	else
		DP_NOTICE(p_hwfn,
			  "Failed to receive FW final cleanup notification\n");

	/* Cleanup afterwards */
	REG_WR(p_hwfn, addr, 0);

	return rc;
}