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
struct mlx5_core_qp {void* uid; void* qpn; } ;
struct mlx5_core_dev {int dummy; } ;
struct mlx5_core_dct {int /*<<< orphan*/  drained; struct mlx5_core_qp mqp; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_CMD_OP_CREATE_DCT ; 
 void* MLX5_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_RES_DCT ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mlx5_core_destroy_dct (struct mlx5_core_dev*,struct mlx5_core_dct*,int) ; 
 int /*<<< orphan*/  create_dct_in ; 
 int /*<<< orphan*/  create_dct_out ; 
 int create_resource_common (struct mlx5_core_dev*,struct mlx5_core_qp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dctn ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int mlx5_cmd_exec (struct mlx5_core_dev*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int) ; 
 int /*<<< orphan*/  opcode ; 
 int /*<<< orphan*/  uid ; 

int mlx5_core_create_dct(struct mlx5_core_dev *dev,
			 struct mlx5_core_dct *dct,
			 u32 *in, int inlen,
			 u32 *out, int outlen)
{
	struct mlx5_core_qp *qp = &dct->mqp;
	int err;

	init_completion(&dct->drained);
	MLX5_SET(create_dct_in, in, opcode, MLX5_CMD_OP_CREATE_DCT);

	err = mlx5_cmd_exec(dev, in, inlen, out, outlen);
	if (err) {
		mlx5_core_warn(dev, "create DCT failed, ret %d\n", err);
		return err;
	}

	qp->qpn = MLX5_GET(create_dct_out, out, dctn);
	qp->uid = MLX5_GET(create_dct_in, in, uid);
	err = create_resource_common(dev, qp, MLX5_RES_DCT);
	if (err)
		goto err_cmd;

	return 0;
err_cmd:
	_mlx5_core_destroy_dct(dev, dct, false);
	return err;
}