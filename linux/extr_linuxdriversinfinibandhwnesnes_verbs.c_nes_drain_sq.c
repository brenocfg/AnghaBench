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
struct TYPE_2__ {scalar_t__ sq_tail; scalar_t__ sq_head; } ;
struct nes_qp {int /*<<< orphan*/  sq_drained; TYPE_1__ hwqp; } ;
struct ib_qp {int dummy; } ;

/* Variables and functions */
 struct nes_qp* to_nesqp (struct ib_qp*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nes_drain_sq(struct ib_qp *ibqp)
{
	struct nes_qp *nesqp = to_nesqp(ibqp);

	if (nesqp->hwqp.sq_tail != nesqp->hwqp.sq_head)
		wait_for_completion(&nesqp->sq_drained);
}