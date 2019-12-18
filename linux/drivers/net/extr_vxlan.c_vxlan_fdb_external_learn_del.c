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
typedef  size_t u32 ;
struct vxlan_fdb {int flags; } ;
struct vxlan_dev {int /*<<< orphan*/ * hash_lock; } ;
struct switchdev_notifier_vxlan_fdb_info {int /*<<< orphan*/  remote_ifindex; int /*<<< orphan*/  remote_vni; int /*<<< orphan*/  vni; int /*<<< orphan*/  remote_port; int /*<<< orphan*/  remote_ip; int /*<<< orphan*/  eth_addr; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int NTF_EXT_LEARNED ; 
 int __vxlan_fdb_delete (struct vxlan_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 size_t fdb_head_index (struct vxlan_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vxlan_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct vxlan_fdb* vxlan_find_mac (struct vxlan_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vxlan_fdb_external_learn_del(struct net_device *dev,
			     struct switchdev_notifier_vxlan_fdb_info *fdb_info)
{
	struct vxlan_dev *vxlan = netdev_priv(dev);
	struct vxlan_fdb *f;
	u32 hash_index;
	int err = 0;

	hash_index = fdb_head_index(vxlan, fdb_info->eth_addr, fdb_info->vni);
	spin_lock_bh(&vxlan->hash_lock[hash_index]);

	f = vxlan_find_mac(vxlan, fdb_info->eth_addr, fdb_info->vni);
	if (!f)
		err = -ENOENT;
	else if (f->flags & NTF_EXT_LEARNED)
		err = __vxlan_fdb_delete(vxlan, fdb_info->eth_addr,
					 fdb_info->remote_ip,
					 fdb_info->remote_port,
					 fdb_info->vni,
					 fdb_info->remote_vni,
					 fdb_info->remote_ifindex,
					 false);

	spin_unlock_bh(&vxlan->hash_lock[hash_index]);

	return err;
}