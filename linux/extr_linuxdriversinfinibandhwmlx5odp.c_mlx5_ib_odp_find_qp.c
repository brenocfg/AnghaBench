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
struct mlx5_ib_qp {int dummy; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct mlx5_core_qp {int dummy; } ;

/* Variables and functions */
 struct mlx5_core_qp* __mlx5_qp_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_err (struct mlx5_ib_dev*,char*,int /*<<< orphan*/ ) ; 
 struct mlx5_ib_qp* to_mibqp (struct mlx5_core_qp*) ; 

__attribute__((used)) static struct mlx5_ib_qp *mlx5_ib_odp_find_qp(struct mlx5_ib_dev *dev,
					      u32 wq_num)
{
	struct mlx5_core_qp *mqp = __mlx5_qp_lookup(dev->mdev, wq_num);

	if (!mqp) {
		mlx5_ib_err(dev, "QPN 0x%6x not found\n", wq_num);
		return NULL;
	}

	return to_mibqp(mqp);
}