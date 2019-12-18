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
struct rxe_queue_buf {int dummy; } ;
struct rxe_queue {unsigned int elem_size; unsigned int index_mask; size_t buf_size; TYPE_1__* buf; int /*<<< orphan*/  log2_elem_size; struct rxe_dev* rxe; } ;
struct rxe_dev {int dummy; } ;
struct TYPE_2__ {unsigned int index_mask; int /*<<< orphan*/  log2_elem_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int cache_line_size () ; 
 int /*<<< orphan*/  kfree (struct rxe_queue*) ; 
 struct rxe_queue* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  order_base_2 (unsigned int) ; 
 unsigned int roundup_pow_of_two (unsigned int) ; 
 TYPE_1__* vmalloc_user (size_t) ; 

struct rxe_queue *rxe_queue_init(struct rxe_dev *rxe,
				 int *num_elem,
				 unsigned int elem_size)
{
	struct rxe_queue *q;
	size_t buf_size;
	unsigned int num_slots;

	/* num_elem == 0 is allowed, but uninteresting */
	if (*num_elem < 0)
		goto err1;

	q = kmalloc(sizeof(*q), GFP_KERNEL);
	if (!q)
		goto err1;

	q->rxe = rxe;

	/* used in resize, only need to copy used part of queue */
	q->elem_size = elem_size;

	/* pad element up to at least a cacheline and always a power of 2 */
	if (elem_size < cache_line_size())
		elem_size = cache_line_size();
	elem_size = roundup_pow_of_two(elem_size);

	q->log2_elem_size = order_base_2(elem_size);

	num_slots = *num_elem + 1;
	num_slots = roundup_pow_of_two(num_slots);
	q->index_mask = num_slots - 1;

	buf_size = sizeof(struct rxe_queue_buf) + num_slots * elem_size;

	q->buf = vmalloc_user(buf_size);
	if (!q->buf)
		goto err2;

	q->buf->log2_elem_size = q->log2_elem_size;
	q->buf->index_mask = q->index_mask;

	q->buf_size = buf_size;

	*num_elem = num_slots - 1;
	return q;

err2:
	kfree(q);
err1:
	return NULL;
}