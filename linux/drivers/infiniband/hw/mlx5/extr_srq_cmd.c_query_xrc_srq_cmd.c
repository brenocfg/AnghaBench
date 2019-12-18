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
typedef  int /*<<< orphan*/  xrcsrq_in ;
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_srq_attr {int /*<<< orphan*/  flags; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct mlx5_core_srq {int /*<<< orphan*/  srqn; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_CMD_OP_QUERY_XRC_SRQ ; 
 scalar_t__ MLX5_GET (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SRQ_FLAG_ERR ; 
 int /*<<< orphan*/  MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_DW (int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_XRC_SRQC_STATE_GOOD ; 
 int /*<<< orphan*/  get_srqc (void*,struct mlx5_srq_attr*) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kvzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int mlx5_cmd_exec (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opcode ; 
 int /*<<< orphan*/  query_xrc_srq_in ; 
 int /*<<< orphan*/  query_xrc_srq_out ; 
 int /*<<< orphan*/  state ; 
 int /*<<< orphan*/  xrc_srq_context_entry ; 
 int /*<<< orphan*/  xrc_srqn ; 

__attribute__((used)) static int query_xrc_srq_cmd(struct mlx5_ib_dev *dev,
			     struct mlx5_core_srq *srq,
			     struct mlx5_srq_attr *out)
{
	u32 xrcsrq_in[MLX5_ST_SZ_DW(query_xrc_srq_in)];
	u32 *xrcsrq_out;
	void *xrc_srqc;
	int err;

	xrcsrq_out = kvzalloc(MLX5_ST_SZ_BYTES(query_xrc_srq_out), GFP_KERNEL);
	if (!xrcsrq_out)
		return -ENOMEM;
	memset(xrcsrq_in, 0, sizeof(xrcsrq_in));

	MLX5_SET(query_xrc_srq_in, xrcsrq_in, opcode,
		 MLX5_CMD_OP_QUERY_XRC_SRQ);
	MLX5_SET(query_xrc_srq_in, xrcsrq_in, xrc_srqn, srq->srqn);

	err = mlx5_cmd_exec(dev->mdev, xrcsrq_in, sizeof(xrcsrq_in),
			    xrcsrq_out, MLX5_ST_SZ_BYTES(query_xrc_srq_out));
	if (err)
		goto out;

	xrc_srqc = MLX5_ADDR_OF(query_xrc_srq_out, xrcsrq_out,
				xrc_srq_context_entry);
	get_srqc(xrc_srqc, out);
	if (MLX5_GET(xrc_srqc, xrc_srqc, state) != MLX5_XRC_SRQC_STATE_GOOD)
		out->flags |= MLX5_SRQ_FLAG_ERR;

out:
	kvfree(xrcsrq_out);
	return err;
}