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
struct TYPE_2__ {int /*<<< orphan*/  tx_ring_AC_BK; int /*<<< orphan*/  tx_ring_AC_BE; int /*<<< orphan*/  tx_ring_AC_VI; int /*<<< orphan*/  tx_ring_AC_VO; int /*<<< orphan*/  tx_ring_mcast; } ;
struct b43_wldev {TYPE_1__ dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  b43_dma_tx_resume_ring (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_power_saving_ctl_bits (struct b43_wldev*,int /*<<< orphan*/ ) ; 

void b43_dma_tx_resume(struct b43_wldev *dev)
{
	b43_dma_tx_resume_ring(dev->dma.tx_ring_mcast);
	b43_dma_tx_resume_ring(dev->dma.tx_ring_AC_VO);
	b43_dma_tx_resume_ring(dev->dma.tx_ring_AC_VI);
	b43_dma_tx_resume_ring(dev->dma.tx_ring_AC_BE);
	b43_dma_tx_resume_ring(dev->dma.tx_ring_AC_BK);
	b43_power_saving_ctl_bits(dev, 0);
}