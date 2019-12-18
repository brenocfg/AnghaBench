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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {scalar_t__ min_rate; scalar_t__ max_rate; } ;
struct TYPE_3__ {int /*<<< orphan*/  bw_share; } ;
struct mlx5_vport {TYPE_2__ info; TYPE_1__ qos; } ;
struct mlx5_eswitch {int /*<<< orphan*/  state_lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int EPERM ; 
 int /*<<< orphan*/  ESW_ALLOWED (struct mlx5_eswitch*) ; 
 scalar_t__ IS_ERR (struct mlx5_vport*) ; 
 void* MLX5_CAP_QOS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_MIN_BW_SHARE ; 
 int PTR_ERR (struct mlx5_vport*) ; 
 scalar_t__ calculate_vports_min_rate_divider (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  esw_bw_share ; 
 int /*<<< orphan*/  esw_rate_limit ; 
 int esw_vport_qos_config (struct mlx5_eswitch*,struct mlx5_vport*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_tsar_bw_share ; 
 struct mlx5_vport* mlx5_eswitch_get_vport (struct mlx5_eswitch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int normalize_vports_min_rate (struct mlx5_eswitch*,scalar_t__) ; 

int mlx5_eswitch_set_vport_rate(struct mlx5_eswitch *esw, u16 vport,
				u32 max_rate, u32 min_rate)
{
	struct mlx5_vport *evport = mlx5_eswitch_get_vport(esw, vport);
	u32 fw_max_bw_share;
	u32 previous_min_rate;
	u32 divider;
	bool min_rate_supported;
	bool max_rate_supported;
	int err = 0;

	if (!ESW_ALLOWED(esw))
		return -EPERM;
	if (IS_ERR(evport))
		return PTR_ERR(evport);

	fw_max_bw_share = MLX5_CAP_QOS(esw->dev, max_tsar_bw_share);
	min_rate_supported = MLX5_CAP_QOS(esw->dev, esw_bw_share) &&
				fw_max_bw_share >= MLX5_MIN_BW_SHARE;
	max_rate_supported = MLX5_CAP_QOS(esw->dev, esw_rate_limit);

	if ((min_rate && !min_rate_supported) || (max_rate && !max_rate_supported))
		return -EOPNOTSUPP;

	mutex_lock(&esw->state_lock);

	if (min_rate == evport->info.min_rate)
		goto set_max_rate;

	previous_min_rate = evport->info.min_rate;
	evport->info.min_rate = min_rate;
	divider = calculate_vports_min_rate_divider(esw);
	err = normalize_vports_min_rate(esw, divider);
	if (err) {
		evport->info.min_rate = previous_min_rate;
		goto unlock;
	}

set_max_rate:
	if (max_rate == evport->info.max_rate)
		goto unlock;

	err = esw_vport_qos_config(esw, evport, max_rate, evport->qos.bw_share);
	if (!err)
		evport->info.max_rate = max_rate;

unlock:
	mutex_unlock(&esw->state_lock);
	return err;
}