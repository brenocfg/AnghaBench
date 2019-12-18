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

/* Variables and functions */
 int /*<<< orphan*/  global_dev ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  via_fb_pci_remove (struct pci_dev*) ; 
 int /*<<< orphan*/  via_pci_teardown_mmio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  via_teardown_subdevs () ; 

__attribute__((used)) static void via_pci_remove(struct pci_dev *pdev)
{
	via_teardown_subdevs();
	via_fb_pci_remove(pdev);
	via_pci_teardown_mmio(&global_dev);
	pci_disable_device(pdev);
}