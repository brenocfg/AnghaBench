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
struct mlx5_core_qp {int /*<<< orphan*/  uid; int /*<<< orphan*/  qpn; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_RES_SQ ; 
 int create_resource_common (struct mlx5_core_dev*,struct mlx5_core_qp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_sq_in ; 
 int /*<<< orphan*/  destroy_sq_tracked (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx5_core_create_sq (struct mlx5_core_dev*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uid ; 

int mlx5_core_create_sq_tracked(struct mlx5_core_dev *dev, u32 *in, int inlen,
				struct mlx5_core_qp *sq)
{
	int err;
	u32 sqn;

	err = mlx5_core_create_sq(dev, in, inlen, &sqn);
	if (err)
		return err;

	sq->uid = MLX5_GET(create_sq_in, in, uid);
	sq->qpn = sqn;
	err = create_resource_common(dev, sq, MLX5_RES_SQ);
	if (err)
		goto err_destroy_sq;

	return 0;

err_destroy_sq:
	destroy_sq_tracked(dev, sq->qpn, sq->uid);

	return err;
}