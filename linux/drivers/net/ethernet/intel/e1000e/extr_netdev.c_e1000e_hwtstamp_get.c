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
struct ifreq {int /*<<< orphan*/  ifr_data; } ;
struct e1000_adapter {int /*<<< orphan*/  hwtstamp_config; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int e1000e_hwtstamp_get(struct net_device *netdev, struct ifreq *ifr)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);

	return copy_to_user(ifr->ifr_data, &adapter->hwtstamp_config,
			    sizeof(adapter->hwtstamp_config)) ? -EFAULT : 0;
}