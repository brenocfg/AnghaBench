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
struct net_device {int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  addr_assign_type; int /*<<< orphan*/  addr_len; } ;
struct hisi_femac_priv {int dummy; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  NET_ADDR_RANDOM ; 
 int /*<<< orphan*/  hisi_femac_set_hw_mac_addr (struct hisi_femac_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hisi_femac_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int hisi_femac_set_mac_address(struct net_device *dev, void *p)
{
	struct hisi_femac_priv *priv = netdev_priv(dev);
	struct sockaddr *skaddr = p;

	if (!is_valid_ether_addr(skaddr->sa_data))
		return -EADDRNOTAVAIL;

	memcpy(dev->dev_addr, skaddr->sa_data, dev->addr_len);
	dev->addr_assign_type &= ~NET_ADDR_RANDOM;

	hisi_femac_set_hw_mac_addr(priv, dev->dev_addr);

	return 0;
}