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
struct ixgbe_adapter {int num_vfs; int vf_rate_link_speed; TYPE_1__* vfinfo; int /*<<< orphan*/  link_up; } ;
struct TYPE_2__ {int tx_rate; } ;

/* Variables and functions */
 int EINVAL ; 
 int ixgbe_link_mbps (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_set_vf_rate_limit (struct ixgbe_adapter*,int) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 

int ixgbe_ndo_set_vf_bw(struct net_device *netdev, int vf, int min_tx_rate,
			int max_tx_rate)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);
	int link_speed;

	/* verify VF is active */
	if (vf >= adapter->num_vfs)
		return -EINVAL;

	/* verify link is up */
	if (!adapter->link_up)
		return -EINVAL;

	/* verify we are linked at 10Gbps */
	link_speed = ixgbe_link_mbps(adapter);
	if (link_speed != 10000)
		return -EINVAL;

	if (min_tx_rate)
		return -EINVAL;

	/* rate limit cannot be less than 10Mbs or greater than link speed */
	if (max_tx_rate && ((max_tx_rate <= 10) || (max_tx_rate > link_speed)))
		return -EINVAL;

	/* store values */
	adapter->vf_rate_link_speed = link_speed;
	adapter->vfinfo[vf].tx_rate = max_tx_rate;

	/* update hardware configuration */
	ixgbe_set_vf_rate_limit(adapter, vf);

	return 0;
}