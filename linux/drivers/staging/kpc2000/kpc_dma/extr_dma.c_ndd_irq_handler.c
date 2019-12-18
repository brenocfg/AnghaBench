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
struct kpc_dma_device {int /*<<< orphan*/  irq_work; TYPE_1__* desc_completed; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {scalar_t__ MyDMAAddr; } ;

/* Variables and functions */
 int ENG_CTL_IRQ_ACTIVE ; 
 scalar_t__ GetEngineCompletePtr (struct kpc_dma_device*) ; 
 int GetEngineControl (struct kpc_dma_device*) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
irqreturn_t  ndd_irq_handler(int irq, void *dev_id)
{
	struct kpc_dma_device *ldev = (struct kpc_dma_device *)dev_id;

	if ((GetEngineControl(ldev) & ENG_CTL_IRQ_ACTIVE) || (ldev->desc_completed->MyDMAAddr != GetEngineCompletePtr(ldev)))
		schedule_work(&ldev->irq_work);

	return IRQ_HANDLED;
}