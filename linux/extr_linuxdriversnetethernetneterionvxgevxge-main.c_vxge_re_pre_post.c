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
struct vxge_rx_priv {int /*<<< orphan*/  data_size; int /*<<< orphan*/  data_dma; } ;
struct vxge_ring {int /*<<< orphan*/  handle; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxge_hw_ring_rxd_1b_set (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxge_hw_ring_rxd_pre_post (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static inline void vxge_re_pre_post(void *dtr, struct vxge_ring *ring,
				    struct vxge_rx_priv *rx_priv)
{
	pci_dma_sync_single_for_device(ring->pdev,
		rx_priv->data_dma, rx_priv->data_size, PCI_DMA_FROMDEVICE);

	vxge_hw_ring_rxd_1b_set(dtr, rx_priv->data_dma, rx_priv->data_size);
	vxge_hw_ring_rxd_pre_post(ring->handle, dtr);
}