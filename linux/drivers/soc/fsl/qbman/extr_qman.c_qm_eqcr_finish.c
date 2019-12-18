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
typedef  scalar_t__ u8 ;
struct qm_eqcr {scalar_t__ ci; int /*<<< orphan*/  cursor; int /*<<< orphan*/  busy; } ;
struct qm_portal {struct qm_eqcr eqcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA_ASSERT (int) ; 
 int QM_EQCR_SIZE ; 
 int /*<<< orphan*/  QM_REG_EQCR_CI_CINH ; 
 int /*<<< orphan*/  QM_REG_EQCR_PI_CINH ; 
 scalar_t__ eqcr_ptr2idx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_crit (char*) ; 
 int qm_in (struct qm_portal*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void qm_eqcr_finish(struct qm_portal *portal)
{
	struct qm_eqcr *eqcr = &portal->eqcr;
	u8 pi = qm_in(portal, QM_REG_EQCR_PI_CINH) & (QM_EQCR_SIZE - 1);
	u8 ci = qm_in(portal, QM_REG_EQCR_CI_CINH) & (QM_EQCR_SIZE - 1);

	DPAA_ASSERT(!eqcr->busy);
	if (pi != eqcr_ptr2idx(eqcr->cursor))
		pr_crit("losing uncommitted EQCR entries\n");
	if (ci != eqcr->ci)
		pr_crit("missing existing EQCR completions\n");
	if (eqcr->ci != eqcr_ptr2idx(eqcr->cursor))
		pr_crit("EQCR destroyed unquiesced\n");
}