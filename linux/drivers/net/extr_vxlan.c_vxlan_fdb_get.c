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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct vxlan_fdb {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  remote_vni; } ;
struct vxlan_dev {TYPE_1__ default_dst; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOENT ; 
 size_t NDA_VNI ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  RTM_NEWNEIGH ; 
 struct vxlan_fdb* __vxlan_find_mac (struct vxlan_dev*,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  first_remote_rcu (struct vxlan_fdb*) ; 
 struct vxlan_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int vxlan_fdb_info (struct sk_buff*,struct vxlan_dev*,struct vxlan_fdb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vxlan_fdb_get(struct sk_buff *skb,
			 struct nlattr *tb[],
			 struct net_device *dev,
			 const unsigned char *addr,
			 u16 vid, u32 portid, u32 seq,
			 struct netlink_ext_ack *extack)
{
	struct vxlan_dev *vxlan = netdev_priv(dev);
	struct vxlan_fdb *f;
	__be32 vni;
	int err;

	if (tb[NDA_VNI])
		vni = cpu_to_be32(nla_get_u32(tb[NDA_VNI]));
	else
		vni = vxlan->default_dst.remote_vni;

	rcu_read_lock();

	f = __vxlan_find_mac(vxlan, addr, vni);
	if (!f) {
		NL_SET_ERR_MSG(extack, "Fdb entry not found");
		err = -ENOENT;
		goto errout;
	}

	err = vxlan_fdb_info(skb, vxlan, f, portid, seq,
			     RTM_NEWNEIGH, 0, first_remote_rcu(f));
errout:
	rcu_read_unlock();
	return err;
}