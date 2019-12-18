#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u64 ;
struct TYPE_3__ {unsigned int vec_idx; } ;
struct aq_vec_s {int /*<<< orphan*/  aq_hw; TYPE_2__* aq_hw_ops; int /*<<< orphan*/  napi; TYPE_1__ aq_ring_param; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int (* hw_irq_read ) (int /*<<< orphan*/ ,unsigned int*) ;int /*<<< orphan*/  (* hw_irq_enable ) (int /*<<< orphan*/ ,unsigned int) ;int /*<<< orphan*/  (* hw_irq_disable ) (int /*<<< orphan*/ ,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,unsigned int) ; 

irqreturn_t aq_vec_isr_legacy(int irq, void *private)
{
	struct aq_vec_s *self = private;
	u64 irq_mask = 0U;
	int err;

	if (!self)
		return IRQ_NONE;
	err = self->aq_hw_ops->hw_irq_read(self->aq_hw, &irq_mask);
	if (err < 0)
		return IRQ_NONE;

	if (irq_mask) {
		self->aq_hw_ops->hw_irq_disable(self->aq_hw,
			      1U << self->aq_ring_param.vec_idx);
		napi_schedule(&self->napi);
	} else {
		self->aq_hw_ops->hw_irq_enable(self->aq_hw, 1U);
		return IRQ_NONE;
	}

	return IRQ_HANDLED;
}