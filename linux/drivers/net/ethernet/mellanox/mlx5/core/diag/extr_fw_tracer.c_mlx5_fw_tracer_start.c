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
struct mlx5_fw_tracer {struct mlx5_core_dev* dev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_core_dbg (struct mlx5_core_dev*,char*,...) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int) ; 
 int mlx5_fw_tracer_ownership_acquire (struct mlx5_fw_tracer*) ; 
 int /*<<< orphan*/  mlx5_fw_tracer_ownership_release (struct mlx5_fw_tracer*) ; 
 int mlx5_fw_tracer_set_mtrc_conf (struct mlx5_fw_tracer*) ; 
 int mlx5_fw_tracer_set_mtrc_ctrl (struct mlx5_fw_tracer*,int,int) ; 

__attribute__((used)) static int mlx5_fw_tracer_start(struct mlx5_fw_tracer *tracer)
{
	struct mlx5_core_dev *dev = tracer->dev;
	int err;

	err = mlx5_fw_tracer_ownership_acquire(tracer);
	if (err) {
		mlx5_core_dbg(dev, "FWTracer: Ownership was not granted %d\n", err);
		/* Don't fail since ownership can be acquired on a later FW event */
		return 0;
	}

	err = mlx5_fw_tracer_set_mtrc_conf(tracer);
	if (err) {
		mlx5_core_warn(dev, "FWTracer: Failed to set tracer configuration %d\n", err);
		goto release_ownership;
	}

	/* enable tracer & trace events */
	err = mlx5_fw_tracer_set_mtrc_ctrl(tracer, 1, 1);
	if (err) {
		mlx5_core_warn(dev, "FWTracer: Failed to enable tracer %d\n", err);
		goto release_ownership;
	}

	mlx5_core_dbg(dev, "FWTracer: Ownership granted and active\n");
	return 0;

release_ownership:
	mlx5_fw_tracer_ownership_release(tracer);
	return err;
}