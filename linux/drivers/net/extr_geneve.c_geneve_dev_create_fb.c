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
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  tb ;
struct nlattr {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct ip_tunnel_info {int dummy; } ;

/* Variables and functions */
 struct net_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  GENEVE_DF_UNSET ; 
 int /*<<< orphan*/  IFLA_MAX ; 
 int /*<<< orphan*/  IP_MAX_MTU ; 
 scalar_t__ IS_ERR (struct net_device*) ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int geneve_change_mtu (struct net_device*,int /*<<< orphan*/ ) ; 
 int geneve_configure (struct net*,struct net_device*,int /*<<< orphan*/ *,struct ip_tunnel_info*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  geneve_dellink (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  geneve_link_ops ; 
 int /*<<< orphan*/  init_tnl_info (struct ip_tunnel_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_kill ; 
 int /*<<< orphan*/  memset (struct nlattr**,int /*<<< orphan*/ ,int) ; 
 int rtnl_configure_link (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* rtnl_create_link (struct net*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct nlattr**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdevice_many (int /*<<< orphan*/ *) ; 

struct net_device *geneve_dev_create_fb(struct net *net, const char *name,
					u8 name_assign_type, u16 dst_port)
{
	struct nlattr *tb[IFLA_MAX + 1];
	struct ip_tunnel_info info;
	struct net_device *dev;
	LIST_HEAD(list_kill);
	int err;

	memset(tb, 0, sizeof(tb));
	dev = rtnl_create_link(net, name, name_assign_type,
			       &geneve_link_ops, tb, NULL);
	if (IS_ERR(dev))
		return dev;

	init_tnl_info(&info, dst_port);
	err = geneve_configure(net, dev, NULL, &info,
			       true, true, false, GENEVE_DF_UNSET);
	if (err) {
		free_netdev(dev);
		return ERR_PTR(err);
	}

	/* openvswitch users expect packet sizes to be unrestricted,
	 * so set the largest MTU we can.
	 */
	err = geneve_change_mtu(dev, IP_MAX_MTU);
	if (err)
		goto err;

	err = rtnl_configure_link(dev, NULL);
	if (err < 0)
		goto err;

	return dev;
err:
	geneve_dellink(dev, &list_kill);
	unregister_netdevice_many(&list_kill);
	return ERR_PTR(err);
}