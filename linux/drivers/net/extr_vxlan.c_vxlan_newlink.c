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
struct vxlan_config {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int __vxlan_dev_create (struct net*,struct net_device*,struct vxlan_config*,struct netlink_ext_ack*) ; 
 int vxlan_nl2conf (struct nlattr**,struct nlattr**,struct net_device*,struct vxlan_config*,int,struct netlink_ext_ack*) ; 

__attribute__((used)) static int vxlan_newlink(struct net *src_net, struct net_device *dev,
			 struct nlattr *tb[], struct nlattr *data[],
			 struct netlink_ext_ack *extack)
{
	struct vxlan_config conf;
	int err;

	err = vxlan_nl2conf(tb, data, dev, &conf, false, extack);
	if (err)
		return err;

	return __vxlan_dev_create(src_net, dev, &conf, extack);
}