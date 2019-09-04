#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct npu {size_t index; int /*<<< orphan*/  nmmu_flush; } ;
struct pnv_phb {struct npu npu; int /*<<< orphan*/  opal_id; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;
struct pci_dev {int /*<<< orphan*/  devfn; TYPE_4__* bus; TYPE_1__ dev; } ;
struct TYPE_12__ {int /*<<< orphan*/ * ops; } ;
struct npu_context {void (* release_cb ) (struct npu_context*,void*) ;void* priv; int nmmu_flush; int /*<<< orphan*/ ** npdev; TYPE_6__ mn; struct mm_struct* mm; int /*<<< orphan*/  kref; } ;
struct TYPE_8__ {scalar_t__ id; struct npu_context* npu_context; } ;
struct mm_struct {TYPE_2__ context; } ;
struct device_node {int dummy; } ;
struct TYPE_11__ {struct mm_struct* mm; } ;
struct TYPE_10__ {int /*<<< orphan*/  number; } ;
struct TYPE_9__ {struct pnv_phb* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENOSPC ; 
 struct npu_context* ERR_PTR (int) ; 
 int /*<<< orphan*/  FW_FEATURE_OPAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PCI_DEVID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,struct pci_dev*) ; 
 int __mmu_notifier_register (TYPE_6__*,struct mm_struct*) ; 
 TYPE_5__* current ; 
 int /*<<< orphan*/  firmware_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct npu_context*) ; 
 int /*<<< orphan*/  kref_get_unless_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct npu_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_context_add_copro (struct mm_struct*) ; 
 int /*<<< orphan*/  npu_context_lock ; 
 int /*<<< orphan*/  nv_nmmu_notifier_ops ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int of_property_read_u32 (struct device_node*,char*,size_t*) ; 
 int /*<<< orphan*/  opal_npu_destroy_context (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int opal_npu_init_context (int /*<<< orphan*/ ,scalar_t__,unsigned long,int /*<<< orphan*/ ) ; 
 TYPE_3__* pci_bus_to_host (TYPE_4__*) ; 
 struct pci_dev* pnv_pci_get_npu_dev (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct npu_context *pnv_npu2_init_context(struct pci_dev *gpdev,
			unsigned long flags,
			void (*cb)(struct npu_context *, void *),
			void *priv)
{
	int rc;
	u32 nvlink_index;
	struct device_node *nvlink_dn;
	struct mm_struct *mm = current->mm;
	struct pnv_phb *nphb;
	struct npu *npu;
	struct npu_context *npu_context;

	/*
	 * At present we don't support GPUs connected to multiple NPUs and I'm
	 * not sure the hardware does either.
	 */
	struct pci_dev *npdev = pnv_pci_get_npu_dev(gpdev, 0);

	if (!firmware_has_feature(FW_FEATURE_OPAL))
		return ERR_PTR(-ENODEV);

	if (!npdev)
		/* No nvlink associated with this GPU device */
		return ERR_PTR(-ENODEV);

	nvlink_dn = of_parse_phandle(npdev->dev.of_node, "ibm,nvlink", 0);
	if (WARN_ON(of_property_read_u32(nvlink_dn, "ibm,npu-link-index",
							&nvlink_index)))
		return ERR_PTR(-ENODEV);

	if (!mm || mm->context.id == 0) {
		/*
		 * Kernel thread contexts are not supported and context id 0 is
		 * reserved on the GPU.
		 */
		return ERR_PTR(-EINVAL);
	}

	nphb = pci_bus_to_host(npdev->bus)->private_data;
	npu = &nphb->npu;

	/*
	 * Setup the NPU context table for a particular GPU. These need to be
	 * per-GPU as we need the tables to filter ATSDs when there are no
	 * active contexts on a particular GPU. It is safe for these to be
	 * called concurrently with destroy as the OPAL call takes appropriate
	 * locks and refcounts on init/destroy.
	 */
	rc = opal_npu_init_context(nphb->opal_id, mm->context.id, flags,
				PCI_DEVID(gpdev->bus->number, gpdev->devfn));
	if (rc < 0)
		return ERR_PTR(-ENOSPC);

	/*
	 * We store the npu pci device so we can more easily get at the
	 * associated npus.
	 */
	spin_lock(&npu_context_lock);
	npu_context = mm->context.npu_context;
	if (npu_context) {
		if (npu_context->release_cb != cb ||
			npu_context->priv != priv) {
			spin_unlock(&npu_context_lock);
			opal_npu_destroy_context(nphb->opal_id, mm->context.id,
						PCI_DEVID(gpdev->bus->number,
							gpdev->devfn));
			return ERR_PTR(-EINVAL);
		}

		WARN_ON(!kref_get_unless_zero(&npu_context->kref));
	}
	spin_unlock(&npu_context_lock);

	if (!npu_context) {
		/*
		 * We can set up these fields without holding the
		 * npu_context_lock as the npu_context hasn't been returned to
		 * the caller meaning it can't be destroyed. Parallel allocation
		 * is protected against by mmap_sem.
		 */
		rc = -ENOMEM;
		npu_context = kzalloc(sizeof(struct npu_context), GFP_KERNEL);
		if (npu_context) {
			kref_init(&npu_context->kref);
			npu_context->mm = mm;
			npu_context->mn.ops = &nv_nmmu_notifier_ops;
			rc = __mmu_notifier_register(&npu_context->mn, mm);
		}

		if (rc) {
			kfree(npu_context);
			opal_npu_destroy_context(nphb->opal_id, mm->context.id,
					PCI_DEVID(gpdev->bus->number,
						gpdev->devfn));
			return ERR_PTR(rc);
		}

		mm->context.npu_context = npu_context;
	}

	npu_context->release_cb = cb;
	npu_context->priv = priv;

	/*
	 * npdev is a pci_dev pointer setup by the PCI code. We assign it to
	 * npdev[][] to indicate to the mmu notifiers that an invalidation
	 * should also be sent over this nvlink. The notifiers don't use any
	 * other fields in npu_context, so we just need to ensure that when they
	 * deference npu_context->npdev[][] it is either a valid pointer or
	 * NULL.
	 */
	WRITE_ONCE(npu_context->npdev[npu->index][nvlink_index], npdev);

	if (!nphb->npu.nmmu_flush) {
		/*
		 * If we're not explicitly flushing ourselves we need to mark
		 * the thread for global flushes
		 */
		npu_context->nmmu_flush = false;
		mm_context_add_copro(mm);
	} else
		npu_context->nmmu_flush = true;

	return npu_context;
}