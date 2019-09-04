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
struct ethtool_flash {int /*<<< orphan*/  data; } ;
struct be_adapter {int dummy; } ;

/* Variables and functions */
 int be_load_fw (struct be_adapter*,int /*<<< orphan*/ ) ; 
 struct be_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int be_do_flash(struct net_device *netdev, struct ethtool_flash *efl)
{
	struct be_adapter *adapter = netdev_priv(netdev);

	return be_load_fw(adapter, efl->data);
}