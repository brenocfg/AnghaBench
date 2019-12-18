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
struct qed_hwfn {int /*<<< orphan*/  p_dpc_ptt; int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (int /*<<< orphan*/ ,char*,int,int,char*,int,int /*<<< orphan*/ ,int,char*,int) ; 
 int GET_FIELD (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GRC_REG_TIMEOUT_ATTN_ACCESS_DATA_0 ; 
 int /*<<< orphan*/  GRC_REG_TIMEOUT_ATTN_ACCESS_DATA_1 ; 
 int /*<<< orphan*/  GRC_REG_TIMEOUT_ATTN_ACCESS_VALID ; 
 int /*<<< orphan*/  QED_GRC_ATTENTION_ADDRESS ; 
 int /*<<< orphan*/  QED_GRC_ATTENTION_MASTER ; 
 int /*<<< orphan*/  QED_GRC_ATTENTION_PF ; 
 int /*<<< orphan*/  QED_GRC_ATTENTION_PRIV ; 
 int QED_GRC_ATTENTION_PRIV_VF ; 
 int QED_GRC_ATTENTION_RDWR_BIT ; 
 int QED_GRC_ATTENTION_VALID_BIT ; 
 int /*<<< orphan*/  QED_GRC_ATTENTION_VF ; 
 int /*<<< orphan*/  attn_master_to_str (int) ; 
 int qed_rd (struct qed_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qed_grc_attn_cb(struct qed_hwfn *p_hwfn)
{
	u32 tmp, tmp2;

	/* We've already cleared the timeout interrupt register, so we learn
	 * of interrupts via the validity register
	 */
	tmp = qed_rd(p_hwfn, p_hwfn->p_dpc_ptt,
		     GRC_REG_TIMEOUT_ATTN_ACCESS_VALID);
	if (!(tmp & QED_GRC_ATTENTION_VALID_BIT))
		goto out;

	/* Read the GRC timeout information */
	tmp = qed_rd(p_hwfn, p_hwfn->p_dpc_ptt,
		     GRC_REG_TIMEOUT_ATTN_ACCESS_DATA_0);
	tmp2 = qed_rd(p_hwfn, p_hwfn->p_dpc_ptt,
		      GRC_REG_TIMEOUT_ATTN_ACCESS_DATA_1);

	DP_INFO(p_hwfn->cdev,
		"GRC timeout [%08x:%08x] - %s Address [%08x] [Master %s] [PF: %02x %s %02x]\n",
		tmp2, tmp,
		(tmp & QED_GRC_ATTENTION_RDWR_BIT) ? "Write to" : "Read from",
		GET_FIELD(tmp, QED_GRC_ATTENTION_ADDRESS) << 2,
		attn_master_to_str(GET_FIELD(tmp, QED_GRC_ATTENTION_MASTER)),
		GET_FIELD(tmp2, QED_GRC_ATTENTION_PF),
		(GET_FIELD(tmp2, QED_GRC_ATTENTION_PRIV) ==
		 QED_GRC_ATTENTION_PRIV_VF) ? "VF" : "(Irrelevant)",
		GET_FIELD(tmp2, QED_GRC_ATTENTION_VF));

out:
	/* Regardles of anything else, clean the validity bit */
	qed_wr(p_hwfn, p_hwfn->p_dpc_ptt,
	       GRC_REG_TIMEOUT_ATTN_ACCESS_VALID, 0);
	return 0;
}