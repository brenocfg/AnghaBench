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
struct pm_message {scalar_t__ event; } ;
struct pci_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct pci_dev* to_pci_dev (struct device*) ; 
 int vmw_pci_suspend (struct pci_dev*,struct pm_message) ; 

__attribute__((used)) static int vmw_pm_suspend(struct device *kdev)
{
	struct pci_dev *pdev = to_pci_dev(kdev);
	struct pm_message dummy;

	dummy.event = 0;

	return vmw_pci_suspend(pdev, dummy);
}