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
typedef  int /*<<< orphan*/  u32 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRS_ETH_VXLAN_NO_L2_ENABLE_OFFSET ; 
 scalar_t__ PRS_ETH_VXLAN_NO_L2_OUTPUT_FORMAT ; 
 int /*<<< orphan*/  PRS_REG_MSG_INFO ; 
 int /*<<< orphan*/  PRS_REG_OUTPUT_FORMAT_4_0_BB_K2 ; 
 int /*<<< orphan*/  qed_rd (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void qed_set_vxlan_no_l2_enable(struct qed_hwfn *p_hwfn,
				struct qed_ptt *p_ptt, bool enable)
{
	u32 reg_val, cfg_mask;

	/* read PRS config register */
	reg_val = qed_rd(p_hwfn, p_ptt, PRS_REG_MSG_INFO);

	/* set VXLAN_NO_L2_ENABLE mask */
	cfg_mask = BIT(PRS_ETH_VXLAN_NO_L2_ENABLE_OFFSET);

	if (enable) {
		/* set VXLAN_NO_L2_ENABLE flag */
		reg_val |= cfg_mask;

		/* update PRS FIC  register */
		qed_wr(p_hwfn,
		       p_ptt,
		       PRS_REG_OUTPUT_FORMAT_4_0_BB_K2,
		       (u32)PRS_ETH_VXLAN_NO_L2_OUTPUT_FORMAT);
	} else {
		/* clear VXLAN_NO_L2_ENABLE flag */
		reg_val &= ~cfg_mask;
	}

	/* write PRS config register */
	qed_wr(p_hwfn, p_ptt, PRS_REG_MSG_INFO, reg_val);
}