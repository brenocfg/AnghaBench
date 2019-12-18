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
struct qlcnic_vf_info {int /*<<< orphan*/  vlan_list_lock; scalar_t__ num_vlan; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

bool qlcnic_sriov_check_any_vlan(struct qlcnic_vf_info *vf)
{
	bool err = false;

	spin_lock_bh(&vf->vlan_list_lock);

	if (vf->num_vlan)
		err = true;

	spin_unlock_bh(&vf->vlan_list_lock);
	return err;
}