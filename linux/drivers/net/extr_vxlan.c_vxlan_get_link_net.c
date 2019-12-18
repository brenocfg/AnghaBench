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
struct vxlan_dev {struct net* net; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct vxlan_dev* netdev_priv (struct net_device const*) ; 

__attribute__((used)) static struct net *vxlan_get_link_net(const struct net_device *dev)
{
	struct vxlan_dev *vxlan = netdev_priv(dev);

	return vxlan->net;
}