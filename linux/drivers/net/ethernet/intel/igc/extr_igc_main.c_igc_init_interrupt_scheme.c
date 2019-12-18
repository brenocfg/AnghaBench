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
struct igc_adapter {struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int igc_alloc_q_vectors (struct igc_adapter*) ; 
 int /*<<< orphan*/  igc_cache_ring_register (struct igc_adapter*) ; 
 int /*<<< orphan*/  igc_reset_interrupt_capability (struct igc_adapter*) ; 
 int /*<<< orphan*/  igc_set_interrupt_capability (struct igc_adapter*,int) ; 

__attribute__((used)) static int igc_init_interrupt_scheme(struct igc_adapter *adapter, bool msix)
{
	struct pci_dev *pdev = adapter->pdev;
	int err = 0;

	igc_set_interrupt_capability(adapter, msix);

	err = igc_alloc_q_vectors(adapter);
	if (err) {
		dev_err(&pdev->dev, "Unable to allocate memory for vectors\n");
		goto err_alloc_q_vectors;
	}

	igc_cache_ring_register(adapter);

	return 0;

err_alloc_q_vectors:
	igc_reset_interrupt_capability(adapter);
	return err;
}