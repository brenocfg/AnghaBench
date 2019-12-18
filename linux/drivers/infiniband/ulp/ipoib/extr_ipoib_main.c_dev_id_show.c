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
struct net_device {scalar_t__ dev_port; scalar_t__ dev_id; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 int /*<<< orphan*/  netdev_info_once (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,scalar_t__) ; 
 struct net_device* to_net_dev (struct device*) ; 

__attribute__((used)) static ssize_t dev_id_show(struct device *dev,
			   struct device_attribute *attr, char *buf)
{
	struct net_device *ndev = to_net_dev(dev);

	/*
	 * ndev->dev_port will be equal to 0 in old kernel prior to commit
	 * 9b8b2a323008 ("IB/ipoib: Use dev_port to expose network interface
	 * port numbers") Zero was chosen as special case for user space
	 * applications to fallback and query dev_id to check if it has
	 * different value or not.
	 *
	 * Don't print warning in such scenario.
	 *
	 * https://github.com/systemd/systemd/blob/master/src/udev/udev-builtin-net_id.c#L358
	 */
	if (ndev->dev_port && ndev->dev_id == ndev->dev_port)
		netdev_info_once(ndev,
			"\"%s\" wants to know my dev_id. Should it look at dev_port instead? See Documentation/ABI/testing/sysfs-class-net for more info.\n",
			current->comm);

	return sprintf(buf, "%#x\n", ndev->dev_id);
}