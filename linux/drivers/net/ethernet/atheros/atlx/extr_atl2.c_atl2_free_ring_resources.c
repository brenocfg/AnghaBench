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
struct pci_dev {int dummy; } ;
struct atl2_adapter {int /*<<< orphan*/  ring_dma; int /*<<< orphan*/  ring_vir_addr; int /*<<< orphan*/  ring_size; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atl2_free_ring_resources(struct atl2_adapter *adapter)
{
	struct pci_dev *pdev = adapter->pdev;
	pci_free_consistent(pdev, adapter->ring_size, adapter->ring_vir_addr,
		adapter->ring_dma);
}