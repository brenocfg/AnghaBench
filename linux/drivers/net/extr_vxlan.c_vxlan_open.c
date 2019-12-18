#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ age_interval; } ;
struct TYPE_3__ {int /*<<< orphan*/  remote_ip; } ;
struct vxlan_dev {int /*<<< orphan*/  age_timer; TYPE_2__ cfg; TYPE_1__ default_dst; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EADDRINUSE ; 
 scalar_t__ FDB_AGE_INTERVAL ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct vxlan_dev* netdev_priv (struct net_device*) ; 
 scalar_t__ vxlan_addr_multicast (int /*<<< orphan*/ *) ; 
 int vxlan_igmp_join (struct vxlan_dev*) ; 
 int vxlan_sock_add (struct vxlan_dev*) ; 
 int /*<<< orphan*/  vxlan_sock_release (struct vxlan_dev*) ; 

__attribute__((used)) static int vxlan_open(struct net_device *dev)
{
	struct vxlan_dev *vxlan = netdev_priv(dev);
	int ret;

	ret = vxlan_sock_add(vxlan);
	if (ret < 0)
		return ret;

	if (vxlan_addr_multicast(&vxlan->default_dst.remote_ip)) {
		ret = vxlan_igmp_join(vxlan);
		if (ret == -EADDRINUSE)
			ret = 0;
		if (ret) {
			vxlan_sock_release(vxlan);
			return ret;
		}
	}

	if (vxlan->cfg.age_interval)
		mod_timer(&vxlan->age_timer, jiffies + FDB_AGE_INTERVAL);

	return ret;
}