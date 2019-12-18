#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct pci_dev {int dummy; } ;
struct TYPE_4__ {TYPE_2__* device; } ;
struct nvme_dev {int cmb_size; int cmbsz; int cmb_use_sqes; TYPE_1__ ctrl; void* cmbloc; int /*<<< orphan*/  bar; int /*<<< orphan*/  dev; } ;
typedef  int resource_size_t ;
struct TYPE_6__ {int /*<<< orphan*/  attr; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int NVME_CMBSZ_RDS ; 
 int NVME_CMBSZ_SQS ; 
 int NVME_CMBSZ_WDS ; 
 int NVME_CMB_BIR (void*) ; 
 int NVME_CMB_OFST (void*) ; 
 scalar_t__ NVME_REG_CMBLOC ; 
 scalar_t__ NVME_REG_CMBSZ ; 
 TYPE_3__ dev_attr_cmb ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 int nvme_cmb_size (struct nvme_dev*) ; 
 int nvme_cmb_size_unit (struct nvme_dev*) ; 
 scalar_t__ pci_p2pdma_add_resource (struct pci_dev*,int,int,int) ; 
 int /*<<< orphan*/  pci_p2pmem_publish (struct pci_dev*,int) ; 
 int pci_resource_len (struct pci_dev*,int) ; 
 void* readl (scalar_t__) ; 
 scalar_t__ sysfs_add_file_to_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ use_cmb_sqes ; 

__attribute__((used)) static void nvme_map_cmb(struct nvme_dev *dev)
{
	u64 size, offset;
	resource_size_t bar_size;
	struct pci_dev *pdev = to_pci_dev(dev->dev);
	int bar;

	if (dev->cmb_size)
		return;

	dev->cmbsz = readl(dev->bar + NVME_REG_CMBSZ);
	if (!dev->cmbsz)
		return;
	dev->cmbloc = readl(dev->bar + NVME_REG_CMBLOC);

	size = nvme_cmb_size_unit(dev) * nvme_cmb_size(dev);
	offset = nvme_cmb_size_unit(dev) * NVME_CMB_OFST(dev->cmbloc);
	bar = NVME_CMB_BIR(dev->cmbloc);
	bar_size = pci_resource_len(pdev, bar);

	if (offset > bar_size)
		return;

	/*
	 * Controllers may support a CMB size larger than their BAR,
	 * for example, due to being behind a bridge. Reduce the CMB to
	 * the reported size of the BAR
	 */
	if (size > bar_size - offset)
		size = bar_size - offset;

	if (pci_p2pdma_add_resource(pdev, bar, size, offset)) {
		dev_warn(dev->ctrl.device,
			 "failed to register the CMB\n");
		return;
	}

	dev->cmb_size = size;
	dev->cmb_use_sqes = use_cmb_sqes && (dev->cmbsz & NVME_CMBSZ_SQS);

	if ((dev->cmbsz & (NVME_CMBSZ_WDS | NVME_CMBSZ_RDS)) ==
			(NVME_CMBSZ_WDS | NVME_CMBSZ_RDS))
		pci_p2pmem_publish(pdev, true);

	if (sysfs_add_file_to_group(&dev->ctrl.device->kobj,
				    &dev_attr_cmb.attr, NULL))
		dev_warn(dev->ctrl.device,
			 "failed to add sysfs attribute for CMB\n");
}