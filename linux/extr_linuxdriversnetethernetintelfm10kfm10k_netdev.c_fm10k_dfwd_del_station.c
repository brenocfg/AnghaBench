#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct fm10k_l2_accel {int size; scalar_t__ dglort; scalar_t__ count; struct net_device** macvlan; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* configure_dglort_map ) (struct fm10k_hw*,struct fm10k_dglort_cfg*) ;int /*<<< orphan*/  (* update_xcast_mode ) (struct fm10k_hw*,scalar_t__,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {scalar_t__ default_vid; TYPE_2__ ops; } ;
struct fm10k_hw {TYPE_3__ mac; } ;
struct fm10k_intfc {int /*<<< orphan*/  glort; TYPE_1__* ring_feature; struct fm10k_hw hw; int /*<<< orphan*/  l2_accel; } ;
struct fm10k_dglort_cfg {int inner_rss; void* shared_l; int /*<<< orphan*/  glort; void* pc_l; void* rss_l; int /*<<< orphan*/  idx; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_XCAST_MODE_NONE ; 
 struct fm10k_l2_accel* READ_ONCE (int /*<<< orphan*/ ) ; 
 size_t RING_F_QOS ; 
 size_t RING_F_RSS ; 
 scalar_t__ VLAN_N_VID ; 
 void* fls (int) ; 
 int /*<<< orphan*/  fm10k_assign_l2_accel (struct fm10k_intfc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fm10k_dglort_pf_rss ; 
 scalar_t__ fm10k_find_next_vlan (struct fm10k_intfc*,scalar_t__) ; 
 scalar_t__ fm10k_host_mbx_ready (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_mbx_lock (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_mbx_unlock (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_queue_mac_request (struct fm10k_intfc*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  kfree_rcu (struct fm10k_l2_accel*,int /*<<< orphan*/ ) ; 
 struct fm10k_intfc* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  stub1 (struct fm10k_hw*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct fm10k_hw*,struct fm10k_dglort_cfg*) ; 

__attribute__((used)) static void fm10k_dfwd_del_station(struct net_device *dev, void *priv)
{
	struct fm10k_intfc *interface = netdev_priv(dev);
	struct fm10k_l2_accel *l2_accel = READ_ONCE(interface->l2_accel);
	struct fm10k_dglort_cfg dglort = { 0 };
	struct fm10k_hw *hw = &interface->hw;
	struct net_device *sdev = priv;
	u16 vid, glort;
	int i;

	if (!l2_accel)
		return;

	/* search table for matching interface */
	for (i = 0; i < l2_accel->size; i++) {
		if (l2_accel->macvlan[i] == sdev)
			break;
	}

	/* exit if macvlan not found */
	if (i == l2_accel->size)
		return;

	/* Remove any rules specific to this dglort */
	fm10k_mbx_lock(interface);

	glort = l2_accel->dglort + 1 + i;

	if (fm10k_host_mbx_ready(interface))
		hw->mac.ops.update_xcast_mode(hw, glort,
					      FM10K_XCAST_MODE_NONE);

	fm10k_queue_mac_request(interface, glort, sdev->dev_addr,
				hw->mac.default_vid, false);

	for (vid = fm10k_find_next_vlan(interface, 0);
	     vid < VLAN_N_VID;
	     vid = fm10k_find_next_vlan(interface, vid))
		fm10k_queue_mac_request(interface, glort, sdev->dev_addr,
					vid, false);

	fm10k_mbx_unlock(interface);

	/* record removal */
	l2_accel->macvlan[i] = NULL;
	l2_accel->count--;

	/* configure default DGLORT mapping for RSS/DCB */
	dglort.idx = fm10k_dglort_pf_rss;
	dglort.inner_rss = 1;
	dglort.rss_l = fls(interface->ring_feature[RING_F_RSS].mask);
	dglort.pc_l = fls(interface->ring_feature[RING_F_QOS].mask);
	dglort.glort = interface->glort;
	dglort.shared_l = fls(l2_accel->size);
	hw->mac.ops.configure_dglort_map(hw, &dglort);

	/* If table is empty remove it */
	if (l2_accel->count == 0) {
		fm10k_assign_l2_accel(interface, NULL);
		kfree_rcu(l2_accel, rcu);
	}
}