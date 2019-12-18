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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; } ;
struct ks_wlan_private {int mac_address_valid; int /*<<< orphan*/  eth_addr; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  SME_MACADDRESS_SET_REQUEST ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostif_sme_enqueue (struct ks_wlan_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 struct ks_wlan_private* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static
int ks_wlan_set_mac_address(struct net_device *dev, void *addr)
{
	struct ks_wlan_private *priv = netdev_priv(dev);
	struct sockaddr *mac_addr = (struct sockaddr *)addr;

	if (netif_running(dev))
		return -EBUSY;
	memcpy(dev->dev_addr, mac_addr->sa_data, dev->addr_len);
	ether_addr_copy(priv->eth_addr, mac_addr->sa_data);

	priv->mac_address_valid = false;
	hostif_sme_enqueue(priv, SME_MACADDRESS_SET_REQUEST);
	netdev_info(dev, "ks_wlan:  MAC ADDRESS = %pM\n", priv->eth_addr);
	return 0;
}