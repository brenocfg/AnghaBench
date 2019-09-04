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
struct dpu_hw_intr_ops {int /*<<< orphan*/  get_interrupt_status; int /*<<< orphan*/  clear_intr_status_nolock; int /*<<< orphan*/  clear_interrupt_status; int /*<<< orphan*/  get_interrupt_statuses; int /*<<< orphan*/  get_valid_interrupts; int /*<<< orphan*/  disable_all_irqs; int /*<<< orphan*/  clear_all_irqs; int /*<<< orphan*/  dispatch_irqs; int /*<<< orphan*/  disable_irq; int /*<<< orphan*/  enable_irq; int /*<<< orphan*/  irq_idx_lookup; int /*<<< orphan*/  set_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  dpu_hw_intr_clear_interrupt_status ; 
 int /*<<< orphan*/  dpu_hw_intr_clear_intr_status_nolock ; 
 int /*<<< orphan*/  dpu_hw_intr_clear_irqs ; 
 int /*<<< orphan*/  dpu_hw_intr_disable_irq ; 
 int /*<<< orphan*/  dpu_hw_intr_disable_irqs ; 
 int /*<<< orphan*/  dpu_hw_intr_dispatch_irq ; 
 int /*<<< orphan*/  dpu_hw_intr_enable_irq ; 
 int /*<<< orphan*/  dpu_hw_intr_get_interrupt_status ; 
 int /*<<< orphan*/  dpu_hw_intr_get_interrupt_statuses ; 
 int /*<<< orphan*/  dpu_hw_intr_get_valid_interrupts ; 
 int /*<<< orphan*/  dpu_hw_intr_irqidx_lookup ; 
 int /*<<< orphan*/  dpu_hw_intr_set_mask ; 

__attribute__((used)) static void __setup_intr_ops(struct dpu_hw_intr_ops *ops)
{
	ops->set_mask = dpu_hw_intr_set_mask;
	ops->irq_idx_lookup = dpu_hw_intr_irqidx_lookup;
	ops->enable_irq = dpu_hw_intr_enable_irq;
	ops->disable_irq = dpu_hw_intr_disable_irq;
	ops->dispatch_irqs = dpu_hw_intr_dispatch_irq;
	ops->clear_all_irqs = dpu_hw_intr_clear_irqs;
	ops->disable_all_irqs = dpu_hw_intr_disable_irqs;
	ops->get_valid_interrupts = dpu_hw_intr_get_valid_interrupts;
	ops->get_interrupt_statuses = dpu_hw_intr_get_interrupt_statuses;
	ops->clear_interrupt_status = dpu_hw_intr_clear_interrupt_status;
	ops->clear_intr_status_nolock = dpu_hw_intr_clear_intr_status_nolock;
	ops->get_interrupt_status = dpu_hw_intr_get_interrupt_status;
}