#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mlx5e_rqt {int enabled; int /*<<< orphan*/  rqtn; } ;
struct TYPE_2__ {int rqn; } ;
struct mlx5e_priv {TYPE_1__ drop_rq; struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,int /*<<< orphan*/ ,int) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_rqt_in ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kvzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_core_create_rqt (struct mlx5_core_dev*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rq_num ; 
 int /*<<< orphan*/  rqt_actual_size ; 
 int /*<<< orphan*/  rqt_context ; 
 int /*<<< orphan*/  rqt_max_size ; 

__attribute__((used)) static int
mlx5e_create_rqt(struct mlx5e_priv *priv, int sz, struct mlx5e_rqt *rqt)
{
	struct mlx5_core_dev *mdev = priv->mdev;
	void *rqtc;
	int inlen;
	int err;
	u32 *in;
	int i;

	inlen = MLX5_ST_SZ_BYTES(create_rqt_in) + sizeof(u32) * sz;
	in = kvzalloc(inlen, GFP_KERNEL);
	if (!in)
		return -ENOMEM;

	rqtc = MLX5_ADDR_OF(create_rqt_in, in, rqt_context);

	MLX5_SET(rqtc, rqtc, rqt_actual_size, sz);
	MLX5_SET(rqtc, rqtc, rqt_max_size, sz);

	for (i = 0; i < sz; i++)
		MLX5_SET(rqtc, rqtc, rq_num[i], priv->drop_rq.rqn);

	err = mlx5_core_create_rqt(mdev, in, inlen, &rqt->rqtn);
	if (!err)
		rqt->enabled = true;

	kvfree(in);
	return err;
}