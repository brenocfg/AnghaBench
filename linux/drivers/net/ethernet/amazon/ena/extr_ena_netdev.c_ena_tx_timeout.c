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
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_timeout; } ;
struct ena_adapter {int /*<<< orphan*/  syncp; TYPE_1__ dev_stats; int /*<<< orphan*/  reset_reason; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_FLAG_TRIGGER_RESET ; 
 int /*<<< orphan*/  ENA_REGS_RESET_OS_NETDEV_WD ; 
 struct ena_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct ena_adapter*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx_err ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ena_tx_timeout(struct net_device *dev)
{
	struct ena_adapter *adapter = netdev_priv(dev);

	/* Change the state of the device to trigger reset
	 * Check that we are not in the middle or a trigger already
	 */

	if (test_and_set_bit(ENA_FLAG_TRIGGER_RESET, &adapter->flags))
		return;

	adapter->reset_reason = ENA_REGS_RESET_OS_NETDEV_WD;
	u64_stats_update_begin(&adapter->syncp);
	adapter->dev_stats.tx_timeout++;
	u64_stats_update_end(&adapter->syncp);

	netif_err(adapter, tx_err, dev, "Transmit time out\n");
}