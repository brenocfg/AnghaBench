#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct net_device {int /*<<< orphan*/  base_addr; } ;
struct TYPE_6__ {scalar_t__ save_cnt; } ;
struct de4x5_private {int rxRingSize; int txRingSize; TYPE_3__ cache; TYPE_2__* tx_ring; TYPE_1__* rx_ring; scalar_t__ tx_old; scalar_t__ tx_new; scalar_t__ rx_old; scalar_t__ rx_new; scalar_t__ dma_rings; } ;
struct de4x5_desc {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_5__ {void* status; } ;
struct TYPE_4__ {void* status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE4X5_RRBA ; 
 int /*<<< orphan*/  DE4X5_TRBA ; 
 int NUM_RX_DESC ; 
 int /*<<< orphan*/  R_OWN ; 
 int /*<<< orphan*/  START_DE4X5 ; 
 int /*<<< orphan*/  STOP_DE4X5 ; 
 int /*<<< orphan*/  barrier () ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct de4x5_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outl (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
de4x5_rst_desc_ring(struct net_device *dev)
{
    struct de4x5_private *lp = netdev_priv(dev);
    u_long iobase = dev->base_addr;
    int i;
    s32 omr;

    if (lp->cache.save_cnt) {
	STOP_DE4X5;
	outl(lp->dma_rings, DE4X5_RRBA);
	outl(lp->dma_rings + NUM_RX_DESC * sizeof(struct de4x5_desc),
	     DE4X5_TRBA);

	lp->rx_new = lp->rx_old = 0;
	lp->tx_new = lp->tx_old = 0;

	for (i = 0; i < lp->rxRingSize; i++) {
	    lp->rx_ring[i].status = cpu_to_le32(R_OWN);
	}

	for (i = 0; i < lp->txRingSize; i++) {
	    lp->tx_ring[i].status = cpu_to_le32(0);
	}

	barrier();
	lp->cache.save_cnt--;
	START_DE4X5;
    }
}