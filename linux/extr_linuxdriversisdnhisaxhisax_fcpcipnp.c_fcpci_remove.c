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
struct fritz_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  delete_adapter (struct fritz_adapter*) ; 
 int /*<<< orphan*/  fcpcipnp_release (struct fritz_adapter*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct fritz_adapter* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void fcpci_remove(struct pci_dev *pdev)
{
	struct fritz_adapter *adapter = pci_get_drvdata(pdev);

	fcpcipnp_release(adapter);
	pci_disable_device(pdev);
	delete_adapter(adapter);
}