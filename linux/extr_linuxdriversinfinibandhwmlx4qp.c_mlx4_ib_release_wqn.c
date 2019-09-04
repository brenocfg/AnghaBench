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
struct mlx4_wqn_range {int dirty; int /*<<< orphan*/  list; int /*<<< orphan*/  size; int /*<<< orphan*/  base_wqn; int /*<<< orphan*/  refcount; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct mlx4_ib_ucontext {int /*<<< orphan*/  wqn_ranges_mutex; TYPE_1__ ibucontext; } ;
struct mlx4_ib_qp {struct mlx4_wqn_range* wqn_range; } ;
struct mlx4_ib_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlx4_wqn_range*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_qp_release_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mlx4_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx4_ib_release_wqn(struct mlx4_ib_ucontext *context,
				struct mlx4_ib_qp *qp, bool dirty_release)
{
	struct mlx4_ib_dev *dev = to_mdev(context->ibucontext.device);
	struct mlx4_wqn_range *range;

	mutex_lock(&context->wqn_ranges_mutex);

	range = qp->wqn_range;

	range->refcount--;
	if (!range->refcount) {
		mlx4_qp_release_range(dev->dev, range->base_wqn,
				      range->size);
		list_del(&range->list);
		kfree(range);
	} else if (dirty_release) {
	/*
	 * A range which one of its WQNs is destroyed, won't be able to be
	 * reused for further WQN allocations.
	 * The next created WQ will allocate a new range.
	 */
		range->dirty = 1;
	}

	mutex_unlock(&context->wqn_ranges_mutex);
}