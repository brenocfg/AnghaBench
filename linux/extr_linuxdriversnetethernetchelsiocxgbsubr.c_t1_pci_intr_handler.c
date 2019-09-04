#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_4__ {int /*<<< orphan*/  pdev; } ;
typedef  TYPE_1__ adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_PCICFG_INTR_CAUSE ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  t1_fatal_err (TYPE_1__*) ; 

__attribute__((used)) static int t1_pci_intr_handler(adapter_t *adapter)
{
	u32 pcix_cause;

	pci_read_config_dword(adapter->pdev, A_PCICFG_INTR_CAUSE, &pcix_cause);

	if (pcix_cause) {
		pci_write_config_dword(adapter->pdev, A_PCICFG_INTR_CAUSE,
				       pcix_cause);
		t1_fatal_err(adapter);    /* PCI errors are fatal */
	}
	return 0;
}