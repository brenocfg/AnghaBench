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
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct mlx5_ib_cq {int /*<<< orphan*/  mcq; } ;
struct ib_udata {int dummy; } ;
struct ib_cq {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_cq_kernel (struct mlx5_ib_dev*,struct mlx5_ib_cq*) ; 
 int /*<<< orphan*/  destroy_cq_user (struct mlx5_ib_cq*,struct ib_udata*) ; 
 int /*<<< orphan*/  mlx5_core_destroy_cq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mlx5_ib_cq* to_mcq (struct ib_cq*) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 

void mlx5_ib_destroy_cq(struct ib_cq *cq, struct ib_udata *udata)
{
	struct mlx5_ib_dev *dev = to_mdev(cq->device);
	struct mlx5_ib_cq *mcq = to_mcq(cq);

	mlx5_core_destroy_cq(dev->mdev, &mcq->mcq);
	if (udata)
		destroy_cq_user(mcq, udata);
	else
		destroy_cq_kernel(dev, mcq);
}