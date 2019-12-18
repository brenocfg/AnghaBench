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
typedef  scalar_t__ u32 ;
struct ag71xx_ring {scalar_t__ dirty; scalar_t__ curr; TYPE_2__* buf; scalar_t__ descs_dma; int /*<<< orphan*/  order; } ;
struct ag71xx_desc {int /*<<< orphan*/  ctrl; scalar_t__ next; } ;
struct ag71xx {int /*<<< orphan*/  ndev; struct ag71xx_ring tx_ring; } ;
struct TYPE_3__ {int /*<<< orphan*/ * skb; } ;
struct TYPE_4__ {TYPE_1__ tx; } ;

/* Variables and functions */
 int AG71XX_DESC_SIZE ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DESC_EMPTY ; 
 struct ag71xx_desc* ag71xx_ring_desc (struct ag71xx_ring*,int) ; 
 int /*<<< orphan*/  netdev_reset_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void ag71xx_ring_tx_init(struct ag71xx *ag)
{
	struct ag71xx_ring *ring = &ag->tx_ring;
	int ring_size = BIT(ring->order);
	int ring_mask = ring_size - 1;
	int i;

	for (i = 0; i < ring_size; i++) {
		struct ag71xx_desc *desc = ag71xx_ring_desc(ring, i);

		desc->next = (u32)(ring->descs_dma +
			AG71XX_DESC_SIZE * ((i + 1) & ring_mask));

		desc->ctrl = DESC_EMPTY;
		ring->buf[i].tx.skb = NULL;
	}

	/* flush descriptors */
	wmb();

	ring->curr = 0;
	ring->dirty = 0;
	netdev_reset_queue(ag->ndev);
}