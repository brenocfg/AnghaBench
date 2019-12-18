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
struct TYPE_2__ {scalar_t__ pvid; } ;
struct i40e_vsi {int /*<<< orphan*/  mac_filter_hash_lock; TYPE_1__ info; } ;

/* Variables and functions */
 int i40e_is_vsi_in_vlan (struct i40e_vsi*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool i40e_vsi_has_vlans(struct i40e_vsi *vsi)
{
	bool have_vlans;

	/* If we have a port VLAN, then the VSI cannot have any VLANs
	 * configured, as all MAC/VLAN filters will be assigned to the PVID.
	 */
	if (vsi->info.pvid)
		return false;

	/* Since we don't have a PVID, we know that if the device is in VLAN
	 * mode it must be because of a VLAN filter configured on this VSI.
	 */
	spin_lock_bh(&vsi->mac_filter_hash_lock);
	have_vlans = i40e_is_vsi_in_vlan(vsi);
	spin_unlock_bh(&vsi->mac_filter_hash_lock);

	return have_vlans;
}