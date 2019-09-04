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
 int /*<<< orphan*/  free_candev (struct net_device*) ; 
 int /*<<< orphan*/  netdev_sysfs_group ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_candev (struct net_device*) ; 

__attribute__((used)) static void softing_netdev_cleanup(struct net_device *netdev)
{
	sysfs_remove_group(&netdev->dev.kobj, &netdev_sysfs_group);
	unregister_candev(netdev);
	free_candev(netdev);
}