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
struct mlx5_fw_reporter_ctx {int dummy; } ;
struct mlx5_core_dev {int /*<<< orphan*/  tracer; } ;
struct devlink_health_reporter {int dummy; } ;
struct devlink_fmsg {int dummy; } ;

/* Variables and functions */
 struct mlx5_core_dev* devlink_health_reporter_priv (struct devlink_health_reporter*) ; 
 int mlx5_fw_reporter_ctx_pairs_put (struct devlink_fmsg*,struct mlx5_fw_reporter_ctx*) ; 
 int mlx5_fw_reporter_heath_buffer_data_put (struct mlx5_core_dev*,struct devlink_fmsg*) ; 
 int mlx5_fw_tracer_get_saved_traces_objects (int /*<<< orphan*/ ,struct devlink_fmsg*) ; 
 int mlx5_fw_tracer_trigger_core_dump_general (struct mlx5_core_dev*) ; 

__attribute__((used)) static int
mlx5_fw_reporter_dump(struct devlink_health_reporter *reporter,
		      struct devlink_fmsg *fmsg, void *priv_ctx)
{
	struct mlx5_core_dev *dev = devlink_health_reporter_priv(reporter);
	int err;

	err = mlx5_fw_tracer_trigger_core_dump_general(dev);
	if (err)
		return err;

	if (priv_ctx) {
		struct mlx5_fw_reporter_ctx *fw_reporter_ctx = priv_ctx;

		err = mlx5_fw_reporter_ctx_pairs_put(fmsg, fw_reporter_ctx);
		if (err)
			return err;
	}

	err = mlx5_fw_reporter_heath_buffer_data_put(dev, fmsg);
	if (err)
		return err;
	return mlx5_fw_tracer_get_saved_traces_objects(dev->tracer, fmsg);
}