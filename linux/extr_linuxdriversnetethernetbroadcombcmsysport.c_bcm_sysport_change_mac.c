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
struct net_device {int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  addr_len; } ;
struct bcm_sysport_priv {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bcm_sysport_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  umac_set_hw_addr (struct bcm_sysport_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm_sysport_change_mac(struct net_device *dev, void *p)
{
	struct bcm_sysport_priv *priv = netdev_priv(dev);
	struct sockaddr *addr = p;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EINVAL;

	memcpy(dev->dev_addr, addr->sa_data, dev->addr_len);

	/* interface is disabled, changes to MAC will be reflected on next
	 * open call
	 */
	if (!netif_running(dev))
		return 0;

	umac_set_hw_addr(priv, dev->dev_addr);

	return 0;
}