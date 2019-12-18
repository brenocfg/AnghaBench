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
struct TYPE_2__ {scalar_t__ remote_dev; } ;
struct vxlan_dev {TYPE_1__ default_dst; int /*<<< orphan*/  next; } ;
struct net_device {int dummy; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct vxlan_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_upper_dev_unlink (scalar_t__,struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdevice_queue (struct net_device*,struct list_head*) ; 
 int /*<<< orphan*/  vxlan_flush (struct vxlan_dev*,int) ; 

__attribute__((used)) static void vxlan_dellink(struct net_device *dev, struct list_head *head)
{
	struct vxlan_dev *vxlan = netdev_priv(dev);

	vxlan_flush(vxlan, true);

	list_del(&vxlan->next);
	unregister_netdevice_queue(dev, head);
	if (vxlan->default_dst.remote_dev)
		netdev_upper_dev_unlink(vxlan->default_dst.remote_dev, dev);
}