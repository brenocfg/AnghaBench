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
struct xenbus_device_id {int dummy; } ;
struct xenbus_device {int /*<<< orphan*/  dev; } ;
struct netfront_info {TYPE_1__* netdev; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** sysfs_groups; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct net_device*) ; 
 int PTR_ERR (struct net_device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct netfront_info*) ; 
 struct netfront_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (struct xenbus_device*,int,char*) ; 
 struct net_device* xennet_create_dev (struct xenbus_device*) ; 
 int /*<<< orphan*/  xennet_dev_group ; 

__attribute__((used)) static int netfront_probe(struct xenbus_device *dev,
			  const struct xenbus_device_id *id)
{
	int err;
	struct net_device *netdev;
	struct netfront_info *info;

	netdev = xennet_create_dev(dev);
	if (IS_ERR(netdev)) {
		err = PTR_ERR(netdev);
		xenbus_dev_fatal(dev, err, "creating netdev");
		return err;
	}

	info = netdev_priv(netdev);
	dev_set_drvdata(&dev->dev, info);
#ifdef CONFIG_SYSFS
	info->netdev->sysfs_groups[0] = &xennet_dev_group;
#endif

	return 0;
}