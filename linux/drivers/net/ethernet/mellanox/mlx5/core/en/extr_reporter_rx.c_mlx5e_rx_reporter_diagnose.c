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
struct mlx5e_rq {int /*<<< orphan*/  cq; } ;
struct mlx5e_params {int /*<<< orphan*/  rq_wq_type; } ;
struct TYPE_4__ {int num; TYPE_1__** c; struct mlx5e_params params; } ;
struct mlx5e_priv {int /*<<< orphan*/  state_lock; TYPE_2__ channels; int /*<<< orphan*/  mdev; int /*<<< orphan*/  state; } ;
struct devlink_health_reporter {int dummy; } ;
struct devlink_fmsg {int dummy; } ;
struct TYPE_3__ {struct mlx5e_rq rq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5E_STATE_OPENED ; 
 int devlink_fmsg_arr_pair_nest_end (struct devlink_fmsg*) ; 
 int devlink_fmsg_arr_pair_nest_start (struct devlink_fmsg*,char*) ; 
 int devlink_fmsg_u32_pair_put (struct devlink_fmsg*,char*,int /*<<< orphan*/ ) ; 
 int devlink_fmsg_u64_pair_put (struct devlink_fmsg*,char*,int /*<<< orphan*/ ) ; 
 int devlink_fmsg_u8_pair_put (struct devlink_fmsg*,char*,int /*<<< orphan*/ ) ; 
 struct mlx5e_priv* devlink_health_reporter_priv (struct devlink_health_reporter*) ; 
 int /*<<< orphan*/  mlx5e_mpwqe_get_log_stride_size (int /*<<< orphan*/ ,struct mlx5e_params*,int /*<<< orphan*/ *) ; 
 int mlx5e_reporter_cq_common_diagnose (int /*<<< orphan*/ *,struct devlink_fmsg*) ; 
 int mlx5e_reporter_named_obj_nest_end (struct devlink_fmsg*) ; 
 int mlx5e_reporter_named_obj_nest_start (struct devlink_fmsg*,char*) ; 
 int /*<<< orphan*/  mlx5e_rqwq_get_size (struct mlx5e_rq*) ; 
 int mlx5e_rx_reporter_build_diagnose_output (struct mlx5e_rq*,struct devlink_fmsg*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx5e_rx_reporter_diagnose(struct devlink_health_reporter *reporter,
				      struct devlink_fmsg *fmsg)
{
	struct mlx5e_priv *priv = devlink_health_reporter_priv(reporter);
	struct mlx5e_params *params = &priv->channels.params;
	struct mlx5e_rq *generic_rq;
	u32 rq_stride, rq_sz;
	int i, err = 0;

	mutex_lock(&priv->state_lock);

	if (!test_bit(MLX5E_STATE_OPENED, &priv->state))
		goto unlock;

	generic_rq = &priv->channels.c[0]->rq;
	rq_sz = mlx5e_rqwq_get_size(generic_rq);
	rq_stride = BIT(mlx5e_mpwqe_get_log_stride_size(priv->mdev, params, NULL));

	err = mlx5e_reporter_named_obj_nest_start(fmsg, "Common config");
	if (err)
		goto unlock;

	err = mlx5e_reporter_named_obj_nest_start(fmsg, "RQ");
	if (err)
		goto unlock;

	err = devlink_fmsg_u8_pair_put(fmsg, "type", params->rq_wq_type);
	if (err)
		goto unlock;

	err = devlink_fmsg_u64_pair_put(fmsg, "stride size", rq_stride);
	if (err)
		goto unlock;

	err = devlink_fmsg_u32_pair_put(fmsg, "size", rq_sz);
	if (err)
		goto unlock;

	err = mlx5e_reporter_named_obj_nest_end(fmsg);
	if (err)
		goto unlock;

	err = mlx5e_reporter_cq_common_diagnose(&generic_rq->cq, fmsg);
	if (err)
		goto unlock;

	err = mlx5e_reporter_named_obj_nest_end(fmsg);
	if (err)
		goto unlock;

	err = devlink_fmsg_arr_pair_nest_start(fmsg, "RQs");
	if (err)
		goto unlock;

	for (i = 0; i < priv->channels.num; i++) {
		struct mlx5e_rq *rq = &priv->channels.c[i]->rq;

		err = mlx5e_rx_reporter_build_diagnose_output(rq, fmsg);
		if (err)
			goto unlock;
	}
	err = devlink_fmsg_arr_pair_nest_end(fmsg);
	if (err)
		goto unlock;
unlock:
	mutex_unlock(&priv->state_lock);
	return err;
}