#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  bus; } ;
struct device {TYPE_2__* bus; } ;
struct TYPE_8__ {int /*<<< orphan*/  mux_hw_lock; TYPE_3__* handler; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* switchto ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {TYPE_1__* pm; } ;
struct TYPE_5__ {int (* runtime_suspend ) (struct device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_D3cold ; 
 int /*<<< orphan*/  VGA_SWITCHEROO_IGD ; 
 int /*<<< orphan*/  VGA_SWITCHEROO_OFF ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_bus_set_current_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct device*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 
 int /*<<< orphan*/  vga_switcheroo_power_switch (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgasr_mutex ; 
 TYPE_4__ vgasr_priv ; 

__attribute__((used)) static int vga_switcheroo_runtime_suspend(struct device *dev)
{
	struct pci_dev *pdev = to_pci_dev(dev);
	int ret;

	ret = dev->bus->pm->runtime_suspend(dev);
	if (ret)
		return ret;
	mutex_lock(&vgasr_mutex);
	if (vgasr_priv.handler->switchto) {
		mutex_lock(&vgasr_priv.mux_hw_lock);
		vgasr_priv.handler->switchto(VGA_SWITCHEROO_IGD);
		mutex_unlock(&vgasr_priv.mux_hw_lock);
	}
	pci_bus_set_current_state(pdev->bus, PCI_D3cold);
	vga_switcheroo_power_switch(pdev, VGA_SWITCHEROO_OFF);
	mutex_unlock(&vgasr_mutex);
	return 0;
}