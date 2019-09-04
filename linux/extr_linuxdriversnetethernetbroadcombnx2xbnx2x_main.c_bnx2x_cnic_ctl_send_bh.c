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
struct bnx2x {int /*<<< orphan*/  cnic_data; int /*<<< orphan*/  cnic_ops; } ;

/* Variables and functions */
 struct cnic_ops* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int stub1 (int /*<<< orphan*/ ,struct cnic_ctl_info*) ; 

__attribute__((used)) static int bnx2x_cnic_ctl_send_bh(struct bnx2x *bp, struct cnic_ctl_info *ctl)
{
	struct cnic_ops *c_ops;
	int rc = 0;

	rcu_read_lock();
	c_ops = rcu_dereference(bp->cnic_ops);
	if (c_ops)
		rc = c_ops->cnic_ctl(bp->cnic_data, ctl);
	rcu_read_unlock();

	return rc;
}