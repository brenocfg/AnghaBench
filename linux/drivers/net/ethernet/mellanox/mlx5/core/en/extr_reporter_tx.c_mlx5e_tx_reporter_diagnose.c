#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mlx5e_txqsq {int /*<<< orphan*/  cq; int /*<<< orphan*/  wq; } ;
struct TYPE_3__ {int num_tc; } ;
struct TYPE_4__ {int num; TYPE_1__ params; struct mlx5e_channel** c; } ;
struct mlx5e_priv {int /*<<< orphan*/  state_lock; TYPE_2__ channels; int /*<<< orphan*/  state; struct mlx5e_txqsq** txq2sq; } ;
struct mlx5e_channel {struct mlx5e_txqsq* sq; } ;
struct devlink_health_reporter {int dummy; } ;
struct devlink_fmsg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_STATE_OPENED ; 
 int /*<<< orphan*/  MLX5_SEND_WQE_BB ; 
 int devlink_fmsg_arr_pair_nest_end (struct devlink_fmsg*) ; 
 int devlink_fmsg_arr_pair_nest_start (struct devlink_fmsg*,char*) ; 
 int devlink_fmsg_u32_pair_put (struct devlink_fmsg*,char*,int /*<<< orphan*/ ) ; 
 int devlink_fmsg_u64_pair_put (struct devlink_fmsg*,char*,int /*<<< orphan*/ ) ; 
 struct mlx5e_priv* devlink_health_reporter_priv (struct devlink_health_reporter*) ; 
 int /*<<< orphan*/  mlx5_wq_cyc_get_size (int /*<<< orphan*/ *) ; 
 int mlx5e_reporter_cq_common_diagnose (int /*<<< orphan*/ *,struct devlink_fmsg*) ; 
 int mlx5e_reporter_named_obj_nest_end (struct devlink_fmsg*) ; 
 int mlx5e_reporter_named_obj_nest_start (struct devlink_fmsg*,char*) ; 
 int mlx5e_tx_reporter_build_diagnose_output (struct devlink_fmsg*,struct mlx5e_txqsq*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx5e_tx_reporter_diagnose(struct devlink_health_reporter *reporter,
				      struct devlink_fmsg *fmsg)
{
	struct mlx5e_priv *priv = devlink_health_reporter_priv(reporter);
	struct mlx5e_txqsq *generic_sq = priv->txq2sq[0];
	u32 sq_stride, sq_sz;

	int i, tc, err = 0;

	mutex_lock(&priv->state_lock);

	if (!test_bit(MLX5E_STATE_OPENED, &priv->state))
		goto unlock;

	sq_sz = mlx5_wq_cyc_get_size(&generic_sq->wq);
	sq_stride = MLX5_SEND_WQE_BB;

	err = mlx5e_reporter_named_obj_nest_start(fmsg, "Common Config");
	if (err)
		goto unlock;

	err = mlx5e_reporter_named_obj_nest_start(fmsg, "SQ");
	if (err)
		goto unlock;

	err = devlink_fmsg_u64_pair_put(fmsg, "stride size", sq_stride);
	if (err)
		goto unlock;

	err = devlink_fmsg_u32_pair_put(fmsg, "size", sq_sz);
	if (err)
		goto unlock;

	err = mlx5e_reporter_cq_common_diagnose(&generic_sq->cq, fmsg);
	if (err)
		goto unlock;

	err = mlx5e_reporter_named_obj_nest_end(fmsg);
	if (err)
		goto unlock;

	err = mlx5e_reporter_named_obj_nest_end(fmsg);
	if (err)
		goto unlock;

	err = devlink_fmsg_arr_pair_nest_start(fmsg, "SQs");
	if (err)
		goto unlock;

	for (i = 0; i < priv->channels.num; i++) {
		struct mlx5e_channel *c = priv->channels.c[i];

		for (tc = 0; tc < priv->channels.params.num_tc; tc++) {
			struct mlx5e_txqsq *sq = &c->sq[tc];

			err = mlx5e_tx_reporter_build_diagnose_output(fmsg, sq, tc);
			if (err)
				goto unlock;
		}
	}
	err = devlink_fmsg_arr_pair_nest_end(fmsg);
	if (err)
		goto unlock;

unlock:
	mutex_unlock(&priv->state_lock);
	return err;
}