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
struct net_device {int dummy; } ;
struct hfi1_vnic_vport_info {int vesw_id; int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI1_VNIC_UP ; 
 int /*<<< orphan*/  hfi1_vnic_down (struct hfi1_vnic_vport_info*) ; 
 int /*<<< orphan*/  hfi1_vnic_up (struct hfi1_vnic_vport_info*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct hfi1_vnic_vport_info* opa_vnic_dev_priv (struct net_device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hfi1_vnic_set_vesw_id(struct net_device *netdev, int id)
{
	struct hfi1_vnic_vport_info *vinfo = opa_vnic_dev_priv(netdev);
	bool reopen = false;

	/*
	 * If vesw_id is being changed, and if the vnic port is up,
	 * reset the vnic port to ensure new vesw_id gets picked up
	 */
	if (id != vinfo->vesw_id) {
		mutex_lock(&vinfo->lock);
		if (test_bit(HFI1_VNIC_UP, &vinfo->flags)) {
			hfi1_vnic_down(vinfo);
			reopen = true;
		}

		vinfo->vesw_id = id;
		if (reopen)
			hfi1_vnic_up(vinfo);

		mutex_unlock(&vinfo->lock);
	}
}