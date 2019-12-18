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
struct tb_ring {int running; int /*<<< orphan*/  work; TYPE_2__* nhi; int /*<<< orphan*/  lock; scalar_t__ tail; scalar_t__ head; int /*<<< orphan*/  hop; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; TYPE_1__* pdev; scalar_t__ going_away; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RING_TYPE (struct tb_ring*) ; 
 int /*<<< orphan*/  dev_WARN (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ring_interrupt_active (struct tb_ring*,int) ; 
 int /*<<< orphan*/  ring_iowrite32desc (struct tb_ring*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ring_iowrite32options (struct tb_ring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ring_iowrite64desc (struct tb_ring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void tb_ring_stop(struct tb_ring *ring)
{
	spin_lock_irq(&ring->nhi->lock);
	spin_lock(&ring->lock);
	dev_dbg(&ring->nhi->pdev->dev, "stopping %s %d\n",
		RING_TYPE(ring), ring->hop);
	if (ring->nhi->going_away)
		goto err;
	if (!ring->running) {
		dev_WARN(&ring->nhi->pdev->dev, "%s %d already stopped\n",
			 RING_TYPE(ring), ring->hop);
		goto err;
	}
	ring_interrupt_active(ring, false);

	ring_iowrite32options(ring, 0, 0);
	ring_iowrite64desc(ring, 0, 0);
	ring_iowrite32desc(ring, 0, 8);
	ring_iowrite32desc(ring, 0, 12);
	ring->head = 0;
	ring->tail = 0;
	ring->running = false;

err:
	spin_unlock(&ring->lock);
	spin_unlock_irq(&ring->nhi->lock);

	/*
	 * schedule ring->work to invoke callbacks on all remaining frames.
	 */
	schedule_work(&ring->work);
	flush_work(&ring->work);
}