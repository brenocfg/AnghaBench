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
typedef  int /*<<< orphan*/  u64 ;
struct usnic_fwd_flow {int /*<<< orphan*/  flow_id; int /*<<< orphan*/  vnic_idx; TYPE_1__* ufdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_DEL_FILTER ; 
 int ERR_EINVAL ; 
 int /*<<< orphan*/  kfree (struct usnic_fwd_flow*) ; 
 int /*<<< orphan*/  usnic_dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  usnic_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int usnic_fwd_devcmd (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int usnic_fwd_dealloc_flow(struct usnic_fwd_flow *flow)
{
	int status;
	u64 a0, a1;

	a0 = flow->flow_id;

	status = usnic_fwd_devcmd(flow->ufdev, flow->vnic_idx,
					CMD_DEL_FILTER, &a0, &a1);
	if (status) {
		if (status == ERR_EINVAL) {
			usnic_dbg("Filter %u already deleted for VF Idx %u pf: %s status: %d",
					flow->flow_id, flow->vnic_idx,
					flow->ufdev->name, status);
		} else {
			usnic_err("PF %s VF Idx %u Filter: %u FILTER DELETE failed with status %d",
					flow->ufdev->name, flow->vnic_idx,
					flow->flow_id, status);
		}
		status = 0;
		/*
		 * Log the error and fake success to the caller because if
		 * a flow fails to be deleted in the firmware, it is an
		 * unrecoverable error.
		 */
	} else {
		usnic_dbg("PF %s VF Idx %u Filter: %u FILTER DELETED",
				flow->ufdev->name, flow->vnic_idx,
				flow->flow_id);
	}

	kfree(flow);
	return status;
}