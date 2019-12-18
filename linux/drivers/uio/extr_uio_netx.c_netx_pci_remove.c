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
struct uio_info {TYPE_1__* mem; } ;
struct pci_dev {int dummy; } ;
struct TYPE_2__ {scalar_t__ internal_addr; } ;

/* Variables and functions */
 scalar_t__ DPM_HOST_INT_EN0 ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct uio_info*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct uio_info* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  uio_unregister_device (struct uio_info*) ; 

__attribute__((used)) static void netx_pci_remove(struct pci_dev *dev)
{
	struct uio_info *info = pci_get_drvdata(dev);

	/* Disable all interrupts */
	iowrite32(0, info->mem[0].internal_addr + DPM_HOST_INT_EN0);
	uio_unregister_device(info);
	pci_release_regions(dev);
	pci_disable_device(dev);
	iounmap(info->mem[0].internal_addr);

	kfree(info);
}