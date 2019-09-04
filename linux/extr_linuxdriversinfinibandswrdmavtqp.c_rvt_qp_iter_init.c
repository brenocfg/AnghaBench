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
struct rvt_qp_iter {int specials; void (* cb ) (struct rvt_qp*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  v; struct rvt_dev_info* rdi; } ;
struct TYPE_2__ {int phys_port_cnt; } ;
struct rvt_dev_info {TYPE_1__ ibdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct rvt_qp_iter* kzalloc (int,int /*<<< orphan*/ ) ; 

struct rvt_qp_iter *rvt_qp_iter_init(struct rvt_dev_info *rdi,
				     u64 v,
				     void (*cb)(struct rvt_qp *qp, u64 v))
{
	struct rvt_qp_iter *i;

	i = kzalloc(sizeof(*i), GFP_KERNEL);
	if (!i)
		return NULL;

	i->rdi = rdi;
	/* number of special QPs (SMI/GSI) for device */
	i->specials = rdi->ibdev.phys_port_cnt * 2;
	i->v = v;
	i->cb = cb;

	return i;
}