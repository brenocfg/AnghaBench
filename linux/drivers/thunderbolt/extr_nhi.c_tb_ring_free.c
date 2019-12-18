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
struct tb_ring {size_t hop; int size; int /*<<< orphan*/  work; TYPE_2__* nhi; scalar_t__ descriptors_dma; int /*<<< orphan*/ * descriptors; scalar_t__ running; scalar_t__ is_tx; } ;
struct TYPE_4__ {TYPE_1__* pdev; int /*<<< orphan*/  lock; int /*<<< orphan*/ ** rx_rings; int /*<<< orphan*/ ** tx_rings; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RING_TYPE (struct tb_ring*) ; 
 int /*<<< orphan*/  dev_WARN (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct tb_ring*) ; 
 int /*<<< orphan*/  ring_release_msix (struct tb_ring*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void tb_ring_free(struct tb_ring *ring)
{
	spin_lock_irq(&ring->nhi->lock);
	/*
	 * Dissociate the ring from the NHI. This also ensures that
	 * nhi_interrupt_work cannot reschedule ring->work.
	 */
	if (ring->is_tx)
		ring->nhi->tx_rings[ring->hop] = NULL;
	else
		ring->nhi->rx_rings[ring->hop] = NULL;

	if (ring->running) {
		dev_WARN(&ring->nhi->pdev->dev, "%s %d still running\n",
			 RING_TYPE(ring), ring->hop);
	}
	spin_unlock_irq(&ring->nhi->lock);

	ring_release_msix(ring);

	dma_free_coherent(&ring->nhi->pdev->dev,
			  ring->size * sizeof(*ring->descriptors),
			  ring->descriptors, ring->descriptors_dma);

	ring->descriptors = NULL;
	ring->descriptors_dma = 0;


	dev_dbg(&ring->nhi->pdev->dev, "freeing %s %d\n", RING_TYPE(ring),
		ring->hop);

	/**
	 * ring->work can no longer be scheduled (it is scheduled only
	 * by nhi_interrupt_work, ring_stop and ring_msix). Wait for it
	 * to finish before freeing the ring.
	 */
	flush_work(&ring->work);
	kfree(ring);
}