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
union qm_mc_result {int /*<<< orphan*/  verb; } ;
struct qm_mc {int rridx; scalar_t__ state; int /*<<< orphan*/  vbit; union qm_mc_result* rr; } ;
struct qm_portal {struct qm_mc mc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA_ASSERT (int) ; 
 int /*<<< orphan*/  QM_MCC_VERB_VBIT ; 
 int /*<<< orphan*/  dpaa_invalidate_touch_ro (union qm_mc_result*) ; 
 scalar_t__ qman_mc_hw ; 
 scalar_t__ qman_mc_idle ; 

__attribute__((used)) static inline union qm_mc_result *qm_mc_result(struct qm_portal *portal)
{
	struct qm_mc *mc = &portal->mc;
	union qm_mc_result *rr = mc->rr + mc->rridx;

	DPAA_ASSERT(mc->state == qman_mc_hw);
	/*
	 *  The inactive response register's verb byte always returns zero until
	 * its command is submitted and completed. This includes the valid-bit,
	 * in case you were wondering...
	 */
	if (!rr->verb) {
		dpaa_invalidate_touch_ro(rr);
		return NULL;
	}
	mc->rridx ^= 1;
	mc->vbit ^= QM_MCC_VERB_VBIT;
#ifdef CONFIG_FSL_DPAA_CHECKING
	mc->state = qman_mc_idle;
#endif
	return rr;
}