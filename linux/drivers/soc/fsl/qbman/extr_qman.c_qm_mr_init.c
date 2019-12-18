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
struct TYPE_2__ {scalar_t__ ce; } ;
struct qm_mr {int pi; int ci; int ithresh; int pmode; int cmode; int /*<<< orphan*/  vbit; int /*<<< orphan*/  fill; scalar_t__ ring; scalar_t__ cursor; } ;
struct qm_portal {TYPE_1__ addr; struct qm_mr mr; } ;
typedef  enum qm_mr_pmode { ____Placeholder_qm_mr_pmode } qm_mr_pmode ;
typedef  enum qm_mr_cmode { ____Placeholder_qm_mr_cmode } qm_mr_cmode ;

/* Variables and functions */
 scalar_t__ QM_CL_MR ; 
 int QM_MR_SIZE ; 
 int /*<<< orphan*/  QM_MR_VERB_VBIT ; 
 int /*<<< orphan*/  QM_REG_CFG ; 
 int /*<<< orphan*/  QM_REG_MR_CI_CINH ; 
 int /*<<< orphan*/  QM_REG_MR_ITR ; 
 int /*<<< orphan*/  QM_REG_MR_PI_CINH ; 
 int /*<<< orphan*/  dpaa_cyc_diff (int,int,int) ; 
 int qm_in (struct qm_portal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_out (struct qm_portal*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int qm_mr_init(struct qm_portal *portal, enum qm_mr_pmode pmode,
			     enum qm_mr_cmode cmode)
{
	struct qm_mr *mr = &portal->mr;
	u32 cfg;

	mr->ring = portal->addr.ce + QM_CL_MR;
	mr->pi = qm_in(portal, QM_REG_MR_PI_CINH) & (QM_MR_SIZE - 1);
	mr->ci = qm_in(portal, QM_REG_MR_CI_CINH) & (QM_MR_SIZE - 1);
	mr->cursor = mr->ring + mr->ci;
	mr->fill = dpaa_cyc_diff(QM_MR_SIZE, mr->ci, mr->pi);
	mr->vbit = (qm_in(portal, QM_REG_MR_PI_CINH) & QM_MR_SIZE)
		? QM_MR_VERB_VBIT : 0;
	mr->ithresh = qm_in(portal, QM_REG_MR_ITR);
#ifdef CONFIG_FSL_DPAA_CHECKING
	mr->pmode = pmode;
	mr->cmode = cmode;
#endif
	cfg = (qm_in(portal, QM_REG_CFG) & 0xfffff0ff) |
	      ((cmode & 1) << 8);	/* QCSP_CFG:MM */
	qm_out(portal, QM_REG_CFG, cfg);
	return 0;
}