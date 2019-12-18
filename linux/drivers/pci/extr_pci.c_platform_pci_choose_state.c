#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  pci_power_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* choose_state ) (struct pci_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_POWER_ERROR ; 
 TYPE_1__* pci_platform_pm ; 
 int /*<<< orphan*/  stub1 (struct pci_dev*) ; 

__attribute__((used)) static inline pci_power_t platform_pci_choose_state(struct pci_dev *dev)
{
	return pci_platform_pm ?
			pci_platform_pm->choose_state(dev) : PCI_POWER_ERROR;
}