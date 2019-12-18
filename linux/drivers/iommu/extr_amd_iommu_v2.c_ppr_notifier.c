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
typedef  int u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct pasid_state {int /*<<< orphan*/  lock; TYPE_1__* pri; scalar_t__ invalid; } ;
struct notifier_block {int dummy; } ;
struct iommu_dev_data {scalar_t__ defer_attach; } ;
struct fault {int tag; int finish; int /*<<< orphan*/  work; int /*<<< orphan*/  flags; int /*<<< orphan*/  pasid; struct pasid_state* state; int /*<<< orphan*/  address; struct device_state* dev_state; } ;
struct device_state {struct pci_dev* pdev; } ;
struct amd_iommu_fault {int tag; int device_id; int /*<<< orphan*/  flags; int /*<<< orphan*/  pasid; int /*<<< orphan*/  address; } ;
struct TYPE_2__ {int finish; int /*<<< orphan*/  inflight; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  PCI_BUS_NUM (int) ; 
 int /*<<< orphan*/  PPR_INVALID ; 
 int /*<<< orphan*/  amd_iommu_complete_ppr (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * amd_iommu_rlookup_table ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_fault ; 
 int /*<<< orphan*/  finish_pri_tag (struct device_state*,struct pasid_state*,int) ; 
 struct iommu_dev_data* get_dev_data (int /*<<< orphan*/ *) ; 
 struct device_state* get_device_state (int) ; 
 struct pasid_state* get_pasid_state (struct device_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_wq ; 
 struct fault* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct pci_dev* pci_get_domain_bus_and_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_device_state (struct device_state*) ; 
 int /*<<< orphan*/  put_pasid_state (struct pasid_state*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ translation_pre_enabled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ppr_notifier(struct notifier_block *nb, unsigned long e, void *data)
{
	struct amd_iommu_fault *iommu_fault;
	struct pasid_state *pasid_state;
	struct device_state *dev_state;
	unsigned long flags;
	struct fault *fault;
	bool finish;
	u16 tag, devid;
	int ret;
	struct iommu_dev_data *dev_data;
	struct pci_dev *pdev = NULL;

	iommu_fault = data;
	tag         = iommu_fault->tag & 0x1ff;
	finish      = (iommu_fault->tag >> 9) & 1;

	devid = iommu_fault->device_id;
	pdev = pci_get_domain_bus_and_slot(0, PCI_BUS_NUM(devid),
					   devid & 0xff);
	if (!pdev)
		return -ENODEV;
	dev_data = get_dev_data(&pdev->dev);

	/* In kdump kernel pci dev is not initialized yet -> send INVALID */
	ret = NOTIFY_DONE;
	if (translation_pre_enabled(amd_iommu_rlookup_table[devid])
		&& dev_data->defer_attach) {
		amd_iommu_complete_ppr(pdev, iommu_fault->pasid,
				       PPR_INVALID, tag);
		goto out;
	}

	dev_state = get_device_state(iommu_fault->device_id);
	if (dev_state == NULL)
		goto out;

	pasid_state = get_pasid_state(dev_state, iommu_fault->pasid);
	if (pasid_state == NULL || pasid_state->invalid) {
		/* We know the device but not the PASID -> send INVALID */
		amd_iommu_complete_ppr(dev_state->pdev, iommu_fault->pasid,
				       PPR_INVALID, tag);
		goto out_drop_state;
	}

	spin_lock_irqsave(&pasid_state->lock, flags);
	atomic_inc(&pasid_state->pri[tag].inflight);
	if (finish)
		pasid_state->pri[tag].finish = true;
	spin_unlock_irqrestore(&pasid_state->lock, flags);

	fault = kzalloc(sizeof(*fault), GFP_ATOMIC);
	if (fault == NULL) {
		/* We are OOM - send success and let the device re-fault */
		finish_pri_tag(dev_state, pasid_state, tag);
		goto out_drop_state;
	}

	fault->dev_state = dev_state;
	fault->address   = iommu_fault->address;
	fault->state     = pasid_state;
	fault->tag       = tag;
	fault->finish    = finish;
	fault->pasid     = iommu_fault->pasid;
	fault->flags     = iommu_fault->flags;
	INIT_WORK(&fault->work, do_fault);

	queue_work(iommu_wq, &fault->work);

	ret = NOTIFY_OK;

out_drop_state:

	if (ret != NOTIFY_OK && pasid_state)
		put_pasid_state(pasid_state);

	put_device_state(dev_state);

out:
	return ret;
}