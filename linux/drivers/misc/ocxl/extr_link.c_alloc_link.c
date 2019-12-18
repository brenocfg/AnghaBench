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
struct pci_dev {int /*<<< orphan*/  devfn; TYPE_2__* bus; } ;
struct ocxl_link {int /*<<< orphan*/  platform_data; TYPE_1__* spa; int /*<<< orphan*/  irq_available; int /*<<< orphan*/  dev; int /*<<< orphan*/  bus; int /*<<< orphan*/  domain; int /*<<< orphan*/  ref; } ;
struct TYPE_4__ {int /*<<< orphan*/  number; } ;
struct TYPE_3__ {int /*<<< orphan*/  spa_mem; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_IRQ_PER_LINK ; 
 int /*<<< orphan*/  PCI_SLOT (int /*<<< orphan*/ ) ; 
 int alloc_spa (struct pci_dev*,struct ocxl_link*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_spa (struct ocxl_link*) ; 
 int /*<<< orphan*/  kfree (struct ocxl_link*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct ocxl_link* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_domain_nr (TYPE_2__*) ; 
 int pnv_ocxl_spa_setup (struct pci_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_xsl_irq (struct ocxl_link*) ; 
 int setup_xsl_irq (struct pci_dev*,struct ocxl_link*) ; 

__attribute__((used)) static int alloc_link(struct pci_dev *dev, int PE_mask, struct ocxl_link **out_link)
{
	struct ocxl_link *link;
	int rc;

	link = kzalloc(sizeof(struct ocxl_link), GFP_KERNEL);
	if (!link)
		return -ENOMEM;

	kref_init(&link->ref);
	link->domain = pci_domain_nr(dev->bus);
	link->bus = dev->bus->number;
	link->dev = PCI_SLOT(dev->devfn);
	atomic_set(&link->irq_available, MAX_IRQ_PER_LINK);

	rc = alloc_spa(dev, link);
	if (rc)
		goto err_free;

	rc = setup_xsl_irq(dev, link);
	if (rc)
		goto err_spa;

	/* platform specific hook */
	rc = pnv_ocxl_spa_setup(dev, link->spa->spa_mem, PE_mask,
				&link->platform_data);
	if (rc)
		goto err_xsl_irq;

	*out_link = link;
	return 0;

err_xsl_irq:
	release_xsl_irq(link);
err_spa:
	free_spa(link);
err_free:
	kfree(link);
	return rc;
}