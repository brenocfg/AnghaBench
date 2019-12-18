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
struct vmci_guest_device {int /*<<< orphan*/  data_buffer; int /*<<< orphan*/  notification_base; scalar_t__ notification_bitmap; int /*<<< orphan*/  bm_tasklet; int /*<<< orphan*/  datagram_tasklet; scalar_t__ exclusive_vectors; scalar_t__ iobase; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ VMCI_CONTROL_ADDR ; 
 int /*<<< orphan*/  VMCI_CONTROL_RESET ; 
 int /*<<< orphan*/  VMCI_EVENT_CTX_ID_UPDATE ; 
 int VMCI_SUCCESS ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctx_update_sub_id ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct vmci_guest_device*) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 
 struct vmci_guest_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_irq_vector (struct pci_dev*,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vmci_dev_g ; 
 int /*<<< orphan*/  vmci_dev_spinlock ; 
 int vmci_event_unsubscribe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmci_num_guest_devices ; 
 int /*<<< orphan*/ * vmci_pdev ; 
 int /*<<< orphan*/  vmci_qp_guest_endpoints_exit () ; 

__attribute__((used)) static void vmci_guest_remove_device(struct pci_dev *pdev)
{
	struct vmci_guest_device *vmci_dev = pci_get_drvdata(pdev);
	int vmci_err;

	dev_dbg(&pdev->dev, "Removing device\n");

	atomic_dec(&vmci_num_guest_devices);

	vmci_qp_guest_endpoints_exit();

	vmci_err = vmci_event_unsubscribe(ctx_update_sub_id);
	if (vmci_err < VMCI_SUCCESS)
		dev_warn(&pdev->dev,
			 "Failed to unsubscribe from event (type=%d) with subscriber (ID=0x%x): %d\n",
			 VMCI_EVENT_CTX_ID_UPDATE, ctx_update_sub_id, vmci_err);

	spin_lock_irq(&vmci_dev_spinlock);
	vmci_dev_g = NULL;
	vmci_pdev = NULL;
	spin_unlock_irq(&vmci_dev_spinlock);

	dev_dbg(&pdev->dev, "Resetting vmci device\n");
	iowrite32(VMCI_CONTROL_RESET, vmci_dev->iobase + VMCI_CONTROL_ADDR);

	/*
	 * Free IRQ and then disable MSI/MSI-X as appropriate.  For
	 * MSI-X, we might have multiple vectors, each with their own
	 * IRQ, which we must free too.
	 */
	if (vmci_dev->exclusive_vectors)
		free_irq(pci_irq_vector(pdev, 1), vmci_dev);
	free_irq(pci_irq_vector(pdev, 0), vmci_dev);
	pci_free_irq_vectors(pdev);

	tasklet_kill(&vmci_dev->datagram_tasklet);
	tasklet_kill(&vmci_dev->bm_tasklet);

	if (vmci_dev->notification_bitmap) {
		/*
		 * The device reset above cleared the bitmap state of the
		 * device, so we can safely free it here.
		 */

		dma_free_coherent(&pdev->dev, PAGE_SIZE,
				  vmci_dev->notification_bitmap,
				  vmci_dev->notification_base);
	}

	vfree(vmci_dev->data_buffer);

	/* The rest are managed resources and will be freed by PCI core */
}