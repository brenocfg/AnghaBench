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
typedef  int /*<<< orphan*/  u32 ;
struct list_head {int dummy; } ;
struct ib_qp {int /*<<< orphan*/  mr_lock; int /*<<< orphan*/  pd; } ;
struct ib_mr {int /*<<< orphan*/  qp_entry; } ;
typedef  enum ib_mr_type { ____Placeholder_ib_mr_type } ib_mr_type ;

/* Variables and functions */
 int IB_MR_TYPE_INTEGRITY ; 
 scalar_t__ IS_ERR (struct ib_mr*) ; 
 int PTR_ERR (struct ib_mr*) ; 
 struct ib_mr* ib_alloc_mr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct ib_mr* ib_alloc_mr_integrity (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_mr_pool_destroy (struct ib_qp*,struct list_head*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ib_mr_pool_init(struct ib_qp *qp, struct list_head *list, int nr,
		enum ib_mr_type type, u32 max_num_sg, u32 max_num_meta_sg)
{
	struct ib_mr *mr;
	unsigned long flags;
	int ret, i;

	for (i = 0; i < nr; i++) {
		if (type == IB_MR_TYPE_INTEGRITY)
			mr = ib_alloc_mr_integrity(qp->pd, max_num_sg,
						   max_num_meta_sg);
		else
			mr = ib_alloc_mr(qp->pd, type, max_num_sg);
		if (IS_ERR(mr)) {
			ret = PTR_ERR(mr);
			goto out;
		}

		spin_lock_irqsave(&qp->mr_lock, flags);
		list_add_tail(&mr->qp_entry, list);
		spin_unlock_irqrestore(&qp->mr_lock, flags);
	}

	return 0;
out:
	ib_mr_pool_destroy(qp, list);
	return ret;
}