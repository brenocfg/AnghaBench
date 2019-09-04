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
struct rxe_queue {int /*<<< orphan*/  elem_size; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  advance_consumer (struct rxe_queue*) ; 
 int /*<<< orphan*/  advance_producer (struct rxe_queue*) ; 
 int /*<<< orphan*/  consumer_addr (struct rxe_queue*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  producer_addr (struct rxe_queue*) ; 
 unsigned int queue_count (struct rxe_queue*) ; 
 int /*<<< orphan*/  queue_empty (struct rxe_queue*) ; 
 int /*<<< orphan*/  swap (struct rxe_queue,struct rxe_queue) ; 

__attribute__((used)) static int resize_finish(struct rxe_queue *q, struct rxe_queue *new_q,
			 unsigned int num_elem)
{
	if (!queue_empty(q) && (num_elem < queue_count(q)))
		return -EINVAL;

	while (!queue_empty(q)) {
		memcpy(producer_addr(new_q), consumer_addr(q),
		       new_q->elem_size);
		advance_producer(new_q);
		advance_consumer(q);
	}

	swap(*q, *new_q);

	return 0;
}