#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ mbps; } ;
struct aq_nic_s {int /*<<< orphan*/  flags; int /*<<< orphan*/  ndev; TYPE_2__ link_status; TYPE_3__* aq_hw; TYPE_1__* aq_fw_ops; } ;
struct TYPE_6__ {TYPE_2__ aq_link_status; } ;
struct TYPE_4__ {int (* update_link_status ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AQ_CFG_DRV_NAME ; 
 int /*<<< orphan*/  AQ_NIC_FLAG_STARTED ; 
 int /*<<< orphan*/  AQ_NIC_LINK_DOWN ; 
 int /*<<< orphan*/  aq_nic_update_interrupt_moderation_settings (struct aq_nic_s*) ; 
 int /*<<< orphan*/  aq_utils_obj_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aq_utils_obj_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_wake_all_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int stub1 (TYPE_3__*) ; 

__attribute__((used)) static int aq_nic_update_link_status(struct aq_nic_s *self)
{
	int err = self->aq_fw_ops->update_link_status(self->aq_hw);

	if (err)
		return err;

	if (self->link_status.mbps != self->aq_hw->aq_link_status.mbps) {
		pr_info("%s: link change old %d new %d\n",
			AQ_CFG_DRV_NAME, self->link_status.mbps,
			self->aq_hw->aq_link_status.mbps);
		aq_nic_update_interrupt_moderation_settings(self);
	}

	self->link_status = self->aq_hw->aq_link_status;
	if (!netif_carrier_ok(self->ndev) && self->link_status.mbps) {
		aq_utils_obj_set(&self->flags,
				 AQ_NIC_FLAG_STARTED);
		aq_utils_obj_clear(&self->flags,
				   AQ_NIC_LINK_DOWN);
		netif_carrier_on(self->ndev);
		netif_tx_wake_all_queues(self->ndev);
	}
	if (netif_carrier_ok(self->ndev) && !self->link_status.mbps) {
		netif_carrier_off(self->ndev);
		netif_tx_disable(self->ndev);
		aq_utils_obj_set(&self->flags, AQ_NIC_LINK_DOWN);
	}
	return 0;
}