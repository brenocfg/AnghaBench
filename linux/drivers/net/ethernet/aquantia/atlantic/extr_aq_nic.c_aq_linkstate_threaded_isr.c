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
struct TYPE_4__ {int /*<<< orphan*/  link_irq_vec; } ;
struct aq_nic_s {TYPE_2__ aq_nic_cfg; int /*<<< orphan*/  aq_hw; TYPE_1__* aq_hw_ops; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* hw_irq_enable ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  aq_nic_update_link_status (struct aq_nic_s*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t aq_linkstate_threaded_isr(int irq, void *private)
{
	struct aq_nic_s *self = private;

	if (!self)
		return IRQ_NONE;

	aq_nic_update_link_status(self);

	self->aq_hw_ops->hw_irq_enable(self->aq_hw,
				       BIT(self->aq_nic_cfg.link_irq_vec));
	return IRQ_HANDLED;
}