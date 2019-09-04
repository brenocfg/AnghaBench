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
struct be_adapter {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 scalar_t__ be_error_recovering (struct be_adapter*) ; 
 scalar_t__ pci_num_vf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool be_reset_required(struct be_adapter *adapter)
{
	if (be_error_recovering(adapter))
		return true;
	else
		return pci_num_vf(adapter->pdev) == 0;
}