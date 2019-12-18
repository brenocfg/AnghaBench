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
struct uio_info {char* name; char* version; TYPE_1__* mem; int /*<<< orphan*/  handler; int /*<<< orphan*/  irq_flags; int /*<<< orphan*/  irq; } ;
struct pci_device_id {int subdevice; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  internal_addr; void* memtype; void* size; void* addr; } ;

/* Variables and functions */
#define  CIF_SUBDEVICE_DEVICENET 129 
#define  CIF_SUBDEVICE_PROFIBUS 128 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 void* UIO_MEM_PHYS ; 
 int /*<<< orphan*/  hilscher_handler ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct uio_info*) ; 
 struct uio_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_ioremap_bar (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 scalar_t__ pci_request_regions (struct pci_dev*,char*) ; 
 void* pci_resource_len (struct pci_dev*,int) ; 
 void* pci_resource_start (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct uio_info*) ; 
 scalar_t__ uio_register_device (int /*<<< orphan*/ *,struct uio_info*) ; 

__attribute__((used)) static int hilscher_pci_probe(struct pci_dev *dev,
					const struct pci_device_id *id)
{
	struct uio_info *info;

	info = kzalloc(sizeof(struct uio_info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	if (pci_enable_device(dev))
		goto out_free;

	if (pci_request_regions(dev, "hilscher"))
		goto out_disable;

	info->mem[0].addr = pci_resource_start(dev, 0);
	if (!info->mem[0].addr)
		goto out_release;
	info->mem[0].internal_addr = pci_ioremap_bar(dev, 0);
	if (!info->mem[0].internal_addr)
		goto out_release;

	info->mem[0].size = pci_resource_len(dev, 0);
	info->mem[0].memtype = UIO_MEM_PHYS;
	info->mem[1].addr = pci_resource_start(dev, 2);
	info->mem[1].size = pci_resource_len(dev, 2);
	info->mem[1].memtype = UIO_MEM_PHYS;
	switch (id->subdevice) {
		case CIF_SUBDEVICE_PROFIBUS:
			info->name = "CIF_Profibus";
			break;
		case CIF_SUBDEVICE_DEVICENET:
			info->name = "CIF_Devicenet";
			break;
		default:
			info->name = "CIF_???";
	}
	info->version = "0.0.1";
	info->irq = dev->irq;
	info->irq_flags = IRQF_SHARED;
	info->handler = hilscher_handler;

	if (uio_register_device(&dev->dev, info))
		goto out_unmap;

	pci_set_drvdata(dev, info);

	return 0;
out_unmap:
	iounmap(info->mem[0].internal_addr);
out_release:
	pci_release_regions(dev);
out_disable:
	pci_disable_device(dev);
out_free:
	kfree (info);
	return -ENODEV;
}