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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct ring {int dummy; } ;
struct qxl_ring_header {int dummy; } ;
struct qxl_ring {int element_size; int n_elements; int prod_notify; int /*<<< orphan*/  lock; int /*<<< orphan*/ * push_event; struct ring* ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct qxl_ring* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qxl_ring_init_hdr (struct qxl_ring*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct qxl_ring *
qxl_ring_create(struct qxl_ring_header *header,
		int element_size,
		int n_elements,
		int prod_notify,
		bool set_prod_notify,
		wait_queue_head_t *push_event)
{
	struct qxl_ring *ring;

	ring = kmalloc(sizeof(*ring), GFP_KERNEL);
	if (!ring)
		return NULL;

	ring->ring = (struct ring *)header;
	ring->element_size = element_size;
	ring->n_elements = n_elements;
	ring->prod_notify = prod_notify;
	ring->push_event = push_event;
	if (set_prod_notify)
		qxl_ring_init_hdr(ring);
	spin_lock_init(&ring->lock);
	return ring;
}