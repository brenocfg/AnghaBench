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
struct net_device {int /*<<< orphan*/  name; } ;
struct be_adapter {int err_flags; TYPE_1__* pdev; struct net_device* netdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 

__attribute__((used)) static inline void be_set_error(struct be_adapter *adapter, int err_type)
{
	struct net_device *netdev = adapter->netdev;

	adapter->err_flags |= err_type;
	netif_carrier_off(netdev);

	dev_info(&adapter->pdev->dev, "%s: Link down\n", netdev->name);
}