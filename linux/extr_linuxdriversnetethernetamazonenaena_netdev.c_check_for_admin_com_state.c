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
struct TYPE_2__ {int /*<<< orphan*/  admin_q_pause; } ;
struct ena_adapter {int /*<<< orphan*/  flags; int /*<<< orphan*/  reset_reason; int /*<<< orphan*/  syncp; TYPE_1__ dev_stats; int /*<<< orphan*/  netdev; int /*<<< orphan*/  ena_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_FLAG_TRIGGER_RESET ; 
 int /*<<< orphan*/  ENA_REGS_RESET_ADMIN_TO ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  ena_com_get_admin_running_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_err (struct ena_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void check_for_admin_com_state(struct ena_adapter *adapter)
{
	if (unlikely(!ena_com_get_admin_running_state(adapter->ena_dev))) {
		netif_err(adapter, drv, adapter->netdev,
			  "ENA admin queue is not in running state!\n");
		u64_stats_update_begin(&adapter->syncp);
		adapter->dev_stats.admin_q_pause++;
		u64_stats_update_end(&adapter->syncp);
		adapter->reset_reason = ENA_REGS_RESET_ADMIN_TO;
		set_bit(ENA_FLAG_TRIGGER_RESET, &adapter->flags);
	}
}