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
struct qm_eqcr {int busy; struct qm_eqcr_entry* cursor; int /*<<< orphan*/  available; } ;
struct qm_portal {struct qm_eqcr eqcr; } ;
struct qm_eqcr_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA_ASSERT (int) ; 
 int /*<<< orphan*/  dpaa_zero (struct qm_eqcr_entry*) ; 

__attribute__((used)) static inline struct qm_eqcr_entry *qm_eqcr_start_no_stash(struct qm_portal
								 *portal)
{
	struct qm_eqcr *eqcr = &portal->eqcr;

	DPAA_ASSERT(!eqcr->busy);
	if (!eqcr->available)
		return NULL;

#ifdef CONFIG_FSL_DPAA_CHECKING
	eqcr->busy = 1;
#endif
	dpaa_zero(eqcr->cursor);
	return eqcr->cursor;
}