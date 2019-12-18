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
struct qm_dqrr {scalar_t__ cmode; scalar_t__ ci; int /*<<< orphan*/  cursor; } ;
struct qm_portal {struct qm_dqrr dqrr; } ;

/* Variables and functions */
 scalar_t__ dqrr_ptr2idx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_crit (char*) ; 
 scalar_t__ qm_dqrr_cdc ; 

__attribute__((used)) static inline void qm_dqrr_finish(struct qm_portal *portal)
{
#ifdef CONFIG_FSL_DPAA_CHECKING
	struct qm_dqrr *dqrr = &portal->dqrr;

	if (dqrr->cmode != qm_dqrr_cdc &&
	    dqrr->ci != dqrr_ptr2idx(dqrr->cursor))
		pr_crit("Ignoring completed DQRR entries\n");
#endif
}