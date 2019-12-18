#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  bus; } ;
struct device {TYPE_2__* bus; } ;
struct TYPE_4__ {TYPE_1__* pm; } ;
struct TYPE_3__ {int (* runtime_resume ) (struct device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  VGA_SWITCHEROO_ON ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_wakeup_bus (int /*<<< orphan*/ ) ; 
 int stub1 (struct device*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 
 int /*<<< orphan*/  vga_switcheroo_power_switch (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgasr_mutex ; 

__attribute__((used)) static int vga_switcheroo_runtime_resume(struct device *dev)
{
	struct pci_dev *pdev = to_pci_dev(dev);
	int ret;

	mutex_lock(&vgasr_mutex);
	vga_switcheroo_power_switch(pdev, VGA_SWITCHEROO_ON);
	mutex_unlock(&vgasr_mutex);
	pci_wakeup_bus(pdev->bus);
	ret = dev->bus->pm->runtime_resume(dev);
	if (ret)
		return ret;

	return 0;
}