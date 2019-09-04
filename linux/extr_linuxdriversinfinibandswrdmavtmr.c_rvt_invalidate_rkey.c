#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {scalar_t__ pd; int /*<<< orphan*/  device; } ;
struct rvt_qp {TYPE_2__ ibqp; } ;
struct rvt_mregion {int lkey; scalar_t__ pd; int /*<<< orphan*/  lkey_invalid; } ;
struct rvt_lkey_table {int /*<<< orphan*/ * table; } ;
struct TYPE_3__ {int lkey_table_size; } ;
struct rvt_dev_info {TYPE_1__ dparms; struct rvt_lkey_table lkey_table; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct rvt_dev_info* ib_to_rvt (int /*<<< orphan*/ ) ; 
 struct rvt_mregion* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ unlikely (int) ; 

int rvt_invalidate_rkey(struct rvt_qp *qp, u32 rkey)
{
	struct rvt_dev_info *dev = ib_to_rvt(qp->ibqp.device);
	struct rvt_lkey_table *rkt = &dev->lkey_table;
	struct rvt_mregion *mr;

	if (rkey == 0)
		return -EINVAL;

	rcu_read_lock();
	mr = rcu_dereference(
		rkt->table[(rkey >> (32 - dev->dparms.lkey_table_size))]);
	if (unlikely(!mr || mr->lkey != rkey || qp->ibqp.pd != mr->pd))
		goto bail;

	atomic_set(&mr->lkey_invalid, 1);
	rcu_read_unlock();
	return 0;

bail:
	rcu_read_unlock();
	return -EINVAL;
}