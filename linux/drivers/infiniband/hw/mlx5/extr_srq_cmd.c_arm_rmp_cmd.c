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
typedef  int u16 ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct mlx5_core_srq {int srqn; int uid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* MLX5_ADDR_OF (void*,void*,void*) ; 
 int MLX5_CMD_OP_MODIFY_RMP ; 
 int MLX5_RMPC_STATE_RDY ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,int,int) ; 
 int MLX5_ST_SZ_BYTES (void*) ; 
 void* ctx ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 void* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_cmd_exec (int /*<<< orphan*/ ,void*,int,void*,int) ; 
 void* modify_rmp_in ; 
 void* modify_rmp_out ; 
 int opcode ; 
 void* rmp_bitmask ; 
 int rmp_state ; 
 int rmpn ; 
 int state ; 
 int uid ; 

__attribute__((used)) static int arm_rmp_cmd(struct mlx5_ib_dev *dev, struct mlx5_core_srq *srq,
		       u16 lwm)
{
	void *out = NULL;
	void *in = NULL;
	void *rmpc;
	void *wq;
	void *bitmask;
	int outlen;
	int inlen;
	int err;

	inlen = MLX5_ST_SZ_BYTES(modify_rmp_in);
	outlen = MLX5_ST_SZ_BYTES(modify_rmp_out);

	in = kvzalloc(inlen, GFP_KERNEL);
	out = kvzalloc(outlen, GFP_KERNEL);
	if (!in || !out) {
		err = -ENOMEM;
		goto out;
	}

	rmpc =	  MLX5_ADDR_OF(modify_rmp_in,   in,   ctx);
	bitmask = MLX5_ADDR_OF(modify_rmp_in,   in,   bitmask);
	wq   =	  MLX5_ADDR_OF(rmpc,	        rmpc, wq);

	MLX5_SET(modify_rmp_in, in,	 rmp_state, MLX5_RMPC_STATE_RDY);
	MLX5_SET(modify_rmp_in, in,	 rmpn,      srq->srqn);
	MLX5_SET(modify_rmp_in, in, uid, srq->uid);
	MLX5_SET(wq,		wq,	 lwm,	    lwm);
	MLX5_SET(rmp_bitmask,	bitmask, lwm,	    1);
	MLX5_SET(rmpc, rmpc, state, MLX5_RMPC_STATE_RDY);
	MLX5_SET(modify_rmp_in, in, opcode, MLX5_CMD_OP_MODIFY_RMP);

	err = mlx5_cmd_exec(dev->mdev, in, inlen, out, outlen);

out:
	kvfree(in);
	kvfree(out);
	return err;
}