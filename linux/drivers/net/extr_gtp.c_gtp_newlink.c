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
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct gtp_net {int /*<<< orphan*/  gtp_dev_list; } ;
struct gtp_dev {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t IFLA_GTP_FD0 ; 
 size_t IFLA_GTP_FD1 ; 
 size_t IFLA_GTP_PDP_HASHSIZE ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  gtp_encap_disable (struct gtp_dev*) ; 
 int gtp_encap_enable (struct gtp_dev*,struct nlattr**) ; 
 int /*<<< orphan*/  gtp_hashtable_free (struct gtp_dev*) ; 
 int gtp_hashtable_new (struct gtp_dev*,int) ; 
 int /*<<< orphan*/  gtp_net_id ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct gtp_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,...) ; 
 struct gtp_dev* netdev_priv (struct net_device*) ; 
 int nla_get_u32 (struct nlattr*) ; 
 int register_netdevice (struct net_device*) ; 

__attribute__((used)) static int gtp_newlink(struct net *src_net, struct net_device *dev,
		       struct nlattr *tb[], struct nlattr *data[],
		       struct netlink_ext_ack *extack)
{
	struct gtp_dev *gtp;
	struct gtp_net *gn;
	int hashsize, err;

	if (!data[IFLA_GTP_FD0] && !data[IFLA_GTP_FD1])
		return -EINVAL;

	gtp = netdev_priv(dev);

	err = gtp_encap_enable(gtp, data);
	if (err < 0)
		return err;

	if (!data[IFLA_GTP_PDP_HASHSIZE])
		hashsize = 1024;
	else
		hashsize = nla_get_u32(data[IFLA_GTP_PDP_HASHSIZE]);

	err = gtp_hashtable_new(gtp, hashsize);
	if (err < 0)
		goto out_encap;

	err = register_netdevice(dev);
	if (err < 0) {
		netdev_dbg(dev, "failed to register new netdev %d\n", err);
		goto out_hashtable;
	}

	gn = net_generic(dev_net(dev), gtp_net_id);
	list_add_rcu(&gtp->list, &gn->gtp_dev_list);

	netdev_dbg(dev, "registered new GTP interface\n");

	return 0;

out_hashtable:
	gtp_hashtable_free(gtp);
out_encap:
	gtp_encap_disable(gtp);
	return err;
}