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
struct srp_rdma_ch {int /*<<< orphan*/  qp; int /*<<< orphan*/  lock; int /*<<< orphan*/  send_cq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_destroy_qp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_drain_qp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_process_cq_direct (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void srp_destroy_qp(struct srp_rdma_ch *ch)
{
	spin_lock_irq(&ch->lock);
	ib_process_cq_direct(ch->send_cq, -1);
	spin_unlock_irq(&ch->lock);

	ib_drain_qp(ch->qp);
	ib_destroy_qp(ch->qp);
}