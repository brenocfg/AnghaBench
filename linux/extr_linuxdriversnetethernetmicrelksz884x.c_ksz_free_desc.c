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
struct TYPE_6__ {int /*<<< orphan*/ * ring; scalar_t__ ring_phys; int /*<<< orphan*/ * ring_virt; } ;
struct TYPE_5__ {int /*<<< orphan*/ * ring; scalar_t__ ring_phys; int /*<<< orphan*/ * ring_virt; } ;
struct ksz_hw {TYPE_3__ tx_desc_info; TYPE_2__ rx_desc_info; } ;
struct TYPE_4__ {int /*<<< orphan*/ * alloc_virt; scalar_t__ alloc_size; int /*<<< orphan*/  dma_addr; } ;
struct dev_info {TYPE_1__ desc_pool; int /*<<< orphan*/  pdev; struct ksz_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ksz_free_desc(struct dev_info *adapter)
{
	struct ksz_hw *hw = &adapter->hw;

	/* Reset descriptor. */
	hw->rx_desc_info.ring_virt = NULL;
	hw->tx_desc_info.ring_virt = NULL;
	hw->rx_desc_info.ring_phys = 0;
	hw->tx_desc_info.ring_phys = 0;

	/* Free memory. */
	if (adapter->desc_pool.alloc_virt)
		pci_free_consistent(
			adapter->pdev,
			adapter->desc_pool.alloc_size,
			adapter->desc_pool.alloc_virt,
			adapter->desc_pool.dma_addr);

	/* Reset resource pool. */
	adapter->desc_pool.alloc_size = 0;
	adapter->desc_pool.alloc_virt = NULL;

	kfree(hw->rx_desc_info.ring);
	hw->rx_desc_info.ring = NULL;
	kfree(hw->tx_desc_info.ring);
	hw->tx_desc_info.ring = NULL;
}