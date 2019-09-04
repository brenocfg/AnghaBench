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
struct usnic_ib_qp_grp {scalar_t__ state; int /*<<< orphan*/  res_chunk_list; TYPE_1__* vf; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ IB_QPS_RESET ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  free_qp_grp_res (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct usnic_ib_qp_grp*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qp_grp_and_vf_unbind (struct usnic_ib_qp_grp*) ; 
 int /*<<< orphan*/  release_and_remove_all_flows (struct usnic_ib_qp_grp*) ; 
 int /*<<< orphan*/  usnic_ib_sysfs_qpn_remove (struct usnic_ib_qp_grp*) ; 

void usnic_ib_qp_grp_destroy(struct usnic_ib_qp_grp *qp_grp)
{

	WARN_ON(qp_grp->state != IB_QPS_RESET);
	lockdep_assert_held(&qp_grp->vf->lock);

	release_and_remove_all_flows(qp_grp);
	usnic_ib_sysfs_qpn_remove(qp_grp);
	qp_grp_and_vf_unbind(qp_grp);
	free_qp_grp_res(qp_grp->res_chunk_list);
	kfree(qp_grp);
}