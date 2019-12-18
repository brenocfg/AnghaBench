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
union bm_mc_result {int /*<<< orphan*/  verb; } ;
struct bm_mc {int rridx; scalar_t__ state; int /*<<< orphan*/  vbit; union bm_mc_result* rr; } ;
struct bm_portal {struct bm_mc mc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BM_MCC_VERB_VBIT ; 
 int /*<<< orphan*/  DPAA_ASSERT (int) ; 
 int /*<<< orphan*/  dpaa_invalidate_touch_ro (union bm_mc_result*) ; 
 scalar_t__ mc_hw ; 
 scalar_t__ mc_idle ; 

__attribute__((used)) static inline union bm_mc_result *bm_mc_result(struct bm_portal *portal)
{
	struct bm_mc *mc = &portal->mc;
	union bm_mc_result *rr = mc->rr + mc->rridx;

	DPAA_ASSERT(mc->state == mc_hw);
	/*
	 * The inactive response register's verb byte always returns zero until
	 * its command is submitted and completed. This includes the valid-bit,
	 * in case you were wondering...
	 */
	if (!rr->verb) {
		dpaa_invalidate_touch_ro(rr);
		return NULL;
	}
	mc->rridx ^= 1;
	mc->vbit ^= BM_MCC_VERB_VBIT;
#ifdef CONFIG_FSL_DPAA_CHECKING
	mc->state = mc_idle;
#endif
	return rr;
}