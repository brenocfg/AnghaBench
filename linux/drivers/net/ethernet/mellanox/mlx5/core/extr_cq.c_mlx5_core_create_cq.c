#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_eq_comp {int /*<<< orphan*/  core; int /*<<< orphan*/  tasklet_ctx; } ;
struct TYPE_5__ {int /*<<< orphan*/  uar; } ;
struct mlx5_core_dev {TYPE_2__ priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  list; int /*<<< orphan*/ * priv; } ;
struct mlx5_core_cq {void* uid; void* cqn; int /*<<< orphan*/  uar; int /*<<< orphan*/  pid; TYPE_1__ tasklet_ctx; scalar_t__ comp; int /*<<< orphan*/  free; int /*<<< orphan*/  refcount; struct mlx5_eq_comp* eq; scalar_t__ arm_sn; scalar_t__ cons_index; } ;
typedef  int /*<<< orphan*/  dout ;
typedef  int /*<<< orphan*/  din ;
struct TYPE_6__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct mlx5_eq_comp*) ; 
 int /*<<< orphan*/ * MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* MLX5_CMD_OP_CREATE_CQ ; 
 void* MLX5_CMD_OP_DESTROY_CQ ; 
 void* MLX5_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int MLX5_ST_SZ_DW (int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct mlx5_eq_comp*) ; 
 int /*<<< orphan*/  c_eqn ; 
 int /*<<< orphan*/  cq_context ; 
 int /*<<< orphan*/  cqc ; 
 int /*<<< orphan*/  cqn ; 
 int /*<<< orphan*/  create_cq_in ; 
 int /*<<< orphan*/  create_cq_out ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  destroy_cq_in ; 
 int /*<<< orphan*/  destroy_cq_out ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mlx5_add_cq_to_tasklet ; 
 int mlx5_cmd_exec (struct mlx5_core_dev*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mlx5_core_dbg (struct mlx5_core_dev*,char*,void*) ; 
 int mlx5_debug_cq_add (struct mlx5_core_dev*,struct mlx5_core_cq*) ; 
 int mlx5_eq_add_cq (int /*<<< orphan*/ *,struct mlx5_core_cq*) ; 
 int /*<<< orphan*/  mlx5_eq_del_cq (int /*<<< orphan*/ *,struct mlx5_core_cq*) ; 
 struct mlx5_eq_comp* mlx5_eqn2comp_eq (struct mlx5_core_dev*,int) ; 
 int /*<<< orphan*/ * mlx5_get_async_eq (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  opcode ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uid ; 

int mlx5_core_create_cq(struct mlx5_core_dev *dev, struct mlx5_core_cq *cq,
			u32 *in, int inlen, u32 *out, int outlen)
{
	int eqn = MLX5_GET(cqc, MLX5_ADDR_OF(create_cq_in, in, cq_context), c_eqn);
	u32 dout[MLX5_ST_SZ_DW(destroy_cq_out)];
	u32 din[MLX5_ST_SZ_DW(destroy_cq_in)];
	struct mlx5_eq_comp *eq;
	int err;

	eq = mlx5_eqn2comp_eq(dev, eqn);
	if (IS_ERR(eq))
		return PTR_ERR(eq);

	memset(out, 0, outlen);
	MLX5_SET(create_cq_in, in, opcode, MLX5_CMD_OP_CREATE_CQ);
	err = mlx5_cmd_exec(dev, in, inlen, out, outlen);
	if (err)
		return err;

	cq->cqn = MLX5_GET(create_cq_out, out, cqn);
	cq->cons_index = 0;
	cq->arm_sn     = 0;
	cq->eq         = eq;
	cq->uid = MLX5_GET(create_cq_in, in, uid);
	refcount_set(&cq->refcount, 1);
	init_completion(&cq->free);
	if (!cq->comp)
		cq->comp = mlx5_add_cq_to_tasklet;
	/* assuming CQ will be deleted before the EQ */
	cq->tasklet_ctx.priv = &eq->tasklet_ctx;
	INIT_LIST_HEAD(&cq->tasklet_ctx.list);

	/* Add to comp EQ CQ tree to recv comp events */
	err = mlx5_eq_add_cq(&eq->core, cq);
	if (err)
		goto err_cmd;

	/* Add to async EQ CQ tree to recv async events */
	err = mlx5_eq_add_cq(mlx5_get_async_eq(dev), cq);
	if (err)
		goto err_cq_add;

	cq->pid = current->pid;
	err = mlx5_debug_cq_add(dev, cq);
	if (err)
		mlx5_core_dbg(dev, "failed adding CP 0x%x to debug file system\n",
			      cq->cqn);

	cq->uar = dev->priv.uar;

	return 0;

err_cq_add:
	mlx5_eq_del_cq(&eq->core, cq);
err_cmd:
	memset(din, 0, sizeof(din));
	memset(dout, 0, sizeof(dout));
	MLX5_SET(destroy_cq_in, din, opcode, MLX5_CMD_OP_DESTROY_CQ);
	MLX5_SET(destroy_cq_in, din, cqn, cq->cqn);
	MLX5_SET(destroy_cq_in, din, uid, cq->uid);
	mlx5_cmd_exec(dev, din, sizeof(din), dout, sizeof(dout));
	return err;
}