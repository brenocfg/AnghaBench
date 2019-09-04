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
struct mlx5_core_dev {int dummy; } ;
typedef  int /*<<< orphan*/  out ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_CMD_OP_MODIFY_RQ ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_DW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int mlx5_cmd_exec (struct mlx5_core_dev*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  modify_rq_in ; 
 int /*<<< orphan*/  modify_rq_out ; 
 int /*<<< orphan*/  opcode ; 

int mlx5_core_modify_rq(struct mlx5_core_dev *dev, u32 rqn, u32 *in, int inlen)
{
	u32 out[MLX5_ST_SZ_DW(modify_rq_out)];

	MLX5_SET(modify_rq_in, in, rqn, rqn);
	MLX5_SET(modify_rq_in, in, opcode, MLX5_CMD_OP_MODIFY_RQ);

	memset(out, 0, sizeof(out));
	return mlx5_cmd_exec(dev, in, inlen, out, sizeof(out));
}