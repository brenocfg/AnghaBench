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
typedef  scalar_t__ u32 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DORQ_REG_L2_EDPM_TUNNEL_NGE_ETH_EN_K2_E5 ; 
 int /*<<< orphan*/  DORQ_REG_L2_EDPM_TUNNEL_NGE_IP_EN_K2_E5 ; 
 int /*<<< orphan*/  NIG_REG_NGE_ETH_ENABLE ; 
 int /*<<< orphan*/  NIG_REG_NGE_IP_ENABLE ; 
 scalar_t__ PRS_ETH_OUTPUT_FORMAT ; 
 scalar_t__ PRS_ETH_TUNN_OUTPUT_FORMAT ; 
 int /*<<< orphan*/  PRS_REG_ENCAPSULATION_TYPE_EN ; 
 int /*<<< orphan*/  PRS_REG_ENCAPSULATION_TYPE_EN_ETH_OVER_GENEVE_ENABLE_SHIFT ; 
 int /*<<< orphan*/  PRS_REG_ENCAPSULATION_TYPE_EN_IP_OVER_GENEVE_ENABLE_SHIFT ; 
 int /*<<< orphan*/  PRS_REG_OUTPUT_FORMAT_4_0_BB_K2 ; 
 scalar_t__ QED_IS_BB_B0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TUNNEL_TYPE_ENABLE_BIT (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ qed_rd (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int) ; 

void qed_set_geneve_enable(struct qed_hwfn *p_hwfn,
			   struct qed_ptt *p_ptt,
			   bool eth_geneve_enable, bool ip_geneve_enable)
{
	u32 reg_val;
	u8 shift;

	/* Update PRS register */
	reg_val = qed_rd(p_hwfn, p_ptt, PRS_REG_ENCAPSULATION_TYPE_EN);
	shift = PRS_REG_ENCAPSULATION_TYPE_EN_ETH_OVER_GENEVE_ENABLE_SHIFT;
	SET_TUNNEL_TYPE_ENABLE_BIT(reg_val, shift, eth_geneve_enable);
	shift = PRS_REG_ENCAPSULATION_TYPE_EN_IP_OVER_GENEVE_ENABLE_SHIFT;
	SET_TUNNEL_TYPE_ENABLE_BIT(reg_val, shift, ip_geneve_enable);
	qed_wr(p_hwfn, p_ptt, PRS_REG_ENCAPSULATION_TYPE_EN, reg_val);
	if (reg_val) {
		reg_val =
		    qed_rd(p_hwfn, p_ptt, PRS_REG_OUTPUT_FORMAT_4_0_BB_K2);

		/* Update output  only if tunnel blocks not included. */
		if (reg_val == (u32)PRS_ETH_OUTPUT_FORMAT)
			qed_wr(p_hwfn, p_ptt, PRS_REG_OUTPUT_FORMAT_4_0_BB_K2,
			       (u32)PRS_ETH_TUNN_OUTPUT_FORMAT);
	}

	/* Update NIG register */
	qed_wr(p_hwfn, p_ptt, NIG_REG_NGE_ETH_ENABLE,
	       eth_geneve_enable ? 1 : 0);
	qed_wr(p_hwfn, p_ptt, NIG_REG_NGE_IP_ENABLE, ip_geneve_enable ? 1 : 0);

	/* EDPM with geneve tunnel not supported in BB */
	if (QED_IS_BB_B0(p_hwfn->cdev))
		return;

	/* Update DORQ registers */
	qed_wr(p_hwfn,
	       p_ptt,
	       DORQ_REG_L2_EDPM_TUNNEL_NGE_ETH_EN_K2_E5,
	       eth_geneve_enable ? 1 : 0);
	qed_wr(p_hwfn,
	       p_ptt,
	       DORQ_REG_L2_EDPM_TUNNEL_NGE_IP_EN_K2_E5,
	       ip_geneve_enable ? 1 : 0);
}