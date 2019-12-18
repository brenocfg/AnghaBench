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
typedef  int u16 ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct ib_gid_attr {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_lower_dev_vlan ; 
 scalar_t__ is_vlan_dev (struct net_device*) ; 
 int /*<<< orphan*/  netdev_walk_all_lower_dev_rcu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct net_device* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int vlan_dev_vlan_id (struct net_device*) ; 

int rdma_read_gid_l2_fields(const struct ib_gid_attr *attr,
			    u16 *vlan_id, u8 *smac)
{
	struct net_device *ndev;

	rcu_read_lock();
	ndev = rcu_dereference(attr->ndev);
	if (!ndev) {
		rcu_read_unlock();
		return -ENODEV;
	}
	if (smac)
		ether_addr_copy(smac, ndev->dev_addr);
	if (vlan_id) {
		*vlan_id = 0xffff;
		if (is_vlan_dev(ndev)) {
			*vlan_id = vlan_dev_vlan_id(ndev);
		} else {
			/* If the netdev is upper device and if it's lower
			 * device is vlan device, consider vlan id of the
			 * the lower vlan device for this gid entry.
			 */
			netdev_walk_all_lower_dev_rcu(attr->ndev,
					get_lower_dev_vlan, vlan_id);
		}
	}
	rcu_read_unlock();
	return 0;
}