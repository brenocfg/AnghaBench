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
struct qm_eqcr {scalar_t__ pmode; int vbit; scalar_t__ busy; int /*<<< orphan*/  available; struct qm_eqcr_entry* cursor; } ;
struct qm_portal {struct qm_eqcr eqcr; } ;
struct qm_eqcr_entry {int _ncw_verb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA_ASSERT (int) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 int /*<<< orphan*/  dpaa_flush (struct qm_eqcr_entry*) ; 
 int /*<<< orphan*/  eqcr_commit_checks (struct qm_eqcr*) ; 
 int /*<<< orphan*/  eqcr_inc (struct qm_eqcr*) ; 
 scalar_t__ qm_eqcr_pvb ; 

__attribute__((used)) static inline void qm_eqcr_pvb_commit(struct qm_portal *portal, u8 myverb)
{
	struct qm_eqcr *eqcr = &portal->eqcr;
	struct qm_eqcr_entry *eqcursor;

	eqcr_commit_checks(eqcr);
	DPAA_ASSERT(eqcr->pmode == qm_eqcr_pvb);
	dma_wmb();
	eqcursor = eqcr->cursor;
	eqcursor->_ncw_verb = myverb | eqcr->vbit;
	dpaa_flush(eqcursor);
	eqcr_inc(eqcr);
	eqcr->available--;
#ifdef CONFIG_FSL_DPAA_CHECKING
	eqcr->busy = 0;
#endif
}