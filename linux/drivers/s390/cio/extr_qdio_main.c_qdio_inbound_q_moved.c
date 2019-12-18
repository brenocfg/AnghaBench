#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  timestamp; } ;
struct TYPE_4__ {TYPE_1__ in; } ;
struct qdio_q {TYPE_2__ u; int /*<<< orphan*/  irq_ptr; } ;

/* Variables and functions */
 scalar_t__ MACHINE_IS_LPAR ; 
 int get_inbound_buffer_frontier (struct qdio_q*,unsigned int) ; 
 int /*<<< orphan*/  get_tod_clock () ; 
 int /*<<< orphan*/  is_thinint_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qdio_inbound_q_moved(struct qdio_q *q, unsigned int start)
{
	int count;

	count = get_inbound_buffer_frontier(q, start);

	if (count && !is_thinint_irq(q->irq_ptr) && MACHINE_IS_LPAR)
		q->u.in.timestamp = get_tod_clock();

	return count;
}