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
struct vmd_dev {int /*<<< orphan*/  irq_domain; int /*<<< orphan*/  bus; TYPE_2__* dev; } ;
struct pci_dev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 struct vmd_dev* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_remove_root_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_stop_root_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vmd_cleanup_srcu (struct vmd_dev*) ; 
 int /*<<< orphan*/  vmd_detach_resources (struct vmd_dev*) ; 
 int /*<<< orphan*/  vmd_teardown_dma_ops (struct vmd_dev*) ; 

__attribute__((used)) static void vmd_remove(struct pci_dev *dev)
{
	struct vmd_dev *vmd = pci_get_drvdata(dev);

	sysfs_remove_link(&vmd->dev->dev.kobj, "domain");
	pci_stop_root_bus(vmd->bus);
	pci_remove_root_bus(vmd->bus);
	vmd_cleanup_srcu(vmd);
	vmd_teardown_dma_ops(vmd);
	vmd_detach_resources(vmd);
	irq_domain_remove(vmd->irq_domain);
}