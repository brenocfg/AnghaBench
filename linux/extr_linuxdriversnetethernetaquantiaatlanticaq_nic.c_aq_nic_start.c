#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct aq_vec_s {int dummy; } ;
struct TYPE_8__ {scalar_t__ is_polling; } ;
struct TYPE_7__ {int /*<<< orphan*/  count; int /*<<< orphan*/  ar; } ;
struct aq_nic_s {unsigned int aq_vecs; TYPE_4__* ndev; int /*<<< orphan*/  aq_hw; TYPE_3__* aq_hw_ops; struct aq_vec_s** aq_vec; int /*<<< orphan*/  polling_timer; TYPE_2__ aq_nic_cfg; int /*<<< orphan*/  service_timer; int /*<<< orphan*/  packet_filter; TYPE_1__ mc_list; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;
struct TYPE_9__ {int (* hw_multicast_list_set ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* hw_packet_filter_set ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* hw_start ) (int /*<<< orphan*/ ) ;int (* hw_irq_enable ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AQ_CFG_IRQ_MASK ; 
 scalar_t__ AQ_CFG_POLLING_TIMER_INTERVAL ; 
 scalar_t__ AQ_CFG_SERVICE_TIMER_INTERVAL ; 
 int /*<<< orphan*/  aq_nic_polling_timer_cb ; 
 int /*<<< orphan*/  aq_nic_service_timer_cb ; 
 int aq_nic_update_interrupt_moderation_settings (struct aq_nic_s*) ; 
 int aq_pci_func_alloc_irq (struct aq_nic_s*,unsigned int,int /*<<< orphan*/ ,struct aq_vec_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aq_vec_get_affinity_mask (struct aq_vec_s*) ; 
 int aq_vec_start (struct aq_vec_s*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int netif_set_real_num_rx_queues (TYPE_4__*,unsigned int) ; 
 int netif_set_real_num_tx_queues (TYPE_4__*,unsigned int) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (TYPE_4__*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub3 (int /*<<< orphan*/ ) ; 
 int stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int aq_nic_start(struct aq_nic_s *self)
{
	struct aq_vec_s *aq_vec = NULL;
	int err = 0;
	unsigned int i = 0U;

	err = self->aq_hw_ops->hw_multicast_list_set(self->aq_hw,
						    self->mc_list.ar,
						    self->mc_list.count);
	if (err < 0)
		goto err_exit;

	err = self->aq_hw_ops->hw_packet_filter_set(self->aq_hw,
						   self->packet_filter);
	if (err < 0)
		goto err_exit;

	for (i = 0U, aq_vec = self->aq_vec[0];
		self->aq_vecs > i; ++i, aq_vec = self->aq_vec[i]) {
		err = aq_vec_start(aq_vec);
		if (err < 0)
			goto err_exit;
	}

	err = self->aq_hw_ops->hw_start(self->aq_hw);
	if (err < 0)
		goto err_exit;

	err = aq_nic_update_interrupt_moderation_settings(self);
	if (err)
		goto err_exit;
	timer_setup(&self->service_timer, aq_nic_service_timer_cb, 0);
	mod_timer(&self->service_timer, jiffies +
			AQ_CFG_SERVICE_TIMER_INTERVAL);

	if (self->aq_nic_cfg.is_polling) {
		timer_setup(&self->polling_timer, aq_nic_polling_timer_cb, 0);
		mod_timer(&self->polling_timer, jiffies +
			  AQ_CFG_POLLING_TIMER_INTERVAL);
	} else {
		for (i = 0U, aq_vec = self->aq_vec[0];
			self->aq_vecs > i; ++i, aq_vec = self->aq_vec[i]) {
			err = aq_pci_func_alloc_irq(self, i,
						    self->ndev->name, aq_vec,
						    aq_vec_get_affinity_mask(aq_vec));
			if (err < 0)
				goto err_exit;
		}

		err = self->aq_hw_ops->hw_irq_enable(self->aq_hw,
				    AQ_CFG_IRQ_MASK);
		if (err < 0)
			goto err_exit;
	}

	err = netif_set_real_num_tx_queues(self->ndev, self->aq_vecs);
	if (err < 0)
		goto err_exit;

	err = netif_set_real_num_rx_queues(self->ndev, self->aq_vecs);
	if (err < 0)
		goto err_exit;

	netif_tx_start_all_queues(self->ndev);

err_exit:
	return err;
}