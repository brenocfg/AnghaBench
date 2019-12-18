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
struct mlx5dr_cq {int /*<<< orphan*/  wq_ctrl; int /*<<< orphan*/  mcq; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlx5dr_cq*) ; 
 int /*<<< orphan*/  mlx5_core_destroy_cq (struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_wq_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dr_destroy_cq(struct mlx5_core_dev *mdev, struct mlx5dr_cq *cq)
{
	mlx5_core_destroy_cq(mdev, &cq->mcq);
	mlx5_wq_destroy(&cq->wq_ctrl);
	kfree(cq);
}