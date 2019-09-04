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
struct TYPE_2__ {scalar_t__ pvid; } ;
struct i40e_vsi {int /*<<< orphan*/  back; int /*<<< orphan*/  mac_filter_hash_lock; TYPE_1__ info; } ;

/* Variables and functions */
 int EINVAL ; 
 int i40e_add_vlan_all_mac (struct i40e_vsi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_service_event_schedule (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int i40e_vsi_add_vlan(struct i40e_vsi *vsi, u16 vid)
{
	int err;

	if (vsi->info.pvid)
		return -EINVAL;

	/* The network stack will attempt to add VID=0, with the intention to
	 * receive priority tagged packets with a VLAN of 0. Our HW receives
	 * these packets by default when configured to receive untagged
	 * packets, so we don't need to add a filter for this case.
	 * Additionally, HW interprets adding a VID=0 filter as meaning to
	 * receive *only* tagged traffic and stops receiving untagged traffic.
	 * Thus, we do not want to actually add a filter for VID=0
	 */
	if (!vid)
		return 0;

	/* Locked once because all functions invoked below iterates list*/
	spin_lock_bh(&vsi->mac_filter_hash_lock);
	err = i40e_add_vlan_all_mac(vsi, vid);
	spin_unlock_bh(&vsi->mac_filter_hash_lock);
	if (err)
		return err;

	/* schedule our worker thread which will take care of
	 * applying the new filter changes
	 */
	i40e_service_event_schedule(vsi->back);
	return 0;
}