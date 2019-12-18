#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vfio_pci_device {int num_ctx; TYPE_1__* ctx; struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct msi_msg {int dummy; } ;
struct eventfd_ctx {int dummy; } ;
struct TYPE_5__ {int irq; struct eventfd_ctx* token; } ;
struct TYPE_4__ {struct eventfd_ctx* trigger; TYPE_2__ producer; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct eventfd_ctx*) ; 
 int PTR_ERR (struct eventfd_ctx*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,struct eventfd_ctx*,int) ; 
 struct eventfd_ctx* eventfd_ctx_fdget (int) ; 
 int /*<<< orphan*/  eventfd_ctx_put (struct eventfd_ctx*) ; 
 int /*<<< orphan*/  free_irq (int,struct eventfd_ctx*) ; 
 int /*<<< orphan*/  get_cached_msi_msg (int,struct msi_msg*) ; 
 int irq_bypass_register_producer (TYPE_2__*) ; 
 int /*<<< orphan*/  irq_bypass_unregister_producer (TYPE_2__*) ; 
 int /*<<< orphan*/  kasprintf (int /*<<< orphan*/ ,char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int pci_irq_vector (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_write_msi_msg (int,struct msi_msg*) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct eventfd_ctx*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vfio_msihandler ; 

__attribute__((used)) static int vfio_msi_set_vector_signal(struct vfio_pci_device *vdev,
				      int vector, int fd, bool msix)
{
	struct pci_dev *pdev = vdev->pdev;
	struct eventfd_ctx *trigger;
	int irq, ret;

	if (vector < 0 || vector >= vdev->num_ctx)
		return -EINVAL;

	irq = pci_irq_vector(pdev, vector);

	if (vdev->ctx[vector].trigger) {
		free_irq(irq, vdev->ctx[vector].trigger);
		irq_bypass_unregister_producer(&vdev->ctx[vector].producer);
		kfree(vdev->ctx[vector].name);
		eventfd_ctx_put(vdev->ctx[vector].trigger);
		vdev->ctx[vector].trigger = NULL;
	}

	if (fd < 0)
		return 0;

	vdev->ctx[vector].name = kasprintf(GFP_KERNEL, "vfio-msi%s[%d](%s)",
					   msix ? "x" : "", vector,
					   pci_name(pdev));
	if (!vdev->ctx[vector].name)
		return -ENOMEM;

	trigger = eventfd_ctx_fdget(fd);
	if (IS_ERR(trigger)) {
		kfree(vdev->ctx[vector].name);
		return PTR_ERR(trigger);
	}

	/*
	 * The MSIx vector table resides in device memory which may be cleared
	 * via backdoor resets. We don't allow direct access to the vector
	 * table so even if a userspace driver attempts to save/restore around
	 * such a reset it would be unsuccessful. To avoid this, restore the
	 * cached value of the message prior to enabling.
	 */
	if (msix) {
		struct msi_msg msg;

		get_cached_msi_msg(irq, &msg);
		pci_write_msi_msg(irq, &msg);
	}

	ret = request_irq(irq, vfio_msihandler, 0,
			  vdev->ctx[vector].name, trigger);
	if (ret) {
		kfree(vdev->ctx[vector].name);
		eventfd_ctx_put(trigger);
		return ret;
	}

	vdev->ctx[vector].producer.token = trigger;
	vdev->ctx[vector].producer.irq = irq;
	ret = irq_bypass_register_producer(&vdev->ctx[vector].producer);
	if (unlikely(ret))
		dev_info(&pdev->dev,
		"irq bypass producer (token %p) registration fails: %d\n",
		vdev->ctx[vector].producer.token, ret);

	vdev->ctx[vector].trigger = trigger;

	return 0;
}