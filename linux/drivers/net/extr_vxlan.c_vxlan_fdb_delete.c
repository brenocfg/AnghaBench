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
typedef  union vxlan_addr {int dummy; } vxlan_addr ;
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct vxlan_dev {int /*<<< orphan*/ * hash_lock; } ;
struct nlattr {int dummy; } ;
struct net_device {int dummy; } ;
struct ndmsg {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int __vxlan_fdb_delete (struct vxlan_dev*,unsigned char const*,union vxlan_addr,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int) ; 
 size_t fdb_head_index (struct vxlan_dev*,unsigned char const*,int /*<<< orphan*/ ) ; 
 struct vxlan_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int vxlan_fdb_parse (struct nlattr**,struct vxlan_dev*,union vxlan_addr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static int vxlan_fdb_delete(struct ndmsg *ndm, struct nlattr *tb[],
			    struct net_device *dev,
			    const unsigned char *addr, u16 vid)
{
	struct vxlan_dev *vxlan = netdev_priv(dev);
	union vxlan_addr ip;
	__be32 src_vni, vni;
	__be16 port;
	u32 ifindex;
	u32 hash_index;
	int err;

	err = vxlan_fdb_parse(tb, vxlan, &ip, &port, &src_vni, &vni, &ifindex);
	if (err)
		return err;

	hash_index = fdb_head_index(vxlan, addr, src_vni);
	spin_lock_bh(&vxlan->hash_lock[hash_index]);
	err = __vxlan_fdb_delete(vxlan, addr, ip, port, src_vni, vni, ifindex,
				 true);
	spin_unlock_bh(&vxlan->hash_lock[hash_index]);

	return err;
}