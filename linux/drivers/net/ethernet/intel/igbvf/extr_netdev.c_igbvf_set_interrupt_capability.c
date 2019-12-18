#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct msix_entry {int dummy; } ;
struct igbvf_adapter {TYPE_1__* pdev; TYPE_2__* msix_entries; } ;
struct TYPE_5__ {int entry; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  igbvf_reset_interrupt_capability (struct igbvf_adapter*) ; 
 TYPE_2__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int pci_enable_msix_range (TYPE_1__*,TYPE_2__*,int,int) ; 

__attribute__((used)) static void igbvf_set_interrupt_capability(struct igbvf_adapter *adapter)
{
	int err = -ENOMEM;
	int i;

	/* we allocate 3 vectors, 1 for Tx, 1 for Rx, one for PF messages */
	adapter->msix_entries = kcalloc(3, sizeof(struct msix_entry),
					GFP_KERNEL);
	if (adapter->msix_entries) {
		for (i = 0; i < 3; i++)
			adapter->msix_entries[i].entry = i;

		err = pci_enable_msix_range(adapter->pdev,
					    adapter->msix_entries, 3, 3);
	}

	if (err < 0) {
		/* MSI-X failed */
		dev_err(&adapter->pdev->dev,
			"Failed to initialize MSI-X interrupts.\n");
		igbvf_reset_interrupt_capability(adapter);
	}
}