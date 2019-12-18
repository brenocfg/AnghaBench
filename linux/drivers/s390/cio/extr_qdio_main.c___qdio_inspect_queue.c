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
struct qdio_q {unsigned int first_to_check; unsigned int qdio_error; scalar_t__ is_input_q; } ;

/* Variables and functions */
 unsigned int add_buf (unsigned int,int) ; 
 int qdio_inbound_q_moved (struct qdio_q*,unsigned int) ; 
 int qdio_outbound_q_moved (struct qdio_q*,unsigned int) ; 

__attribute__((used)) static int __qdio_inspect_queue(struct qdio_q *q, unsigned int *bufnr,
				unsigned int *error)
{
	unsigned int start = q->first_to_check;
	int count;

	count = q->is_input_q ? qdio_inbound_q_moved(q, start) :
				qdio_outbound_q_moved(q, start);
	if (count == 0)
		return 0;

	*bufnr = start;
	*error = q->qdio_error;

	/* for the next time */
	q->first_to_check = add_buf(start, count);
	q->qdio_error = 0;

	return count;
}