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
struct amd8111e_tx_dr {int dummy; } ;
struct amd8111e_rx_dr {int dummy; } ;
struct amd8111e_priv {int /*<<< orphan*/ * tx_ring; int /*<<< orphan*/  tx_ring_dma_addr; int /*<<< orphan*/  pci_dev; int /*<<< orphan*/ * rx_ring; int /*<<< orphan*/  rx_ring_dma_addr; } ;

/* Variables and functions */
 int NUM_RX_RING_DR ; 
 int NUM_TX_RING_DR ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void amd8111e_free_ring(struct amd8111e_priv *lp)
{
	/* Free transmit and receive descriptor rings */
	if(lp->rx_ring){
		pci_free_consistent(lp->pci_dev,
			sizeof(struct amd8111e_rx_dr)*NUM_RX_RING_DR,
			lp->rx_ring, lp->rx_ring_dma_addr);
		lp->rx_ring = NULL;
	}

	if(lp->tx_ring){
		pci_free_consistent(lp->pci_dev,
			sizeof(struct amd8111e_tx_dr)*NUM_TX_RING_DR,
			lp->tx_ring, lp->tx_ring_dma_addr);

		lp->tx_ring = NULL;
	}

}