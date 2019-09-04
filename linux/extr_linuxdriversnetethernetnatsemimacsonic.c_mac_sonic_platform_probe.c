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
struct sonic_local {int /*<<< orphan*/ * device; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int mac_onboard_sonic_probe (struct net_device*) ; 
 struct sonic_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct net_device*) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  sonic_msg_init (struct net_device*) ; 

__attribute__((used)) static int mac_sonic_platform_probe(struct platform_device *pdev)
{
	struct net_device *dev;
	struct sonic_local *lp;
	int err;

	dev = alloc_etherdev(sizeof(struct sonic_local));
	if (!dev)
		return -ENOMEM;

	lp = netdev_priv(dev);
	lp->device = &pdev->dev;
	SET_NETDEV_DEV(dev, &pdev->dev);
	platform_set_drvdata(pdev, dev);

	err = mac_onboard_sonic_probe(dev);
	if (err)
		goto out;

	sonic_msg_init(dev);

	err = register_netdev(dev);
	if (err)
		goto out;

	return 0;

out:
	free_netdev(dev);

	return err;
}