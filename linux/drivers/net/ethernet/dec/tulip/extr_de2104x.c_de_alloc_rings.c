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
struct de_private {int /*<<< orphan*/ * rx_ring; int /*<<< orphan*/ * tx_ring; int /*<<< orphan*/  ring_dma; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE_RING_BYTES ; 
 size_t DE_RX_RING_SIZE ; 
 int ENOMEM ; 
 int de_init_rings (struct de_private*) ; 
 int /*<<< orphan*/ * pci_alloc_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int de_alloc_rings (struct de_private *de)
{
	de->rx_ring = pci_alloc_consistent(de->pdev, DE_RING_BYTES, &de->ring_dma);
	if (!de->rx_ring)
		return -ENOMEM;
	de->tx_ring = &de->rx_ring[DE_RX_RING_SIZE];
	return de_init_rings(de);
}