#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct npu {size_t index; } ;
struct pnv_phb {int /*<<< orphan*/  opal_id; struct npu npu; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct pci_dev {int /*<<< orphan*/  devfn; TYPE_4__* bus; TYPE_1__ dev; } ;
struct npu_context {TYPE_5__* mm; int /*<<< orphan*/  mn; int /*<<< orphan*/  kref; int /*<<< orphan*/ ** npdev; } ;
struct device_node {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct TYPE_10__ {TYPE_2__ context; } ;
struct TYPE_9__ {int /*<<< orphan*/  number; } ;
struct TYPE_8__ {struct pnv_phb* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_FEATURE_OPAL ; 
 int /*<<< orphan*/  PCI_DEVID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  firmware_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct npu_context*) ; 
 int kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmu_notifier_unregister (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  npu_context_lock ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int of_property_read_u32 (struct device_node*,char*,size_t*) ; 
 int /*<<< orphan*/  opal_npu_destroy_context (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* pci_bus_to_host (TYPE_4__*) ; 
 int /*<<< orphan*/  pnv_npu2_release_context ; 
 struct pci_dev* pnv_pci_get_npu_dev (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void pnv_npu2_destroy_context(struct npu_context *npu_context,
			struct pci_dev *gpdev)
{
	int removed;
	struct pnv_phb *nphb;
	struct npu *npu;
	struct pci_dev *npdev = pnv_pci_get_npu_dev(gpdev, 0);
	struct device_node *nvlink_dn;
	u32 nvlink_index;

	if (WARN_ON(!npdev))
		return;

	if (!firmware_has_feature(FW_FEATURE_OPAL))
		return;

	nphb = pci_bus_to_host(npdev->bus)->private_data;
	npu = &nphb->npu;
	nvlink_dn = of_parse_phandle(npdev->dev.of_node, "ibm,nvlink", 0);
	if (WARN_ON(of_property_read_u32(nvlink_dn, "ibm,npu-link-index",
							&nvlink_index)))
		return;
	WRITE_ONCE(npu_context->npdev[npu->index][nvlink_index], NULL);
	opal_npu_destroy_context(nphb->opal_id, npu_context->mm->context.id,
				PCI_DEVID(gpdev->bus->number, gpdev->devfn));
	spin_lock(&npu_context_lock);
	removed = kref_put(&npu_context->kref, pnv_npu2_release_context);
	spin_unlock(&npu_context_lock);

	/*
	 * We need to do this outside of pnv_npu2_release_context so that it is
	 * outside the spinlock as mmu_notifier_destroy uses SRCU.
	 */
	if (removed) {
		mmu_notifier_unregister(&npu_context->mn,
					npu_context->mm);

		kfree(npu_context);
	}

}