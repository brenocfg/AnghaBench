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
typedef  int /*<<< orphan*/  u32 ;
struct megasas_irq_context {int /*<<< orphan*/  MSIxIndex; scalar_t__ irq_poll_scheduled; struct megasas_instance* instance; } ;
struct megasas_instance {TYPE_1__* instancet; int /*<<< orphan*/  reset_flags; int /*<<< orphan*/  msix_vectors; scalar_t__ mask_interrupts; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* clear_intr ) (struct megasas_instance*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  MEGASAS_FUSION_IN_RESET ; 
 scalar_t__ complete_cmd_fusion (struct megasas_instance*,int /*<<< orphan*/ ,struct megasas_irq_context*) ; 
 int /*<<< orphan*/  stub1 (struct megasas_instance*) ; 
 int /*<<< orphan*/  stub2 (struct megasas_instance*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t megasas_isr_fusion(int irq, void *devp)
{
	struct megasas_irq_context *irq_context = devp;
	struct megasas_instance *instance = irq_context->instance;
	u32 mfiStatus;

	if (instance->mask_interrupts)
		return IRQ_NONE;

#if defined(ENABLE_IRQ_POLL)
	if (irq_context->irq_poll_scheduled)
		return IRQ_HANDLED;
#endif

	if (!instance->msix_vectors) {
		mfiStatus = instance->instancet->clear_intr(instance);
		if (!mfiStatus)
			return IRQ_NONE;
	}

	/* If we are resetting, bail */
	if (test_bit(MEGASAS_FUSION_IN_RESET, &instance->reset_flags)) {
		instance->instancet->clear_intr(instance);
		return IRQ_HANDLED;
	}

	return complete_cmd_fusion(instance, irq_context->MSIxIndex, irq_context)
			? IRQ_HANDLED : IRQ_NONE;
}