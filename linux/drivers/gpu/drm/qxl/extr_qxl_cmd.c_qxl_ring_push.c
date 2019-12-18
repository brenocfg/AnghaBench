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
typedef  int /*<<< orphan*/  uint8_t ;
struct qxl_ring_header {int prod; scalar_t__ cons; scalar_t__ num_items; scalar_t__ notify_on_cons; int notify_on_prod; } ;
struct qxl_ring {int n_elements; int element_size; int /*<<< orphan*/  lock; int /*<<< orphan*/  prod_notify; TYPE_1__* ring; int /*<<< orphan*/ * push_event; } ;
struct TYPE_2__ {int /*<<< orphan*/ * elements; struct qxl_ring_header header; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_can_sleep () ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  memcpy (void*,void const*,int) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qxl_check_header (struct qxl_ring*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int qxl_ring_push(struct qxl_ring *ring,
		  const void *new_elt, bool interruptible)
{
	struct qxl_ring_header *header = &(ring->ring->header);
	uint8_t *elt;
	int idx, ret;
	unsigned long flags;

	spin_lock_irqsave(&ring->lock, flags);
	if (header->prod - header->cons == header->num_items) {
		header->notify_on_cons = header->cons + 1;
		mb();
		spin_unlock_irqrestore(&ring->lock, flags);
		if (!drm_can_sleep()) {
			while (!qxl_check_header(ring))
				udelay(1);
		} else {
			if (interruptible) {
				ret = wait_event_interruptible(*ring->push_event,
							       qxl_check_header(ring));
				if (ret)
					return ret;
			} else {
				wait_event(*ring->push_event,
					   qxl_check_header(ring));
			}

		}
		spin_lock_irqsave(&ring->lock, flags);
	}

	idx = header->prod & (ring->n_elements - 1);
	elt = ring->ring->elements + idx * ring->element_size;

	memcpy((void *)elt, new_elt, ring->element_size);

	header->prod++;

	mb();

	if (header->prod == header->notify_on_prod)
		outb(0, ring->prod_notify);

	spin_unlock_irqrestore(&ring->lock, flags);
	return 0;
}