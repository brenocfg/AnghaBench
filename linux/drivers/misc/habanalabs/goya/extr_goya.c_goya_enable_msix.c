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
struct TYPE_2__ {int completion_queues_count; } ;
struct hl_device {int /*<<< orphan*/  pdev; int /*<<< orphan*/ * completion_queue; int /*<<< orphan*/  dev; int /*<<< orphan*/  event_queue; TYPE_1__ asic_prop; struct goya_device* asic_specific; } ;
struct goya_device {int hw_cap_initialized; } ;

/* Variables and functions */
 size_t GOYA_EVENT_QUEUE_MSIX_IDX ; 
 int /*<<< orphan*/  GOYA_MSIX_ENTRIES ; 
 int HW_CAP_MSIX ; 
 int /*<<< orphan*/  PCI_IRQ_MSIX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  free_irq (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * goya_irq_name ; 
 int /*<<< orphan*/  hl_irq_handler_cq ; 
 int /*<<< orphan*/  hl_irq_handler_eq ; 
 int pci_alloc_irq_vectors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (int /*<<< orphan*/ ) ; 
 int pci_irq_vector (int /*<<< orphan*/ ,int) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int goya_enable_msix(struct hl_device *hdev)
{
	struct goya_device *goya = hdev->asic_specific;
	int cq_cnt = hdev->asic_prop.completion_queues_count;
	int rc, i, irq_cnt_init, irq;

	if (goya->hw_cap_initialized & HW_CAP_MSIX)
		return 0;

	rc = pci_alloc_irq_vectors(hdev->pdev, GOYA_MSIX_ENTRIES,
				GOYA_MSIX_ENTRIES, PCI_IRQ_MSIX);
	if (rc < 0) {
		dev_err(hdev->dev,
			"MSI-X: Failed to enable support -- %d/%d\n",
			GOYA_MSIX_ENTRIES, rc);
		return rc;
	}

	for (i = 0, irq_cnt_init = 0 ; i < cq_cnt ; i++, irq_cnt_init++) {
		irq = pci_irq_vector(hdev->pdev, i);
		rc = request_irq(irq, hl_irq_handler_cq, 0, goya_irq_name[i],
				&hdev->completion_queue[i]);
		if (rc) {
			dev_err(hdev->dev, "Failed to request IRQ %d", irq);
			goto free_irqs;
		}
	}

	irq = pci_irq_vector(hdev->pdev, GOYA_EVENT_QUEUE_MSIX_IDX);

	rc = request_irq(irq, hl_irq_handler_eq, 0,
			goya_irq_name[GOYA_EVENT_QUEUE_MSIX_IDX],
			&hdev->event_queue);
	if (rc) {
		dev_err(hdev->dev, "Failed to request IRQ %d", irq);
		goto free_irqs;
	}

	goya->hw_cap_initialized |= HW_CAP_MSIX;
	return 0;

free_irqs:
	for (i = 0 ; i < irq_cnt_init ; i++)
		free_irq(pci_irq_vector(hdev->pdev, i),
			&hdev->completion_queue[i]);

	pci_free_irq_vectors(hdev->pdev);
	return rc;
}