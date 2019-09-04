#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pnv_phb {scalar_t__ type; } ;
struct pci_dev {int /*<<< orphan*/  devfn; int /*<<< orphan*/  dev; int /*<<< orphan*/  bus; } ;
struct pci_controller {struct pnv_phb* private_data; } ;
struct npu_link {scalar_t__* fn_desired_actags; } ;

/* Variables and functions */
 size_t PCI_FUNC (int /*<<< orphan*/ ) ; 
 scalar_t__ PNV_PHB_NPU_OCAPI ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct npu_link* find_link (struct pci_dev*) ; 
 int get_actag_count (struct pci_dev*,int,int*) ; 
 int get_max_afu_index (struct pci_dev*,int*) ; 
 int /*<<< orphan*/  links_list_lock ; 
 int /*<<< orphan*/  machine_is (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct pci_controller* pci_bus_to_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  powernv ; 

__attribute__((used)) static void pnv_ocxl_fixup_actag(struct pci_dev *dev)
{
	struct pci_controller *hose = pci_bus_to_host(dev->bus);
	struct pnv_phb *phb = hose->private_data;
	struct npu_link *link;
	int rc, afu_idx = -1, i, actag;

	if (!machine_is(powernv))
		return;

	if (phb->type != PNV_PHB_NPU_OCAPI)
		return;

	mutex_lock(&links_list_lock);

	link = find_link(dev);
	if (!link) {
		dev_warn(&dev->dev, "couldn't update actag information\n");
		mutex_unlock(&links_list_lock);
		return;
	}

	/*
	 * Check how many actags are desired for the AFUs under that
	 * function and add it to the count for the link
	 */
	rc = get_max_afu_index(dev, &afu_idx);
	if (rc) {
		/* Most likely an invalid config space */
		dev_dbg(&dev->dev, "couldn't find AFU information\n");
		afu_idx = -1;
	}

	link->fn_desired_actags[PCI_FUNC(dev->devfn)] = 0;
	for (i = 0; i <= afu_idx; i++) {
		/*
		 * AFU index 'holes' are allowed. So don't fail if we
		 * can't read the actag info for an index
		 */
		rc = get_actag_count(dev, i, &actag);
		if (rc)
			continue;
		link->fn_desired_actags[PCI_FUNC(dev->devfn)] += actag;
	}
	dev_dbg(&dev->dev, "total actags for function: %d\n",
		link->fn_desired_actags[PCI_FUNC(dev->devfn)]);

	mutex_unlock(&links_list_lock);
}