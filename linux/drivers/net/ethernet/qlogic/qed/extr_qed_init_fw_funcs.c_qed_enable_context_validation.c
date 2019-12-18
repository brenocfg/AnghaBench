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
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDU_REG_CCFC_CTX_VALID0 ; 
 int /*<<< orphan*/  CDU_REG_CCFC_CTX_VALID1 ; 
 int /*<<< orphan*/  CDU_REG_TCFC_CTX_VALID0 ; 
 int CDU_VALIDATION_DEFAULT_CFG ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int) ; 

void qed_enable_context_validation(struct qed_hwfn *p_hwfn,
				   struct qed_ptt *p_ptt)
{
	u32 ctx_validation;

	/* Enable validation for connection region 3: CCFC_CTX_VALID0[31:24] */
	ctx_validation = CDU_VALIDATION_DEFAULT_CFG << 24;
	qed_wr(p_hwfn, p_ptt, CDU_REG_CCFC_CTX_VALID0, ctx_validation);

	/* Enable validation for connection region 5: CCFC_CTX_VALID1[15:8] */
	ctx_validation = CDU_VALIDATION_DEFAULT_CFG << 8;
	qed_wr(p_hwfn, p_ptt, CDU_REG_CCFC_CTX_VALID1, ctx_validation);

	/* Enable validation for connection region 1: TCFC_CTX_VALID0[15:8] */
	ctx_validation = CDU_VALIDATION_DEFAULT_CFG << 8;
	qed_wr(p_hwfn, p_ptt, CDU_REG_TCFC_CTX_VALID0, ctx_validation);
}