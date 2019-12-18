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
struct pci_dev {int /*<<< orphan*/  current_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_update_current_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ platform_pci_power_manageable (struct pci_dev*) ; 
 int /*<<< orphan*/  platform_pci_refresh_power_state (struct pci_dev*) ; 

void pci_refresh_power_state(struct pci_dev *dev)
{
	if (platform_pci_power_manageable(dev))
		platform_pci_refresh_power_state(dev);

	pci_update_current_state(dev, dev->current_state);
}