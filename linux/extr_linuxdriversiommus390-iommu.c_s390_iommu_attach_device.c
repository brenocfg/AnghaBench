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
typedef  int /*<<< orphan*/  u64 ;
struct zpci_dev {scalar_t__ start_dma; scalar_t__ end_dma; struct s390_domain* s390_domain; scalar_t__ dma_table; } ;
struct s390_domain_device {int /*<<< orphan*/  list; struct zpci_dev* zdev; } ;
struct s390_domain {int /*<<< orphan*/  list_lock; int /*<<< orphan*/  devices; scalar_t__ dma_table; } ;
struct TYPE_3__ {scalar_t__ aperture_start; scalar_t__ aperture_end; int force_aperture; } ;
struct iommu_domain {TYPE_1__ geometry; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct zpci_dev* sysdata; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct s390_domain_device*) ; 
 struct s390_domain_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_2__* to_pci_dev (struct device*) ; 
 struct s390_domain* to_s390_domain (struct iommu_domain*) ; 
 int /*<<< orphan*/  zpci_dma_exit_device (struct zpci_dev*) ; 
 int /*<<< orphan*/  zpci_dma_init_device (struct zpci_dev*) ; 
 int zpci_register_ioat (struct zpci_dev*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s390_iommu_attach_device(struct iommu_domain *domain,
				    struct device *dev)
{
	struct s390_domain *s390_domain = to_s390_domain(domain);
	struct zpci_dev *zdev = to_pci_dev(dev)->sysdata;
	struct s390_domain_device *domain_device;
	unsigned long flags;
	int rc;

	if (!zdev)
		return -ENODEV;

	domain_device = kzalloc(sizeof(*domain_device), GFP_KERNEL);
	if (!domain_device)
		return -ENOMEM;

	if (zdev->dma_table)
		zpci_dma_exit_device(zdev);

	zdev->dma_table = s390_domain->dma_table;
	rc = zpci_register_ioat(zdev, 0, zdev->start_dma, zdev->end_dma,
				(u64) zdev->dma_table);
	if (rc)
		goto out_restore;

	spin_lock_irqsave(&s390_domain->list_lock, flags);
	/* First device defines the DMA range limits */
	if (list_empty(&s390_domain->devices)) {
		domain->geometry.aperture_start = zdev->start_dma;
		domain->geometry.aperture_end = zdev->end_dma;
		domain->geometry.force_aperture = true;
	/* Allow only devices with identical DMA range limits */
	} else if (domain->geometry.aperture_start != zdev->start_dma ||
		   domain->geometry.aperture_end != zdev->end_dma) {
		rc = -EINVAL;
		spin_unlock_irqrestore(&s390_domain->list_lock, flags);
		goto out_restore;
	}
	domain_device->zdev = zdev;
	zdev->s390_domain = s390_domain;
	list_add(&domain_device->list, &s390_domain->devices);
	spin_unlock_irqrestore(&s390_domain->list_lock, flags);

	return 0;

out_restore:
	zpci_dma_init_device(zdev);
	kfree(domain_device);

	return rc;
}