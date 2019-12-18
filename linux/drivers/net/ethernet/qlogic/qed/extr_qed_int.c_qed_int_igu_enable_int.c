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
typedef  int u32 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {TYPE_1__* cdev; } ;
typedef  enum qed_int_mode { ____Placeholder_qed_int_mode } qed_int_mode ;
struct TYPE_2__ {int int_mode; } ;

/* Variables and functions */
 int IGU_PF_CONF_ATTN_BIT_EN ; 
 int IGU_PF_CONF_FUNC_EN ; 
 int IGU_PF_CONF_INT_LINE_EN ; 
 int IGU_PF_CONF_MSI_MSIX_EN ; 
 int IGU_PF_CONF_SINGLE_ISR_EN ; 
 int /*<<< orphan*/  IGU_REG_PF_CONFIGURATION ; 
#define  QED_INT_MODE_INTA 131 
#define  QED_INT_MODE_MSI 130 
#define  QED_INT_MODE_MSIX 129 
#define  QED_INT_MODE_POLL 128 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int) ; 

void qed_int_igu_enable_int(struct qed_hwfn *p_hwfn,
			    struct qed_ptt *p_ptt, enum qed_int_mode int_mode)
{
	u32 igu_pf_conf = IGU_PF_CONF_FUNC_EN | IGU_PF_CONF_ATTN_BIT_EN;

	p_hwfn->cdev->int_mode = int_mode;
	switch (p_hwfn->cdev->int_mode) {
	case QED_INT_MODE_INTA:
		igu_pf_conf |= IGU_PF_CONF_INT_LINE_EN;
		igu_pf_conf |= IGU_PF_CONF_SINGLE_ISR_EN;
		break;

	case QED_INT_MODE_MSI:
		igu_pf_conf |= IGU_PF_CONF_MSI_MSIX_EN;
		igu_pf_conf |= IGU_PF_CONF_SINGLE_ISR_EN;
		break;

	case QED_INT_MODE_MSIX:
		igu_pf_conf |= IGU_PF_CONF_MSI_MSIX_EN;
		break;
	case QED_INT_MODE_POLL:
		break;
	}

	qed_wr(p_hwfn, p_ptt, IGU_REG_PF_CONFIGURATION, igu_pf_conf);
}