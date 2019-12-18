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
typedef  void u32 ;
struct mlx5_srq_attr {int /*<<< orphan*/  flags; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct mlx5_core_srq {int /*<<< orphan*/  srqn; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* MLX5_ADDR_OF (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_CMD_OP_QUERY_RMP ; 
 scalar_t__ MLX5_GET (void*,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_RMPC_STATE_RDY ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SRQ_FLAG_ERR ; 
 int MLX5_ST_SZ_BYTES (void*) ; 
 int /*<<< orphan*/  get_wq (void*,struct mlx5_srq_attr*) ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 void* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_cmd_exec (int /*<<< orphan*/ ,void*,int,void*,int) ; 
 int /*<<< orphan*/  opcode ; 
 void* query_rmp_in ; 
 void* query_rmp_out ; 
 int /*<<< orphan*/  rmp_context ; 
 int /*<<< orphan*/  rmpn ; 
 int /*<<< orphan*/  state ; 
 int /*<<< orphan*/  wq ; 

__attribute__((used)) static int query_rmp_cmd(struct mlx5_ib_dev *dev, struct mlx5_core_srq *srq,
			 struct mlx5_srq_attr *out)
{
	u32 *rmp_out = NULL;
	u32 *rmp_in = NULL;
	void *rmpc;
	int outlen;
	int inlen;
	int err;

	outlen = MLX5_ST_SZ_BYTES(query_rmp_out);
	inlen = MLX5_ST_SZ_BYTES(query_rmp_in);

	rmp_out = kvzalloc(outlen, GFP_KERNEL);
	rmp_in = kvzalloc(inlen, GFP_KERNEL);
	if (!rmp_out || !rmp_in) {
		err = -ENOMEM;
		goto out;
	}

	MLX5_SET(query_rmp_in, rmp_in, opcode, MLX5_CMD_OP_QUERY_RMP);
	MLX5_SET(query_rmp_in, rmp_in, rmpn,   srq->srqn);
	err = mlx5_cmd_exec(dev->mdev, rmp_in, inlen, rmp_out, outlen);
	if (err)
		goto out;

	rmpc = MLX5_ADDR_OF(query_rmp_out, rmp_out, rmp_context);
	get_wq(MLX5_ADDR_OF(rmpc, rmpc, wq), out);
	if (MLX5_GET(rmpc, rmpc, state) != MLX5_RMPC_STATE_RDY)
		out->flags |= MLX5_SRQ_FLAG_ERR;

out:
	kvfree(rmp_out);
	kvfree(rmp_in);
	return err;
}