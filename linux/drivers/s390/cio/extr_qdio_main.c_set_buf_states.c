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
struct TYPE_2__ {int /*<<< orphan*/ * val; } ;
struct qdio_q {TYPE_1__ slsb; } ;

/* Variables and functions */
 scalar_t__ is_qebsm (struct qdio_q*) ; 
 int next_buf (int) ; 
 int qdio_do_sqbs (struct qdio_q*,unsigned char,int,int) ; 
 int /*<<< orphan*/  xchg (int /*<<< orphan*/ *,unsigned char) ; 

__attribute__((used)) static inline int set_buf_states(struct qdio_q *q, int bufnr,
				 unsigned char state, int count)
{
	int i;

	if (is_qebsm(q))
		return qdio_do_sqbs(q, state, bufnr, count);

	for (i = 0; i < count; i++) {
		xchg(&q->slsb.val[bufnr], state);
		bufnr = next_buf(bufnr);
	}
	return count;
}