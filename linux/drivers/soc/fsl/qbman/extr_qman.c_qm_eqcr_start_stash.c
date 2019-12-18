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
typedef  int u8 ;
struct qm_eqcr {int busy; int available; int ci; struct qm_eqcr_entry* cursor; } ;
struct qm_portal {struct qm_eqcr eqcr; } ;
struct qm_eqcr_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA_ASSERT (int) ; 
 int /*<<< orphan*/  QM_CL_EQCR_CI_CENA ; 
 int QM_EQCR_SIZE ; 
 int dpaa_cyc_diff (int,int,int) ; 
 int /*<<< orphan*/  dpaa_zero (struct qm_eqcr_entry*) ; 
 int qm_ce_in (struct qm_portal*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct qm_eqcr_entry *qm_eqcr_start_stash(struct qm_portal
								*portal)
{
	struct qm_eqcr *eqcr = &portal->eqcr;
	u8 diff, old_ci;

	DPAA_ASSERT(!eqcr->busy);
	if (!eqcr->available) {
		old_ci = eqcr->ci;
		eqcr->ci = qm_ce_in(portal, QM_CL_EQCR_CI_CENA) &
			   (QM_EQCR_SIZE - 1);
		diff = dpaa_cyc_diff(QM_EQCR_SIZE, old_ci, eqcr->ci);
		eqcr->available += diff;
		if (!diff)
			return NULL;
	}
#ifdef CONFIG_FSL_DPAA_CHECKING
	eqcr->busy = 1;
#endif
	dpaa_zero(eqcr->cursor);
	return eqcr->cursor;
}