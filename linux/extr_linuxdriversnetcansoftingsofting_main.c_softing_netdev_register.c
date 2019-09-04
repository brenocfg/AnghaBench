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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct net_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_alert (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  netdev_alert (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_sysfs_group ; 
 int register_candev (struct net_device*) ; 
 scalar_t__ sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int softing_netdev_register(struct net_device *netdev)
{
	int ret;

	ret = register_candev(netdev);
	if (ret) {
		dev_alert(&netdev->dev, "register failed\n");
		return ret;
	}
	if (sysfs_create_group(&netdev->dev.kobj, &netdev_sysfs_group) < 0)
		netdev_alert(netdev, "sysfs group failed\n");

	return 0;
}