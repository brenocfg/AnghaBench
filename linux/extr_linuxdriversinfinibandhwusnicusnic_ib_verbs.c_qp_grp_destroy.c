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
struct usnic_ib_vf {int /*<<< orphan*/  lock; } ;
struct usnic_ib_qp_grp {scalar_t__ state; struct usnic_ib_vf* vf; } ;

/* Variables and functions */
 scalar_t__ IB_QPS_RESET ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usnic_ib_qp_grp_destroy (struct usnic_ib_qp_grp*) ; 

__attribute__((used)) static void qp_grp_destroy(struct usnic_ib_qp_grp *qp_grp)
{
	struct usnic_ib_vf *vf = qp_grp->vf;

	WARN_ON(qp_grp->state != IB_QPS_RESET);

	spin_lock(&vf->lock);
	usnic_ib_qp_grp_destroy(qp_grp);
	spin_unlock(&vf->lock);
}