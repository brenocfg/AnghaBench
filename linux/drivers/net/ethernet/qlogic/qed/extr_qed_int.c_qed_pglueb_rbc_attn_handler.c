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
typedef  int u32 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,int,...) ; 
 scalar_t__ GET_FIELD (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGLUE_ATTENTION_DETAILS2_BME ; 
 int /*<<< orphan*/  PGLUE_ATTENTION_DETAILS2_FID_EN ; 
 int /*<<< orphan*/  PGLUE_ATTENTION_DETAILS2_WAS_ERR ; 
 int /*<<< orphan*/  PGLUE_ATTENTION_DETAILS_PFID ; 
 int /*<<< orphan*/  PGLUE_ATTENTION_DETAILS_VFID ; 
 int /*<<< orphan*/  PGLUE_ATTENTION_DETAILS_VF_VALID ; 
 int PGLUE_ATTENTION_ICPL_VALID ; 
 int PGLUE_ATTENTION_ILT_VALID ; 
 int PGLUE_ATTENTION_RD_VALID ; 
 int PGLUE_ATTENTION_VALID ; 
 int PGLUE_ATTENTION_ZLR_VALID ; 
 int /*<<< orphan*/  PGLUE_B_REG_LATCHED_ERRORS_CLR ; 
 int /*<<< orphan*/  PGLUE_B_REG_MASTER_ZLR_ERR_ADD_31_0 ; 
 int /*<<< orphan*/  PGLUE_B_REG_MASTER_ZLR_ERR_ADD_63_32 ; 
 int /*<<< orphan*/  PGLUE_B_REG_MASTER_ZLR_ERR_DETAILS ; 
 int /*<<< orphan*/  PGLUE_B_REG_TX_ERR_RD_ADD_31_0 ; 
 int /*<<< orphan*/  PGLUE_B_REG_TX_ERR_RD_ADD_63_32 ; 
 int /*<<< orphan*/  PGLUE_B_REG_TX_ERR_RD_DETAILS ; 
 int /*<<< orphan*/  PGLUE_B_REG_TX_ERR_RD_DETAILS2 ; 
 int /*<<< orphan*/  PGLUE_B_REG_TX_ERR_WR_ADD_31_0 ; 
 int /*<<< orphan*/  PGLUE_B_REG_TX_ERR_WR_ADD_63_32 ; 
 int /*<<< orphan*/  PGLUE_B_REG_TX_ERR_WR_DETAILS ; 
 int /*<<< orphan*/  PGLUE_B_REG_TX_ERR_WR_DETAILS2 ; 
 int /*<<< orphan*/  PGLUE_B_REG_TX_ERR_WR_DETAILS_ICPL ; 
 int /*<<< orphan*/  PGLUE_B_REG_VF_ILT_ERR_ADD_31_0 ; 
 int /*<<< orphan*/  PGLUE_B_REG_VF_ILT_ERR_ADD_63_32 ; 
 int /*<<< orphan*/  PGLUE_B_REG_VF_ILT_ERR_DETAILS ; 
 int /*<<< orphan*/  PGLUE_B_REG_VF_ILT_ERR_DETAILS2 ; 
 int qed_rd (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int qed_pglueb_rbc_attn_handler(struct qed_hwfn *p_hwfn,
				struct qed_ptt *p_ptt)
{
	u32 tmp;

	tmp = qed_rd(p_hwfn, p_ptt, PGLUE_B_REG_TX_ERR_WR_DETAILS2);
	if (tmp & PGLUE_ATTENTION_VALID) {
		u32 addr_lo, addr_hi, details;

		addr_lo = qed_rd(p_hwfn, p_ptt,
				 PGLUE_B_REG_TX_ERR_WR_ADD_31_0);
		addr_hi = qed_rd(p_hwfn, p_ptt,
				 PGLUE_B_REG_TX_ERR_WR_ADD_63_32);
		details = qed_rd(p_hwfn, p_ptt,
				 PGLUE_B_REG_TX_ERR_WR_DETAILS);

		DP_NOTICE(p_hwfn,
			  "Illegal write by chip to [%08x:%08x] blocked.\n"
			  "Details: %08x [PFID %02x, VFID %02x, VF_VALID %02x]\n"
			  "Details2 %08x [Was_error %02x BME deassert %02x FID_enable deassert %02x]\n",
			  addr_hi, addr_lo, details,
			  (u8)GET_FIELD(details, PGLUE_ATTENTION_DETAILS_PFID),
			  (u8)GET_FIELD(details, PGLUE_ATTENTION_DETAILS_VFID),
			  GET_FIELD(details,
				    PGLUE_ATTENTION_DETAILS_VF_VALID) ? 1 : 0,
			  tmp,
			  GET_FIELD(tmp,
				    PGLUE_ATTENTION_DETAILS2_WAS_ERR) ? 1 : 0,
			  GET_FIELD(tmp,
				    PGLUE_ATTENTION_DETAILS2_BME) ? 1 : 0,
			  GET_FIELD(tmp,
				    PGLUE_ATTENTION_DETAILS2_FID_EN) ? 1 : 0);
	}

	tmp = qed_rd(p_hwfn, p_ptt, PGLUE_B_REG_TX_ERR_RD_DETAILS2);
	if (tmp & PGLUE_ATTENTION_RD_VALID) {
		u32 addr_lo, addr_hi, details;

		addr_lo = qed_rd(p_hwfn, p_ptt,
				 PGLUE_B_REG_TX_ERR_RD_ADD_31_0);
		addr_hi = qed_rd(p_hwfn, p_ptt,
				 PGLUE_B_REG_TX_ERR_RD_ADD_63_32);
		details = qed_rd(p_hwfn, p_ptt,
				 PGLUE_B_REG_TX_ERR_RD_DETAILS);

		DP_NOTICE(p_hwfn,
			  "Illegal read by chip from [%08x:%08x] blocked.\n"
			  "Details: %08x [PFID %02x, VFID %02x, VF_VALID %02x]\n"
			  "Details2 %08x [Was_error %02x BME deassert %02x FID_enable deassert %02x]\n",
			  addr_hi, addr_lo, details,
			  (u8)GET_FIELD(details, PGLUE_ATTENTION_DETAILS_PFID),
			  (u8)GET_FIELD(details, PGLUE_ATTENTION_DETAILS_VFID),
			  GET_FIELD(details,
				    PGLUE_ATTENTION_DETAILS_VF_VALID) ? 1 : 0,
			  tmp,
			  GET_FIELD(tmp,
				    PGLUE_ATTENTION_DETAILS2_WAS_ERR) ? 1 : 0,
			  GET_FIELD(tmp,
				    PGLUE_ATTENTION_DETAILS2_BME) ? 1 : 0,
			  GET_FIELD(tmp,
				    PGLUE_ATTENTION_DETAILS2_FID_EN) ? 1 : 0);
	}

	tmp = qed_rd(p_hwfn, p_ptt, PGLUE_B_REG_TX_ERR_WR_DETAILS_ICPL);
	if (tmp & PGLUE_ATTENTION_ICPL_VALID)
		DP_NOTICE(p_hwfn, "ICPL error - %08x\n", tmp);

	tmp = qed_rd(p_hwfn, p_ptt, PGLUE_B_REG_MASTER_ZLR_ERR_DETAILS);
	if (tmp & PGLUE_ATTENTION_ZLR_VALID) {
		u32 addr_hi, addr_lo;

		addr_lo = qed_rd(p_hwfn, p_ptt,
				 PGLUE_B_REG_MASTER_ZLR_ERR_ADD_31_0);
		addr_hi = qed_rd(p_hwfn, p_ptt,
				 PGLUE_B_REG_MASTER_ZLR_ERR_ADD_63_32);

		DP_NOTICE(p_hwfn, "ZLR error - %08x [Address %08x:%08x]\n",
			  tmp, addr_hi, addr_lo);
	}

	tmp = qed_rd(p_hwfn, p_ptt, PGLUE_B_REG_VF_ILT_ERR_DETAILS2);
	if (tmp & PGLUE_ATTENTION_ILT_VALID) {
		u32 addr_hi, addr_lo, details;

		addr_lo = qed_rd(p_hwfn, p_ptt,
				 PGLUE_B_REG_VF_ILT_ERR_ADD_31_0);
		addr_hi = qed_rd(p_hwfn, p_ptt,
				 PGLUE_B_REG_VF_ILT_ERR_ADD_63_32);
		details = qed_rd(p_hwfn, p_ptt,
				 PGLUE_B_REG_VF_ILT_ERR_DETAILS);

		DP_NOTICE(p_hwfn,
			  "ILT error - Details %08x Details2 %08x [Address %08x:%08x]\n",
			  details, tmp, addr_hi, addr_lo);
	}

	/* Clear the indications */
	qed_wr(p_hwfn, p_ptt, PGLUE_B_REG_LATCHED_ERRORS_CLR, BIT(2));

	return 0;
}