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
typedef  union qm_mc_result {int dummy; } qm_mc_result ;
typedef  int u8 ;
struct qm_mc {int rridx; scalar_t__ state; int vbit; TYPE_1__* cr; union qm_mc_result* rr; } ;
struct qm_portal {struct qm_mc mc; } ;
struct TYPE_2__ {int _ncw_verb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA_ASSERT (int) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 int /*<<< orphan*/  dpaa_flush (TYPE_1__*) ; 
 int /*<<< orphan*/  dpaa_invalidate_touch_ro (union qm_mc_result*) ; 
 scalar_t__ qman_mc_hw ; 
 scalar_t__ qman_mc_user ; 

__attribute__((used)) static inline void qm_mc_commit(struct qm_portal *portal, u8 myverb)
{
	struct qm_mc *mc = &portal->mc;
	union qm_mc_result *rr = mc->rr + mc->rridx;

	DPAA_ASSERT(mc->state == qman_mc_user);
	dma_wmb();
	mc->cr->_ncw_verb = myverb | mc->vbit;
	dpaa_flush(mc->cr);
	dpaa_invalidate_touch_ro(rr);
#ifdef CONFIG_FSL_DPAA_CHECKING
	mc->state = qman_mc_hw;
#endif
}