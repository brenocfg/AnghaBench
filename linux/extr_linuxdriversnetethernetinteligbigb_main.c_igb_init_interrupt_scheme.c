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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct igb_adapter {struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int igb_alloc_q_vectors (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_cache_ring_register (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_reset_interrupt_capability (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_set_interrupt_capability (struct igb_adapter*,int) ; 

__attribute__((used)) static int igb_init_interrupt_scheme(struct igb_adapter *adapter, bool msix)
{
	struct pci_dev *pdev = adapter->pdev;
	int err;

	igb_set_interrupt_capability(adapter, msix);

	err = igb_alloc_q_vectors(adapter);
	if (err) {
		dev_err(&pdev->dev, "Unable to allocate memory for vectors\n");
		goto err_alloc_q_vectors;
	}

	igb_cache_ring_register(adapter);

	return 0;

err_alloc_q_vectors:
	igb_reset_interrupt_capability(adapter);
	return err;
}