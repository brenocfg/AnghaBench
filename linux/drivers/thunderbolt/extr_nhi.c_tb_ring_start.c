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
typedef  int u32 ;
typedef  int u16 ;
struct tb_ring {int running; int flags; int size; int sof_mask; int eof_mask; TYPE_2__* nhi; int /*<<< orphan*/  lock; scalar_t__ is_tx; int /*<<< orphan*/  descriptors_dma; int /*<<< orphan*/  hop; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; TYPE_1__* pdev; scalar_t__ going_away; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int REG_RX_OPTIONS_E2E_HOP_MASK ; 
 int REG_RX_OPTIONS_E2E_HOP_SHIFT ; 
 int RING_E2E_UNUSED_HOPID ; 
 int RING_FLAG_E2E ; 
 int RING_FLAG_E2E_FLOW_CONTROL ; 
 int RING_FLAG_ENABLE ; 
 int RING_FLAG_FRAME ; 
 int RING_FLAG_RAW ; 
 int /*<<< orphan*/  RING_TYPE (struct tb_ring*) ; 
 int TB_FRAME_SIZE ; 
 int /*<<< orphan*/  dev_WARN (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ring_interrupt_active (struct tb_ring*,int) ; 
 int /*<<< orphan*/  ring_iowrite32desc (struct tb_ring*,int,int) ; 
 int /*<<< orphan*/  ring_iowrite32options (struct tb_ring*,int,int) ; 
 int /*<<< orphan*/  ring_iowrite64desc (struct tb_ring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void tb_ring_start(struct tb_ring *ring)
{
	u16 frame_size;
	u32 flags;

	spin_lock_irq(&ring->nhi->lock);
	spin_lock(&ring->lock);
	if (ring->nhi->going_away)
		goto err;
	if (ring->running) {
		dev_WARN(&ring->nhi->pdev->dev, "ring already started\n");
		goto err;
	}
	dev_dbg(&ring->nhi->pdev->dev, "starting %s %d\n",
		RING_TYPE(ring), ring->hop);

	if (ring->flags & RING_FLAG_FRAME) {
		/* Means 4096 */
		frame_size = 0;
		flags = RING_FLAG_ENABLE;
	} else {
		frame_size = TB_FRAME_SIZE;
		flags = RING_FLAG_ENABLE | RING_FLAG_RAW;
	}

	if (ring->flags & RING_FLAG_E2E && !ring->is_tx) {
		u32 hop;

		/*
		 * In order not to lose Rx packets we enable end-to-end
		 * workaround which transfers Rx credits to an unused Tx
		 * HopID.
		 */
		hop = RING_E2E_UNUSED_HOPID << REG_RX_OPTIONS_E2E_HOP_SHIFT;
		hop &= REG_RX_OPTIONS_E2E_HOP_MASK;
		flags |= hop | RING_FLAG_E2E_FLOW_CONTROL;
	}

	ring_iowrite64desc(ring, ring->descriptors_dma, 0);
	if (ring->is_tx) {
		ring_iowrite32desc(ring, ring->size, 12);
		ring_iowrite32options(ring, 0, 4); /* time releated ? */
		ring_iowrite32options(ring, flags, 0);
	} else {
		u32 sof_eof_mask = ring->sof_mask << 16 | ring->eof_mask;

		ring_iowrite32desc(ring, (frame_size << 16) | ring->size, 12);
		ring_iowrite32options(ring, sof_eof_mask, 4);
		ring_iowrite32options(ring, flags, 0);
	}
	ring_interrupt_active(ring, true);
	ring->running = true;
err:
	spin_unlock(&ring->lock);
	spin_unlock_irq(&ring->nhi->lock);
}