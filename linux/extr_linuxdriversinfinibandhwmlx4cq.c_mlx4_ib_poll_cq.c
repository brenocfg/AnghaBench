#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mlx4_ib_qp {int dummy; } ;
struct mlx4_ib_dev {TYPE_3__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct mlx4_ib_cq {int /*<<< orphan*/  lock; int /*<<< orphan*/  mcq; TYPE_1__ ibcq; } ;
struct ib_wc {int dummy; } ;
struct ib_cq {int dummy; } ;
struct TYPE_6__ {TYPE_2__* persist; } ;
struct TYPE_5__ {int state; } ;

/* Variables and functions */
 int MLX4_DEVICE_STATE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  mlx4_cq_set_ci (int /*<<< orphan*/ *) ; 
 scalar_t__ mlx4_ib_poll_one (struct mlx4_ib_cq*,struct mlx4_ib_qp**,struct ib_wc*) ; 
 int /*<<< orphan*/  mlx4_ib_poll_sw_comp (struct mlx4_ib_cq*,int,struct ib_wc*,int*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mlx4_ib_cq* to_mcq (struct ib_cq*) ; 
 struct mlx4_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 

int mlx4_ib_poll_cq(struct ib_cq *ibcq, int num_entries, struct ib_wc *wc)
{
	struct mlx4_ib_cq *cq = to_mcq(ibcq);
	struct mlx4_ib_qp *cur_qp = NULL;
	unsigned long flags;
	int npolled;
	struct mlx4_ib_dev *mdev = to_mdev(cq->ibcq.device);

	spin_lock_irqsave(&cq->lock, flags);
	if (mdev->dev->persist->state & MLX4_DEVICE_STATE_INTERNAL_ERROR) {
		mlx4_ib_poll_sw_comp(cq, num_entries, wc, &npolled);
		goto out;
	}

	for (npolled = 0; npolled < num_entries; ++npolled) {
		if (mlx4_ib_poll_one(cq, &cur_qp, wc + npolled))
			break;
	}

	mlx4_cq_set_ci(&cq->mcq);

out:
	spin_unlock_irqrestore(&cq->lock, flags);

	return npolled;
}