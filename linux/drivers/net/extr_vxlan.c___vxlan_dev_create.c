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
struct vxlan_rdst {struct net_device* remote_dev; int /*<<< orphan*/  remote_vni; scalar_t__ remote_ifindex; int /*<<< orphan*/  remote_ip; } ;
struct vxlan_net {int /*<<< orphan*/  vxlan_list; } ;
struct vxlan_fdb {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dst_port; } ;
struct vxlan_dev {int /*<<< orphan*/  next; TYPE_1__ cfg; struct vxlan_rdst default_dst; } ;
struct vxlan_config {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int /*<<< orphan*/ * ethtool_ops; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NTF_SELF ; 
 int NUD_PERMANENT ; 
 int NUD_REACHABLE ; 
 int /*<<< orphan*/  RTM_NEWNEIGH ; 
 struct net_device* __dev_get_by_index (struct net*,scalar_t__) ; 
 int /*<<< orphan*/  __vxlan_fdb_free (struct vxlan_fdb*) ; 
 int /*<<< orphan*/  all_zeros_mac ; 
 int /*<<< orphan*/  first_remote_rtnl (struct vxlan_fdb*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct vxlan_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct vxlan_dev* netdev_priv (struct net_device*) ; 
 int netdev_upper_dev_link (struct net_device*,struct net_device*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  netdev_upper_dev_unlink (struct net_device*,struct net_device*) ; 
 int register_netdevice (struct net_device*) ; 
 int rtnl_configure_link (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdevice (struct net_device*) ; 
 int /*<<< orphan*/  vxlan_addr_any (int /*<<< orphan*/ *) ; 
 int vxlan_dev_configure (struct net*,struct net_device*,struct vxlan_config*,int,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  vxlan_ethtool_ops ; 
 int vxlan_fdb_create (struct vxlan_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct vxlan_fdb**) ; 
 int /*<<< orphan*/  vxlan_fdb_destroy (struct vxlan_dev*,struct vxlan_fdb*,int,int) ; 
 int /*<<< orphan*/  vxlan_fdb_insert (struct vxlan_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vxlan_fdb*) ; 
 int vxlan_fdb_notify (struct vxlan_dev*,struct vxlan_fdb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  vxlan_net_id ; 

__attribute__((used)) static int __vxlan_dev_create(struct net *net, struct net_device *dev,
			      struct vxlan_config *conf,
			      struct netlink_ext_ack *extack)
{
	struct vxlan_net *vn = net_generic(net, vxlan_net_id);
	struct vxlan_dev *vxlan = netdev_priv(dev);
	struct net_device *remote_dev = NULL;
	struct vxlan_fdb *f = NULL;
	bool unregister = false;
	struct vxlan_rdst *dst;
	int err;

	dst = &vxlan->default_dst;
	err = vxlan_dev_configure(net, dev, conf, false, extack);
	if (err)
		return err;

	dev->ethtool_ops = &vxlan_ethtool_ops;

	/* create an fdb entry for a valid default destination */
	if (!vxlan_addr_any(&dst->remote_ip)) {
		err = vxlan_fdb_create(vxlan, all_zeros_mac,
				       &dst->remote_ip,
				       NUD_REACHABLE | NUD_PERMANENT,
				       vxlan->cfg.dst_port,
				       dst->remote_vni,
				       dst->remote_vni,
				       dst->remote_ifindex,
				       NTF_SELF, &f);
		if (err)
			return err;
	}

	err = register_netdevice(dev);
	if (err)
		goto errout;
	unregister = true;

	if (dst->remote_ifindex) {
		remote_dev = __dev_get_by_index(net, dst->remote_ifindex);
		if (!remote_dev)
			goto errout;

		err = netdev_upper_dev_link(remote_dev, dev, extack);
		if (err)
			goto errout;
	}

	err = rtnl_configure_link(dev, NULL);
	if (err)
		goto unlink;

	if (f) {
		vxlan_fdb_insert(vxlan, all_zeros_mac, dst->remote_vni, f);

		/* notify default fdb entry */
		err = vxlan_fdb_notify(vxlan, f, first_remote_rtnl(f),
				       RTM_NEWNEIGH, true, extack);
		if (err) {
			vxlan_fdb_destroy(vxlan, f, false, false);
			if (remote_dev)
				netdev_upper_dev_unlink(remote_dev, dev);
			goto unregister;
		}
	}

	list_add(&vxlan->next, &vn->vxlan_list);
	if (remote_dev)
		dst->remote_dev = remote_dev;
	return 0;
unlink:
	if (remote_dev)
		netdev_upper_dev_unlink(remote_dev, dev);
errout:
	/* unregister_netdevice() destroys the default FDB entry with deletion
	 * notification. But the addition notification was not sent yet, so
	 * destroy the entry by hand here.
	 */
	if (f)
		__vxlan_fdb_free(f);
unregister:
	if (unregister)
		unregister_netdevice(dev);
	return err;
}