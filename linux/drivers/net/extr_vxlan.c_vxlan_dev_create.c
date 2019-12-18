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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  tb ;
struct vxlan_config {int dummy; } ;
struct nlattr {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct net_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  IFLA_MAX ; 
 scalar_t__ IS_ERR (struct net_device*) ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int __vxlan_dev_create (struct net*,struct net_device*,struct vxlan_config*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  list_kill ; 
 int /*<<< orphan*/  memset (struct nlattr***,int /*<<< orphan*/ ,int) ; 
 int rtnl_configure_link (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* rtnl_create_link (struct net*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct nlattr**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdevice_many (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vxlan_dellink (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vxlan_link_ops ; 

struct net_device *vxlan_dev_create(struct net *net, const char *name,
				    u8 name_assign_type,
				    struct vxlan_config *conf)
{
	struct nlattr *tb[IFLA_MAX + 1];
	struct net_device *dev;
	int err;

	memset(&tb, 0, sizeof(tb));

	dev = rtnl_create_link(net, name, name_assign_type,
			       &vxlan_link_ops, tb, NULL);
	if (IS_ERR(dev))
		return dev;

	err = __vxlan_dev_create(net, dev, conf, NULL);
	if (err < 0) {
		free_netdev(dev);
		return ERR_PTR(err);
	}

	err = rtnl_configure_link(dev, NULL);
	if (err < 0) {
		LIST_HEAD(list_kill);

		vxlan_dellink(dev, &list_kill);
		unregister_netdevice_many(&list_kill);
		return ERR_PTR(err);
	}

	return dev;
}