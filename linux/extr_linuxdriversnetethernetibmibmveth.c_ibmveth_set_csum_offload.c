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
typedef  int u32 ;
struct net_device {int /*<<< orphan*/  features; } ;
struct ibmveth_adapter {int pool_config; int fw_ipv4_csum_support; int fw_ipv6_csum_support; int rx_csum; TYPE_1__* vdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  unit_address; } ;

/* Variables and functions */
 int EIO ; 
 long H_SUCCESS ; 
 unsigned long IBMVETH_ILLAN_IPV4_TCP_CSUM ; 
 unsigned long IBMVETH_ILLAN_IPV6_TCP_CSUM ; 
 unsigned long IBMVETH_ILLAN_PADDED_PKT_CSUM ; 
 int /*<<< orphan*/  NETIF_F_IPV6_CSUM ; 
 int /*<<< orphan*/  NETIF_F_IP_CSUM ; 
 long h_illan_attributes (int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned long*) ; 
 int /*<<< orphan*/  ibmveth_close (struct net_device*) ; 
 int ibmveth_open (struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int,long,...) ; 
 struct ibmveth_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int ibmveth_set_csum_offload(struct net_device *dev, u32 data)
{
	struct ibmveth_adapter *adapter = netdev_priv(dev);
	unsigned long set_attr, clr_attr, ret_attr;
	unsigned long set_attr6, clr_attr6;
	long ret, ret4, ret6;
	int rc1 = 0, rc2 = 0;
	int restart = 0;

	if (netif_running(dev)) {
		restart = 1;
		adapter->pool_config = 1;
		ibmveth_close(dev);
		adapter->pool_config = 0;
	}

	set_attr = 0;
	clr_attr = 0;
	set_attr6 = 0;
	clr_attr6 = 0;

	if (data) {
		set_attr = IBMVETH_ILLAN_IPV4_TCP_CSUM;
		set_attr6 = IBMVETH_ILLAN_IPV6_TCP_CSUM;
	} else {
		clr_attr = IBMVETH_ILLAN_IPV4_TCP_CSUM;
		clr_attr6 = IBMVETH_ILLAN_IPV6_TCP_CSUM;
	}

	ret = h_illan_attributes(adapter->vdev->unit_address, 0, 0, &ret_attr);

	if (ret == H_SUCCESS &&
	    (ret_attr & IBMVETH_ILLAN_PADDED_PKT_CSUM)) {
		ret4 = h_illan_attributes(adapter->vdev->unit_address, clr_attr,
					 set_attr, &ret_attr);

		if (ret4 != H_SUCCESS) {
			netdev_err(dev, "unable to change IPv4 checksum "
					"offload settings. %d rc=%ld\n",
					data, ret4);

			h_illan_attributes(adapter->vdev->unit_address,
					   set_attr, clr_attr, &ret_attr);

			if (data == 1)
				dev->features &= ~NETIF_F_IP_CSUM;

		} else {
			adapter->fw_ipv4_csum_support = data;
		}

		ret6 = h_illan_attributes(adapter->vdev->unit_address,
					 clr_attr6, set_attr6, &ret_attr);

		if (ret6 != H_SUCCESS) {
			netdev_err(dev, "unable to change IPv6 checksum "
					"offload settings. %d rc=%ld\n",
					data, ret6);

			h_illan_attributes(adapter->vdev->unit_address,
					   set_attr6, clr_attr6, &ret_attr);

			if (data == 1)
				dev->features &= ~NETIF_F_IPV6_CSUM;

		} else
			adapter->fw_ipv6_csum_support = data;

		if (ret4 == H_SUCCESS || ret6 == H_SUCCESS)
			adapter->rx_csum = data;
		else
			rc1 = -EIO;
	} else {
		rc1 = -EIO;
		netdev_err(dev, "unable to change checksum offload settings."
				     " %d rc=%ld ret_attr=%lx\n", data, ret,
				     ret_attr);
	}

	if (restart)
		rc2 = ibmveth_open(dev);

	return rc1 ? rc1 : rc2;
}