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
struct device {int dummy; } ;

/* Variables and functions */
 int __nhi_suspend_noirq (struct device*,int) ; 
 scalar_t__ device_may_wakeup (struct device*) ; 
 scalar_t__ nhi_wake_supported (struct pci_dev*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static int nhi_poweroff_noirq(struct device *dev)
{
	struct pci_dev *pdev = to_pci_dev(dev);
	bool wakeup;

	wakeup = device_may_wakeup(dev) && nhi_wake_supported(pdev);
	return __nhi_suspend_noirq(dev, wakeup);
}