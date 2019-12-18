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
struct qman_portal {int dummy; } ;
struct qman_fq {int dummy; } ;
struct qm_dqrr_entry {int stat; int /*<<< orphan*/  fd; } ;
typedef  enum qman_cb_dqrr_result { ____Placeholder_qman_cb_dqrr_result } qman_cb_dqrr_result ;

/* Variables and functions */
 int QM_DQRR_STAT_UNSCHEDULED ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fd ; 
 int /*<<< orphan*/  fd_dq ; 
 int /*<<< orphan*/  fd_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fd_neq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int qman_cb_dqrr_consume ; 
 int sdqcr_complete ; 
 int /*<<< orphan*/  waitqueue ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum qman_cb_dqrr_result cb_dqrr(struct qman_portal *p,
					struct qman_fq *fq,
					const struct qm_dqrr_entry *dq)
{
	if (WARN_ON(fd_neq(&fd_dq, &dq->fd))) {
		pr_err("BADNESS: dequeued frame doesn't match;\n");
		return qman_cb_dqrr_consume;
	}
	fd_inc(&fd_dq);
	if (!(dq->stat & QM_DQRR_STAT_UNSCHEDULED) && !fd_neq(&fd_dq, &fd)) {
		sdqcr_complete = 1;
		wake_up(&waitqueue);
	}
	return qman_cb_dqrr_consume;
}