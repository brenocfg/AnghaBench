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
struct hinic_dev {unsigned int flags; int /*<<< orphan*/  hwdev; int /*<<< orphan*/  rss_tmpl_idx; int /*<<< orphan*/  mgmt_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  HINIC_FUNC_PORT_DISABLE ; 
 unsigned int HINIC_INTF_UP ; 
 int /*<<< orphan*/  HINIC_PORT_DISABLE ; 
 int HINIC_RSS_ENABLE ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  free_rxqs (struct hinic_dev*) ; 
 int /*<<< orphan*/  free_txqs (struct hinic_dev*) ; 
 int /*<<< orphan*/  hinic_hwdev_ifdown (int /*<<< orphan*/ ) ; 
 int hinic_port_set_func_state (struct hinic_dev*,int /*<<< orphan*/ ) ; 
 int hinic_port_set_state (struct hinic_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hinic_rss_deinit (struct hinic_dev*) ; 
 int /*<<< orphan*/  hinic_rss_template_free (struct hinic_dev*,int /*<<< orphan*/ ) ; 
 struct hinic_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct hinic_dev*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_info (struct hinic_dev*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_tx_disable (struct net_device*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_nic_stats (struct hinic_dev*) ; 

__attribute__((used)) static int hinic_close(struct net_device *netdev)
{
	struct hinic_dev *nic_dev = netdev_priv(netdev);
	unsigned int flags;
	int err;

	down(&nic_dev->mgmt_lock);

	flags = nic_dev->flags;
	nic_dev->flags &= ~HINIC_INTF_UP;

	netif_carrier_off(netdev);
	netif_tx_disable(netdev);

	update_nic_stats(nic_dev);

	up(&nic_dev->mgmt_lock);

	err = hinic_port_set_func_state(nic_dev, HINIC_FUNC_PORT_DISABLE);
	if (err) {
		netif_err(nic_dev, drv, netdev,
			  "Failed to set func port state\n");
		nic_dev->flags |= (flags & HINIC_INTF_UP);
		return err;
	}

	err = hinic_port_set_state(nic_dev, HINIC_PORT_DISABLE);
	if (err) {
		netif_err(nic_dev, drv, netdev, "Failed to set port state\n");
		nic_dev->flags |= (flags & HINIC_INTF_UP);
		return err;
	}

	if (nic_dev->flags & HINIC_RSS_ENABLE) {
		hinic_rss_deinit(nic_dev);
		hinic_rss_template_free(nic_dev, nic_dev->rss_tmpl_idx);
	}

	free_rxqs(nic_dev);
	free_txqs(nic_dev);

	if (flags & HINIC_INTF_UP)
		hinic_hwdev_ifdown(nic_dev->hwdev);

	netif_info(nic_dev, drv, netdev, "HINIC_INTF is DOWN\n");
	return 0;
}