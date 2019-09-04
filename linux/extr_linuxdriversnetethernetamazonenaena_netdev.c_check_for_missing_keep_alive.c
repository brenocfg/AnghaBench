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
struct TYPE_2__ {int /*<<< orphan*/  wd_expired; } ;
struct ena_adapter {scalar_t__ keep_alive_timeout; scalar_t__ last_keep_alive_jiffies; int /*<<< orphan*/  flags; int /*<<< orphan*/  reset_reason; int /*<<< orphan*/  syncp; TYPE_1__ dev_stats; int /*<<< orphan*/  netdev; int /*<<< orphan*/  wd_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_FLAG_TRIGGER_RESET ; 
 scalar_t__ ENA_HW_HINTS_NO_TIMEOUT ; 
 int /*<<< orphan*/  ENA_REGS_RESET_KEEP_ALIVE_TO ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  netif_err (struct ena_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 unsigned long round_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time_is_before_jiffies (unsigned long) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_for_missing_keep_alive(struct ena_adapter *adapter)
{
	unsigned long keep_alive_expired;

	if (!adapter->wd_state)
		return;

	if (adapter->keep_alive_timeout == ENA_HW_HINTS_NO_TIMEOUT)
		return;

	keep_alive_expired = round_jiffies(adapter->last_keep_alive_jiffies +
					   adapter->keep_alive_timeout);
	if (unlikely(time_is_before_jiffies(keep_alive_expired))) {
		netif_err(adapter, drv, adapter->netdev,
			  "Keep alive watchdog timeout.\n");
		u64_stats_update_begin(&adapter->syncp);
		adapter->dev_stats.wd_expired++;
		u64_stats_update_end(&adapter->syncp);
		adapter->reset_reason = ENA_REGS_RESET_KEEP_ALIVE_TO;
		set_bit(ENA_FLAG_TRIGGER_RESET, &adapter->flags);
	}
}