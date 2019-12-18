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
union qm_mr_entry {int verb; } ;
struct qm_mr {int pi; scalar_t__ pmode; int vbit; int /*<<< orphan*/  fill; int /*<<< orphan*/  ring; } ;
struct qm_portal {struct qm_mr mr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA_ASSERT (int) ; 
 int QM_MR_SIZE ; 
 int QM_MR_VERB_VBIT ; 
 int /*<<< orphan*/  dpaa_invalidate_touch_ro (union qm_mr_entry*) ; 
 union qm_mr_entry* mr_inc (union qm_mr_entry*) ; 
 union qm_mr_entry* qm_cl (int /*<<< orphan*/ ,int) ; 
 scalar_t__ qm_mr_pvb ; 

__attribute__((used)) static inline void qm_mr_pvb_update(struct qm_portal *portal)
{
	struct qm_mr *mr = &portal->mr;
	union qm_mr_entry *res = qm_cl(mr->ring, mr->pi);

	DPAA_ASSERT(mr->pmode == qm_mr_pvb);

	if ((res->verb & QM_MR_VERB_VBIT) == mr->vbit) {
		mr->pi = (mr->pi + 1) & (QM_MR_SIZE - 1);
		if (!mr->pi)
			mr->vbit ^= QM_MR_VERB_VBIT;
		mr->fill++;
		res = mr_inc(res);
	}
	dpaa_invalidate_touch_ro(res);
}