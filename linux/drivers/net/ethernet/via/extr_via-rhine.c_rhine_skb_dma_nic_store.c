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
struct rhine_skb_dma {int /*<<< orphan*/  dma; int /*<<< orphan*/  skb; } ;
struct rhine_private {TYPE_1__* rx_ring; int /*<<< orphan*/ * rx_skbuff; int /*<<< orphan*/ * rx_skbuff_dma; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_wmb () ; 

__attribute__((used)) static inline void rhine_skb_dma_nic_store(struct rhine_private *rp,
					   struct rhine_skb_dma *sd, int entry)
{
	rp->rx_skbuff_dma[entry] = sd->dma;
	rp->rx_skbuff[entry] = sd->skb;

	rp->rx_ring[entry].addr = cpu_to_le32(sd->dma);
	dma_wmb();
}