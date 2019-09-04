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
struct qlcnic_vf_info {scalar_t__ num_vlan; int /*<<< orphan*/  vlan_list_lock; } ;
struct qlcnic_sriov {scalar_t__ num_allowed_vlans; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qlcnic_sriov_validate_num_vlans(struct qlcnic_sriov *sriov,
					   struct qlcnic_vf_info *vf)
{
	int err = 0;

	spin_lock_bh(&vf->vlan_list_lock);

	if (vf->num_vlan >= sriov->num_allowed_vlans)
		err = -EINVAL;

	spin_unlock_bh(&vf->vlan_list_lock);
	return err;
}