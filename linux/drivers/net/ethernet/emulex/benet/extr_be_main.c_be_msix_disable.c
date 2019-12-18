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
struct be_adapter {scalar_t__ num_msix_roce_vec; scalar_t__ num_msix_vec; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 scalar_t__ msix_enabled (struct be_adapter*) ; 
 int /*<<< orphan*/  pci_disable_msix (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void be_msix_disable(struct be_adapter *adapter)
{
	if (msix_enabled(adapter)) {
		pci_disable_msix(adapter->pdev);
		adapter->num_msix_vec = 0;
		adapter->num_msix_roce_vec = 0;
	}
}