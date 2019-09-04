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
struct TYPE_2__ {int /*<<< orphan*/  mac_addr; } ;
struct cmac {int dummy; } ;
struct port_info {int /*<<< orphan*/  link_config; int /*<<< orphan*/  phy; TYPE_1__ iscsic; struct cmac mac; } ;
struct net_device {int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  LAN_MAC_IDX ; 
 int MAC_DIRECTION_RX ; 
 int MAC_DIRECTION_TX ; 
 int /*<<< orphan*/  MAX_MAC_IDX ; 
 int /*<<< orphan*/  SAN_MAC_IDX ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  t3_link_start (int /*<<< orphan*/ *,struct cmac*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t3_mac_enable (struct cmac*,int) ; 
 int /*<<< orphan*/  t3_mac_reset (struct cmac*) ; 
 int /*<<< orphan*/  t3_mac_set_address (struct cmac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_mac_set_mtu (struct cmac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_mac_set_num_ucast (struct cmac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_mac_set_rx_mode (struct cmac*,struct net_device*) ; 

__attribute__((used)) static void link_start(struct net_device *dev)
{
	struct port_info *pi = netdev_priv(dev);
	struct cmac *mac = &pi->mac;

	t3_mac_reset(mac);
	t3_mac_set_num_ucast(mac, MAX_MAC_IDX);
	t3_mac_set_mtu(mac, dev->mtu);
	t3_mac_set_address(mac, LAN_MAC_IDX, dev->dev_addr);
	t3_mac_set_address(mac, SAN_MAC_IDX, pi->iscsic.mac_addr);
	t3_mac_set_rx_mode(mac, dev);
	t3_link_start(&pi->phy, mac, &pi->link_config);
	t3_mac_enable(mac, MAC_DIRECTION_RX | MAC_DIRECTION_TX);
}