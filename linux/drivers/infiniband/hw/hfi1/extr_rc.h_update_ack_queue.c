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
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct rvt_qp {unsigned int s_tail_ack_queue; unsigned int s_acked_ack_queue; int /*<<< orphan*/  s_ack_state; TYPE_1__ ibqp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACKNOWLEDGE ; 
 int /*<<< orphan*/  OP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_to_rvt (int /*<<< orphan*/ ) ; 
 unsigned int rvt_size_atomic (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void update_ack_queue(struct rvt_qp *qp, unsigned int n)
{
	unsigned int next;

	next = n + 1;
	if (next > rvt_size_atomic(ib_to_rvt(qp->ibqp.device)))
		next = 0;
	qp->s_tail_ack_queue = next;
	qp->s_acked_ack_queue = next;
	qp->s_ack_state = OP(ACKNOWLEDGE);
}