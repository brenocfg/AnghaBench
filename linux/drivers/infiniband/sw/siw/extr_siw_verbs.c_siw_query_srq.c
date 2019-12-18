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
struct siw_srq {int /*<<< orphan*/  lock; int /*<<< orphan*/  limit; int /*<<< orphan*/  max_sge; int /*<<< orphan*/  num_rqe; } ;
struct ib_srq_attr {int /*<<< orphan*/  srq_limit; int /*<<< orphan*/  max_sge; int /*<<< orphan*/  max_wr; } ;
struct ib_srq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct siw_srq* to_siw_srq (struct ib_srq*) ; 

int siw_query_srq(struct ib_srq *base_srq, struct ib_srq_attr *attrs)
{
	struct siw_srq *srq = to_siw_srq(base_srq);
	unsigned long flags;

	spin_lock_irqsave(&srq->lock, flags);

	attrs->max_wr = srq->num_rqe;
	attrs->max_sge = srq->max_sge;
	attrs->srq_limit = srq->limit;

	spin_unlock_irqrestore(&srq->lock, flags);

	return 0;
}