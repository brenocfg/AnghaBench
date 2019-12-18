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
struct mlx5_core_qp {int /*<<< orphan*/  uid; int /*<<< orphan*/  qpn; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_resource_common (struct mlx5_core_dev*,struct mlx5_core_qp*) ; 
 int /*<<< orphan*/  destroy_sq_tracked (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mlx5_core_destroy_sq_tracked(struct mlx5_core_dev *dev,
				  struct mlx5_core_qp *sq)
{
	destroy_resource_common(dev, sq);
	destroy_sq_tracked(dev, sq->qpn, sq->uid);
}