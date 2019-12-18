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
struct hl_device {int /*<<< orphan*/  pdev; TYPE_1__ asic_prop; struct goya_device* asic_specific; } ;
struct goya_device {int hw_cap_initialized; } ;

/* Variables and functions */
 int GOYA_EVENT_QUEUE_MSIX_IDX ; 
 int HW_CAP_MSIX ; 
 int /*<<< orphan*/  pci_irq_vector (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void goya_sync_irqs(struct hl_device *hdev)
{
	struct goya_device *goya = hdev->asic_specific;
	int i;

	if (!(goya->hw_cap_initialized & HW_CAP_MSIX))
		return;

	/* Wait for all pending IRQs to be finished */
	for (i = 0 ; i < hdev->asic_prop.completion_queues_count ; i++)
		synchronize_irq(pci_irq_vector(hdev->pdev, i));

	synchronize_irq(pci_irq_vector(hdev->pdev, GOYA_EVENT_QUEUE_MSIX_IDX));
}