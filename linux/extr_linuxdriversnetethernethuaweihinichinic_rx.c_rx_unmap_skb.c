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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hinic_rxq {TYPE_1__* rq; int /*<<< orphan*/  netdev; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;
struct hinic_hwdev {struct hinic_hwif* hwif; } ;
struct hinic_dev {struct hinic_hwdev* hwdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  buf_sz; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hinic_dev* netdev_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rx_unmap_skb(struct hinic_rxq *rxq, dma_addr_t dma_addr)
{
	struct hinic_dev *nic_dev = netdev_priv(rxq->netdev);
	struct hinic_hwdev *hwdev = nic_dev->hwdev;
	struct hinic_hwif *hwif = hwdev->hwif;
	struct pci_dev *pdev = hwif->pdev;

	dma_unmap_single(&pdev->dev, dma_addr, rxq->rq->buf_sz,
			 DMA_FROM_DEVICE);
}