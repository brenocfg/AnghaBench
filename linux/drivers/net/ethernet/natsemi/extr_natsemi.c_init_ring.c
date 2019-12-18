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
struct netdev_private {int cur_rx; int /*<<< orphan*/ ** rx_skbuff; TYPE_2__* rx_ring; scalar_t__ ring_dma; TYPE_2__* rx_head_desc; scalar_t__ oom; scalar_t__ dirty_rx; TYPE_1__* tx_ring; int /*<<< orphan*/ ** tx_skbuff; scalar_t__ cur_tx; scalar_t__ dirty_tx; } ;
struct netdev_desc {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {void* cmd_status; void* next_desc; } ;
struct TYPE_3__ {scalar_t__ cmd_status; void* next_desc; } ;

/* Variables and functions */
 scalar_t__ DescOwn ; 
 int RX_RING_SIZE ; 
 int TX_RING_SIZE ; 
 void* cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  dump_ring (struct net_device*) ; 
 struct netdev_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  refill_rx (struct net_device*) ; 
 int /*<<< orphan*/  set_bufsize (struct net_device*) ; 

__attribute__((used)) static void init_ring(struct net_device *dev)
{
	struct netdev_private *np = netdev_priv(dev);
	int i;

	/* 1) TX ring */
	np->dirty_tx = np->cur_tx = 0;
	for (i = 0; i < TX_RING_SIZE; i++) {
		np->tx_skbuff[i] = NULL;
		np->tx_ring[i].next_desc = cpu_to_le32(np->ring_dma
			+sizeof(struct netdev_desc)
			*((i+1)%TX_RING_SIZE+RX_RING_SIZE));
		np->tx_ring[i].cmd_status = 0;
	}

	/* 2) RX ring */
	np->dirty_rx = 0;
	np->cur_rx = RX_RING_SIZE;
	np->oom = 0;
	set_bufsize(dev);

	np->rx_head_desc = &np->rx_ring[0];

	/* Please be careful before changing this loop - at least gcc-2.95.1
	 * miscompiles it otherwise.
	 */
	/* Initialize all Rx descriptors. */
	for (i = 0; i < RX_RING_SIZE; i++) {
		np->rx_ring[i].next_desc = cpu_to_le32(np->ring_dma
				+sizeof(struct netdev_desc)
				*((i+1)%RX_RING_SIZE));
		np->rx_ring[i].cmd_status = cpu_to_le32(DescOwn);
		np->rx_skbuff[i] = NULL;
	}
	refill_rx(dev);
	dump_ring(dev);
}