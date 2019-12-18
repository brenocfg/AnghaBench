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
struct uio_info {char* name; char* version; TYPE_1__* mem; int /*<<< orphan*/  irqcontrol; int /*<<< orphan*/  handler; int /*<<< orphan*/  irq_flags; int /*<<< orphan*/  irq; struct uio_info* priv; int /*<<< orphan*/  ier0_cache_lock; } ;
struct sercos3_priv {char* name; char* version; TYPE_1__* mem; int /*<<< orphan*/  irqcontrol; int /*<<< orphan*/  handler; int /*<<< orphan*/  irq_flags; int /*<<< orphan*/  irq; struct sercos3_priv* priv; int /*<<< orphan*/  ier0_cache_lock; } ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {scalar_t__ internal_addr; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct uio_info*) ; 
 struct uio_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 scalar_t__ pci_request_regions (struct pci_dev*,char*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct uio_info*) ; 
 int /*<<< orphan*/  sercos3_handler ; 
 int /*<<< orphan*/  sercos3_irqcontrol ; 
 scalar_t__ sercos3_setup_iomem (struct pci_dev*,struct uio_info*,int,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ uio_register_device (int /*<<< orphan*/ *,struct uio_info*) ; 

__attribute__((used)) static int sercos3_pci_probe(struct pci_dev *dev,
				       const struct pci_device_id *id)
{
	struct uio_info *info;
	struct sercos3_priv *priv;
	int i;

	info = kzalloc(sizeof(struct uio_info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	priv = kzalloc(sizeof(struct sercos3_priv), GFP_KERNEL);
	if (!priv)
		goto out_free;

	if (pci_enable_device(dev))
		goto out_free_priv;

	if (pci_request_regions(dev, "sercos3"))
		goto out_disable;

	/* we only need PCI BAR's 0, 2, 3, 4, 5 */
	if (sercos3_setup_iomem(dev, info, 0, 0))
		goto out_unmap;
	if (sercos3_setup_iomem(dev, info, 1, 2))
		goto out_unmap;
	if (sercos3_setup_iomem(dev, info, 2, 3))
		goto out_unmap;
	if (sercos3_setup_iomem(dev, info, 3, 4))
		goto out_unmap;
	if (sercos3_setup_iomem(dev, info, 4, 5))
		goto out_unmap;

	spin_lock_init(&priv->ier0_cache_lock);
	info->priv = priv;
	info->name = "Sercos_III_PCI";
	info->version = "0.0.1";
	info->irq = dev->irq;
	info->irq_flags = IRQF_SHARED;
	info->handler = sercos3_handler;
	info->irqcontrol = sercos3_irqcontrol;

	pci_set_drvdata(dev, info);

	if (uio_register_device(&dev->dev, info))
		goto out_unmap;

	return 0;

out_unmap:
	for (i = 0; i < 5; i++) {
		if (info->mem[i].internal_addr)
			iounmap(info->mem[i].internal_addr);
	}
	pci_release_regions(dev);
out_disable:
	pci_disable_device(dev);
out_free_priv:
	kfree(priv);
out_free:
	kfree(info);
	return -ENODEV;
}