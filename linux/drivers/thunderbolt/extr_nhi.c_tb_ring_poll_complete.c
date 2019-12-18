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
struct tb_ring {TYPE_1__* nhi; int /*<<< orphan*/  lock; scalar_t__ start_poll; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ring_interrupt_mask (struct tb_ring*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void tb_ring_poll_complete(struct tb_ring *ring)
{
	unsigned long flags;

	spin_lock_irqsave(&ring->nhi->lock, flags);
	spin_lock(&ring->lock);
	if (ring->start_poll)
		__ring_interrupt_mask(ring, false);
	spin_unlock(&ring->lock);
	spin_unlock_irqrestore(&ring->nhi->lock, flags);
}