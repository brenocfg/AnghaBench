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
struct cnic_ops {int (* cnic_ctl ) (int /*<<< orphan*/ ,struct cnic_ctl_info*) ;} ;
struct cnic_ctl_info {int dummy; } ;
struct bnx2x {int /*<<< orphan*/  cnic_mutex; int /*<<< orphan*/  cnic_data; int /*<<< orphan*/  cnic_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct cnic_ops* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,struct cnic_ctl_info*) ; 

__attribute__((used)) static int bnx2x_cnic_ctl_send(struct bnx2x *bp, struct cnic_ctl_info *ctl)
{
	struct cnic_ops *c_ops;
	int rc = 0;

	mutex_lock(&bp->cnic_mutex);
	c_ops = rcu_dereference_protected(bp->cnic_ops,
					  lockdep_is_held(&bp->cnic_mutex));
	if (c_ops)
		rc = c_ops->cnic_ctl(bp->cnic_data, ctl);
	mutex_unlock(&bp->cnic_mutex);

	return rc;
}