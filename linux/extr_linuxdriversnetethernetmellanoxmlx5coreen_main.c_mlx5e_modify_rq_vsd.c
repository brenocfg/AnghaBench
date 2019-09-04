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
struct mlx5e_rq {int /*<<< orphan*/  rqn; struct mlx5e_channel* channel; } ;
struct mlx5e_channel {struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* MLX5_ADDR_OF (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_MODIFY_RQ_IN_MODIFY_BITMASK_VSD ; 
 int MLX5_RQC_STATE_RDY ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,int,int) ; 
 int /*<<< orphan*/  MLX5_SET64 (void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_BYTES (void*) ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 void* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_core_modify_rq (struct mlx5_core_dev*,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  modify_bitmask ; 
 void* modify_rq_in ; 
 int rq_state ; 
 int state ; 

__attribute__((used)) static int mlx5e_modify_rq_vsd(struct mlx5e_rq *rq, bool vsd)
{
	struct mlx5e_channel *c = rq->channel;
	struct mlx5_core_dev *mdev = c->mdev;
	void *in;
	void *rqc;
	int inlen;
	int err;

	inlen = MLX5_ST_SZ_BYTES(modify_rq_in);
	in = kvzalloc(inlen, GFP_KERNEL);
	if (!in)
		return -ENOMEM;

	rqc = MLX5_ADDR_OF(modify_rq_in, in, ctx);

	MLX5_SET(modify_rq_in, in, rq_state, MLX5_RQC_STATE_RDY);
	MLX5_SET64(modify_rq_in, in, modify_bitmask,
		   MLX5_MODIFY_RQ_IN_MODIFY_BITMASK_VSD);
	MLX5_SET(rqc, rqc, vsd, vsd);
	MLX5_SET(rqc, rqc, state, MLX5_RQC_STATE_RDY);

	err = mlx5_core_modify_rq(mdev, rq->rqn, in, inlen);

	kvfree(in);

	return err;
}