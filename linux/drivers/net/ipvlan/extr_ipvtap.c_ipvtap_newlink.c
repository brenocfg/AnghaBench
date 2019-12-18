#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  count_rx_dropped; int /*<<< orphan*/  update_features; int /*<<< orphan*/  count_tx_dropped; int /*<<< orphan*/  tap_features; int /*<<< orphan*/  queue_list; } ;
struct ipvtap_dev {TYPE_1__ vlan; TYPE_2__ tap; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TUN_OFFLOADS ; 
 int ipvlan_link_new (struct net*,struct net_device*,struct nlattr**,struct nlattr**,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  ipvtap_count_rx_dropped ; 
 int /*<<< orphan*/  ipvtap_count_tx_dropped ; 
 int /*<<< orphan*/  ipvtap_update_features ; 
 struct ipvtap_dev* netdev_priv (struct net_device*) ; 
 int netdev_rx_handler_register (struct net_device*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  netdev_rx_handler_unregister (struct net_device*) ; 
 int /*<<< orphan*/  tap_handle_frame ; 

__attribute__((used)) static int ipvtap_newlink(struct net *src_net, struct net_device *dev,
			  struct nlattr *tb[], struct nlattr *data[],
			  struct netlink_ext_ack *extack)
{
	struct ipvtap_dev *vlantap = netdev_priv(dev);
	int err;

	INIT_LIST_HEAD(&vlantap->tap.queue_list);

	/* Since macvlan supports all offloads by default, make
	 * tap support all offloads also.
	 */
	vlantap->tap.tap_features = TUN_OFFLOADS;
	vlantap->tap.count_tx_dropped = ipvtap_count_tx_dropped;
	vlantap->tap.update_features =	ipvtap_update_features;
	vlantap->tap.count_rx_dropped = ipvtap_count_rx_dropped;

	err = netdev_rx_handler_register(dev, tap_handle_frame, &vlantap->tap);
	if (err)
		return err;

	/* Don't put anything that may fail after macvlan_common_newlink
	 * because we can't undo what it does.
	 */
	err =  ipvlan_link_new(src_net, dev, tb, data, extack);
	if (err) {
		netdev_rx_handler_unregister(dev);
		return err;
	}

	vlantap->tap.dev = vlantap->vlan.dev;

	return err;
}