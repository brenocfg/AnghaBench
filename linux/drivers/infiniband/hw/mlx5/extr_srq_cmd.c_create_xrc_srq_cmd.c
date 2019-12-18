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
struct mlx5_srq_attr {int /*<<< orphan*/  uid; int /*<<< orphan*/  pas; int /*<<< orphan*/  user_index; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct mlx5_core_srq {int /*<<< orphan*/  uid; int /*<<< orphan*/  srqn; } ;
typedef  int /*<<< orphan*/  create_out ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* MLX5_ADDR_OF (void*,void*,void*) ; 
 int /*<<< orphan*/  MLX5_CMD_OP_CREATE_XRC_SRQ ; 
 int /*<<< orphan*/  MLX5_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_BYTES (void*) ; 
 int MLX5_ST_SZ_DW (int /*<<< orphan*/ ) ; 
 void* create_xrc_srq_in ; 
 int /*<<< orphan*/  create_xrc_srq_out ; 
 int get_pas_size (struct mlx5_srq_attr*) ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 void* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int mlx5_cmd_exec (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  opcode ; 
 int /*<<< orphan*/  set_srqc (void*,struct mlx5_srq_attr*) ; 
 int /*<<< orphan*/  uid ; 
 int /*<<< orphan*/  user_index ; 
 void* xrc_srq_context_entry ; 
 int /*<<< orphan*/  xrc_srqn ; 

__attribute__((used)) static int create_xrc_srq_cmd(struct mlx5_ib_dev *dev,
			      struct mlx5_core_srq *srq,
			      struct mlx5_srq_attr *in)
{
	u32 create_out[MLX5_ST_SZ_DW(create_xrc_srq_out)];
	void *create_in;
	void *xrc_srqc;
	void *pas;
	int pas_size;
	int inlen;
	int err;

	pas_size  = get_pas_size(in);
	inlen	  = MLX5_ST_SZ_BYTES(create_xrc_srq_in) + pas_size;
	create_in = kvzalloc(inlen, GFP_KERNEL);
	if (!create_in)
		return -ENOMEM;

	MLX5_SET(create_xrc_srq_in, create_in, uid, in->uid);
	xrc_srqc = MLX5_ADDR_OF(create_xrc_srq_in, create_in,
				xrc_srq_context_entry);
	pas	 = MLX5_ADDR_OF(create_xrc_srq_in, create_in, pas);

	set_srqc(xrc_srqc, in);
	MLX5_SET(xrc_srqc, xrc_srqc, user_index, in->user_index);
	memcpy(pas, in->pas, pas_size);
	MLX5_SET(create_xrc_srq_in, create_in, opcode,
		 MLX5_CMD_OP_CREATE_XRC_SRQ);

	memset(create_out, 0, sizeof(create_out));
	err = mlx5_cmd_exec(dev->mdev, create_in, inlen, create_out,
			    sizeof(create_out));
	if (err)
		goto out;

	srq->srqn = MLX5_GET(create_xrc_srq_out, create_out, xrc_srqn);
	srq->uid = in->uid;
out:
	kvfree(create_in);
	return err;
}