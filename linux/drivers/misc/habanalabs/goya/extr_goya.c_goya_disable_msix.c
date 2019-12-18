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
struct hl_device {int /*<<< orphan*/  pdev; int /*<<< orphan*/ * completion_queue; TYPE_1__ asic_prop; int /*<<< orphan*/  event_queue; struct goya_device* asic_specific; } ;
struct goya_device {int hw_cap_initialized; } ;

/* Variables and functions */
 int GOYA_EVENT_QUEUE_MSIX_IDX ; 
 int HW_CAP_MSIX ; 
 int /*<<< orphan*/  free_irq (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  goya_sync_irqs (struct hl_device*) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (int /*<<< orphan*/ ) ; 
 int pci_irq_vector (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void goya_disable_msix(struct hl_device *hdev)
{
	struct goya_device *goya = hdev->asic_specific;
	int i, irq;

	if (!(goya->hw_cap_initialized & HW_CAP_MSIX))
		return;

	goya_sync_irqs(hdev);

	irq = pci_irq_vector(hdev->pdev, GOYA_EVENT_QUEUE_MSIX_IDX);
	free_irq(irq, &hdev->event_queue);

	for (i = 0 ; i < hdev->asic_prop.completion_queues_count ; i++) {
		irq = pci_irq_vector(hdev->pdev, i);
		free_irq(irq, &hdev->completion_queue[i]);
	}

	pci_free_irq_vectors(hdev->pdev);

	goya->hw_cap_initialized &= ~HW_CAP_MSIX;
}