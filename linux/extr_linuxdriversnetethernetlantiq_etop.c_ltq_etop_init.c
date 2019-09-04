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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int watchdog_timeo; int /*<<< orphan*/  addr_assign_type; } ;
struct ltq_etop_priv {TYPE_1__* pldata; } ;
struct TYPE_2__ {int /*<<< orphan*/  mac; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  NET_ADDR_RANDOM ; 
 int /*<<< orphan*/  eth_random_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ltq_etop_change_mtu (struct net_device*,int) ; 
 int /*<<< orphan*/  ltq_etop_hw_exit (struct net_device*) ; 
 int ltq_etop_hw_init (struct net_device*) ; 
 int ltq_etop_mdio_init (struct net_device*) ; 
 int ltq_etop_set_mac_address (struct net_device*,struct sockaddr*) ; 
 int /*<<< orphan*/  ltq_etop_set_multicast_list (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (struct sockaddr*,int /*<<< orphan*/ *,int) ; 
 struct ltq_etop_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int
ltq_etop_init(struct net_device *dev)
{
	struct ltq_etop_priv *priv = netdev_priv(dev);
	struct sockaddr mac;
	int err;
	bool random_mac = false;

	dev->watchdog_timeo = 10 * HZ;
	err = ltq_etop_hw_init(dev);
	if (err)
		goto err_hw;
	ltq_etop_change_mtu(dev, 1500);

	memcpy(&mac, &priv->pldata->mac, sizeof(struct sockaddr));
	if (!is_valid_ether_addr(mac.sa_data)) {
		pr_warn("etop: invalid MAC, using random\n");
		eth_random_addr(mac.sa_data);
		random_mac = true;
	}

	err = ltq_etop_set_mac_address(dev, &mac);
	if (err)
		goto err_netdev;

	/* Set addr_assign_type here, ltq_etop_set_mac_address would reset it. */
	if (random_mac)
		dev->addr_assign_type = NET_ADDR_RANDOM;

	ltq_etop_set_multicast_list(dev);
	err = ltq_etop_mdio_init(dev);
	if (err)
		goto err_netdev;
	return 0;

err_netdev:
	unregister_netdev(dev);
	free_netdev(dev);
err_hw:
	ltq_etop_hw_exit(dev);
	return err;
}