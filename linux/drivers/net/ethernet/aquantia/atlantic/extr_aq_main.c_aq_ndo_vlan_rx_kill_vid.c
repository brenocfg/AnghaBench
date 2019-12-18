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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct aq_nic_s {int /*<<< orphan*/  active_vlans; TYPE_1__* aq_hw_ops; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int /*<<< orphan*/  hw_filter_vlan_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  aq_del_fvlan_by_vlan (struct aq_nic_s*,int /*<<< orphan*/ ) ; 
 int aq_filters_vlans_update (struct aq_nic_s*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct aq_nic_s* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int aq_ndo_vlan_rx_kill_vid(struct net_device *ndev, __be16 proto,
				   u16 vid)
{
	struct aq_nic_s *aq_nic = netdev_priv(ndev);

	if (!aq_nic->aq_hw_ops->hw_filter_vlan_set)
		return -EOPNOTSUPP;

	clear_bit(vid, aq_nic->active_vlans);

	if (-ENOENT == aq_del_fvlan_by_vlan(aq_nic, vid))
		return aq_filters_vlans_update(aq_nic);

	return 0;
}