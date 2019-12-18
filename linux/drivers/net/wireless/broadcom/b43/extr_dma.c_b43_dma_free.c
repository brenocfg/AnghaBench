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
struct b43_dma {int dummy; } ;
struct b43_wldev {struct b43_dma dma; } ;

/* Variables and functions */
 scalar_t__ b43_using_pio_transfers (struct b43_wldev*) ; 
 int /*<<< orphan*/  destroy_ring (struct b43_dma*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_ring ; 
 int /*<<< orphan*/  tx_ring_AC_BE ; 
 int /*<<< orphan*/  tx_ring_AC_BK ; 
 int /*<<< orphan*/  tx_ring_AC_VI ; 
 int /*<<< orphan*/  tx_ring_AC_VO ; 
 int /*<<< orphan*/  tx_ring_mcast ; 

void b43_dma_free(struct b43_wldev *dev)
{
	struct b43_dma *dma;

	if (b43_using_pio_transfers(dev))
		return;
	dma = &dev->dma;

	destroy_ring(dma, rx_ring);
	destroy_ring(dma, tx_ring_AC_BK);
	destroy_ring(dma, tx_ring_AC_BE);
	destroy_ring(dma, tx_ring_AC_VI);
	destroy_ring(dma, tx_ring_AC_VO);
	destroy_ring(dma, tx_ring_mcast);
}