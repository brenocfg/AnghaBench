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
struct uio_info {char* name; char* version; TYPE_1__* mem; int /*<<< orphan*/  irqcontrol; int /*<<< orphan*/  handler; int /*<<< orphan*/  irq_flags; int /*<<< orphan*/  irq; } ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  internal_addr; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct uio_info*) ; 
 struct uio_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mf624_irq_handler ; 
 int /*<<< orphan*/  mf624_irqcontrol ; 
 scalar_t__ mf624_setup_mem (struct pci_dev*,int,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 scalar_t__ pci_request_regions (struct pci_dev*,char*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct uio_info*) ; 
 scalar_t__ uio_register_device (int /*<<< orphan*/ *,struct uio_info*) ; 

__attribute__((used)) static int mf624_pci_probe(struct pci_dev *dev, const struct pci_device_id *id)
{
	struct uio_info *info;

	info = kzalloc(sizeof(struct uio_info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	if (pci_enable_device(dev))
		goto out_free;

	if (pci_request_regions(dev, "mf624"))
		goto out_disable;

	info->name = "mf624";
	info->version = "0.0.1";

	/* Note: Datasheet says device uses BAR0, BAR1, BAR2 -- do not trust it */

	/* BAR0 */
	if (mf624_setup_mem(dev, 0, &info->mem[0], "PCI chipset, interrupts, status "
			    "bits, special functions"))
		goto out_release;
	/* BAR2 */
	if (mf624_setup_mem(dev, 2, &info->mem[1], "ADC, DAC, DIO"))
		goto out_unmap0;

	/* BAR4 */
	if (mf624_setup_mem(dev, 4, &info->mem[2], "Counter/timer chip"))
		goto out_unmap1;

	info->irq = dev->irq;
	info->irq_flags = IRQF_SHARED;
	info->handler = mf624_irq_handler;

	info->irqcontrol = mf624_irqcontrol;

	if (uio_register_device(&dev->dev, info))
		goto out_unmap2;

	pci_set_drvdata(dev, info);

	return 0;

out_unmap2:
	iounmap(info->mem[2].internal_addr);
out_unmap1:
	iounmap(info->mem[1].internal_addr);
out_unmap0:
	iounmap(info->mem[0].internal_addr);

out_release:
	pci_release_regions(dev);

out_disable:
	pci_disable_device(dev);

out_free:
	kfree(info);
	return -ENODEV;
}