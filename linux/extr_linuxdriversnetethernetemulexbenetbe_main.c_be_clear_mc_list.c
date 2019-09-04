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
struct net_device {int dummy; } ;
struct be_adapter {scalar_t__ mc_count; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BE_IF_FLAGS_MULTICAST ; 
 int /*<<< orphan*/  OFF ; 
 int /*<<< orphan*/  __dev_mc_unsync (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be_cmd_rx_filter (struct be_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void be_clear_mc_list(struct be_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;

	__dev_mc_unsync(netdev, NULL);
	be_cmd_rx_filter(adapter, BE_IF_FLAGS_MULTICAST, OFF);
	adapter->mc_count = 0;
}