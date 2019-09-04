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
struct timer_list {int dummy; } ;
struct aq_nic_s {int /*<<< orphan*/  service_timer; int /*<<< orphan*/  ndev; int /*<<< orphan*/  aq_hw; TYPE_1__* aq_fw_ops; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* update_stats ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int AQ_CFG_SERVICE_TIMER_INTERVAL ; 
 int /*<<< orphan*/  AQ_NIC_FLAGS_IS_NOT_READY ; 
 int aq_nic_update_link_status (struct aq_nic_s*) ; 
 int /*<<< orphan*/  aq_nic_update_ndev_stats (struct aq_nic_s*) ; 
 scalar_t__ aq_utils_obj_test (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct aq_nic_s* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int max (int,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  netif_carrier_ok (int /*<<< orphan*/ ) ; 
 struct aq_nic_s* self ; 
 int /*<<< orphan*/  service_timer ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aq_nic_service_timer_cb(struct timer_list *t)
{
	struct aq_nic_s *self = from_timer(self, t, service_timer);
	int ctimer = AQ_CFG_SERVICE_TIMER_INTERVAL;
	int err = 0;

	if (aq_utils_obj_test(&self->flags, AQ_NIC_FLAGS_IS_NOT_READY))
		goto err_exit;

	err = aq_nic_update_link_status(self);
	if (err)
		goto err_exit;

	if (self->aq_fw_ops->update_stats)
		self->aq_fw_ops->update_stats(self->aq_hw);

	aq_nic_update_ndev_stats(self);

	/* If no link - use faster timer rate to detect link up asap */
	if (!netif_carrier_ok(self->ndev))
		ctimer = max(ctimer / 2, 1);

err_exit:
	mod_timer(&self->service_timer, jiffies + ctimer);
}