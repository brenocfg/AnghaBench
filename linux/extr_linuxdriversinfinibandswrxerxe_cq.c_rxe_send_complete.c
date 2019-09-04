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
struct TYPE_2__ {int /*<<< orphan*/  cq_context; int /*<<< orphan*/  (* comp_handler ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
struct rxe_cq {TYPE_1__ ibcq; int /*<<< orphan*/  cq_lock; scalar_t__ is_dying; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rxe_send_complete(unsigned long data)
{
	struct rxe_cq *cq = (struct rxe_cq *)data;
	unsigned long flags;

	spin_lock_irqsave(&cq->cq_lock, flags);
	if (cq->is_dying) {
		spin_unlock_irqrestore(&cq->cq_lock, flags);
		return;
	}
	spin_unlock_irqrestore(&cq->cq_lock, flags);

	cq->ibcq.comp_handler(&cq->ibcq, cq->ibcq.cq_context);
}