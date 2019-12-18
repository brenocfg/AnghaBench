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
struct xdp_umem {unsigned int npgs; TYPE_2__* pages; } ;
struct ixgbe_adapter {TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {scalar_t__ dma; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  IXGBE_RX_DMA_ATTR ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_unmap_page_attrs (struct device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ixgbe_xsk_umem_dma_unmap(struct ixgbe_adapter *adapter,
				     struct xdp_umem *umem)
{
	struct device *dev = &adapter->pdev->dev;
	unsigned int i;

	for (i = 0; i < umem->npgs; i++) {
		dma_unmap_page_attrs(dev, umem->pages[i].dma, PAGE_SIZE,
				     DMA_BIDIRECTIONAL, IXGBE_RX_DMA_ATTR);

		umem->pages[i].dma = 0;
	}
}