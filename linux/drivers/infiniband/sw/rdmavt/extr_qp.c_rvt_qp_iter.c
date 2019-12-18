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
struct rvt_qp_iter {int specials; void (* cb ) (struct rvt_qp*,int /*<<< orphan*/ ) ;struct rvt_qp* qp; int /*<<< orphan*/  v; struct rvt_dev_info* rdi; } ;
struct TYPE_2__ {int phys_port_cnt; } ;
struct rvt_dev_info {TYPE_1__ ibdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  rvt_get_qp (struct rvt_qp*) ; 
 int /*<<< orphan*/  rvt_put_qp (struct rvt_qp*) ; 
 int rvt_qp_iter_next (struct rvt_qp_iter*) ; 
 void stub1 (struct rvt_qp*,int /*<<< orphan*/ ) ; 

void rvt_qp_iter(struct rvt_dev_info *rdi,
		 u64 v,
		 void (*cb)(struct rvt_qp *qp, u64 v))
{
	int ret;
	struct rvt_qp_iter i = {
		.rdi = rdi,
		.specials = rdi->ibdev.phys_port_cnt * 2,
		.v = v,
		.cb = cb
	};

	rcu_read_lock();
	do {
		ret = rvt_qp_iter_next(&i);
		if (!ret) {
			rvt_get_qp(i.qp);
			rcu_read_unlock();
			i.cb(i.qp, i.v);
			rcu_read_lock();
			rvt_put_qp(i.qp);
		}
	} while (!ret);
	rcu_read_unlock();
}