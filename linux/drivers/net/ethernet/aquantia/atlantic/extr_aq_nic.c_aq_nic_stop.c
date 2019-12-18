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
struct aq_vec_s {int dummy; } ;
struct TYPE_3__ {scalar_t__ is_polling; } ;
struct aq_nic_s {unsigned int aq_vecs; int /*<<< orphan*/  aq_hw; TYPE_2__* aq_hw_ops; struct aq_vec_s** aq_vec; int /*<<< orphan*/  polling_timer; TYPE_1__ aq_nic_cfg; int /*<<< orphan*/  service_task; int /*<<< orphan*/  service_timer; int /*<<< orphan*/  ndev; } ;
struct TYPE_4__ {int (* hw_stop ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* hw_irq_disable ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AQ_CFG_IRQ_MASK ; 
 int /*<<< orphan*/  aq_pci_func_free_irqs (struct aq_nic_s*) ; 
 int /*<<< orphan*/  aq_vec_stop (struct aq_vec_s*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ) ; 

int aq_nic_stop(struct aq_nic_s *self)
{
	struct aq_vec_s *aq_vec = NULL;
	unsigned int i = 0U;

	netif_tx_disable(self->ndev);
	netif_carrier_off(self->ndev);

	del_timer_sync(&self->service_timer);
	cancel_work_sync(&self->service_task);

	self->aq_hw_ops->hw_irq_disable(self->aq_hw, AQ_CFG_IRQ_MASK);

	if (self->aq_nic_cfg.is_polling)
		del_timer_sync(&self->polling_timer);
	else
		aq_pci_func_free_irqs(self);

	for (i = 0U, aq_vec = self->aq_vec[0];
		self->aq_vecs > i; ++i, aq_vec = self->aq_vec[i])
		aq_vec_stop(aq_vec);

	return self->aq_hw_ops->hw_stop(self->aq_hw);
}