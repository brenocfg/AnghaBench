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
struct mlx5_err_cqe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_dump_err_cqe (int /*<<< orphan*/ ,struct mlx5_err_cqe*) ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*) ; 

__attribute__((used)) static void dump_cqe(struct mlx5_ib_dev *dev, struct mlx5_err_cqe *cqe)
{
	mlx5_ib_warn(dev, "dump error cqe\n");
	mlx5_dump_err_cqe(dev->mdev, cqe);
}