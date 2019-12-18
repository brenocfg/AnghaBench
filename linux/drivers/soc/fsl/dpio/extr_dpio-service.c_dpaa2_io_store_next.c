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
struct dpaa2_io_store {size_t idx; struct dpaa2_dq* vaddr; int /*<<< orphan*/  swp; } ;
struct dpaa2_dq {int dummy; } ;

/* Variables and functions */
 int DPAA2_DQ_STAT_VALIDFRAME ; 
 int dpaa2_dq_flags (struct dpaa2_dq*) ; 
 scalar_t__ dpaa2_dq_is_pull_complete (struct dpaa2_dq*) ; 
 int /*<<< orphan*/  prefetch (struct dpaa2_dq*) ; 
 int qbman_result_has_new_result (int /*<<< orphan*/ ,struct dpaa2_dq*) ; 

struct dpaa2_dq *dpaa2_io_store_next(struct dpaa2_io_store *s, int *is_last)
{
	int match;
	struct dpaa2_dq *ret = &s->vaddr[s->idx];

	match = qbman_result_has_new_result(s->swp, ret);
	if (!match) {
		*is_last = 0;
		return NULL;
	}

	s->idx++;

	if (dpaa2_dq_is_pull_complete(ret)) {
		*is_last = 1;
		s->idx = 0;
		/*
		 * If we get an empty dequeue result to terminate a zero-results
		 * vdqcr, return NULL to the caller rather than expecting him to
		 * check non-NULL results every time.
		 */
		if (!(dpaa2_dq_flags(ret) & DPAA2_DQ_STAT_VALIDFRAME))
			ret = NULL;
	} else {
		prefetch(&s->vaddr[s->idx]);
		*is_last = 0;
	}

	return ret;
}