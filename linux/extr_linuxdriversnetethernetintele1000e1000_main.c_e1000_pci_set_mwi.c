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
struct e1000_hw {struct e1000_adapter* back; } ;
struct e1000_adapter {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  e_err (int /*<<< orphan*/ ,char*) ; 
 int pci_set_mwi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  probe ; 

void e1000_pci_set_mwi(struct e1000_hw *hw)
{
	struct e1000_adapter *adapter = hw->back;
	int ret_val = pci_set_mwi(adapter->pdev);

	if (ret_val)
		e_err(probe, "Error in setting MWI\n");
}