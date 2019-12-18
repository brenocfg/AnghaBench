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
struct be_adapter {int uc_macs; int /*<<< orphan*/ * pmac_id; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dev_uc_unsync (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be_uc_mac_del (struct be_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void be_clear_uc_list(struct be_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	int i;

	__dev_uc_unsync(netdev, NULL);
	for (i = 0; i < adapter->uc_macs; i++)
		be_uc_mac_del(adapter, adapter->pmac_id[i + 1]);

	adapter->uc_macs = 0;
}