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
struct TYPE_3__ {int /*<<< orphan*/  pdn; } ;
struct TYPE_4__ {int /*<<< orphan*/  loaded; } ;
struct mlx5_fw_tracer {TYPE_1__ buff; int /*<<< orphan*/  nb; int /*<<< orphan*/  read_fw_strings_work; int /*<<< orphan*/  work_queue; TYPE_2__ str_db; struct mlx5_core_dev* dev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_TRACER ; 
 scalar_t__ IS_ERR_OR_NULL (struct mlx5_fw_tracer*) ; 
 int /*<<< orphan*/  MLX5_NB_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_tracer_event ; 
 int mlx5_core_alloc_pd (struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_core_dealloc_pd (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int) ; 
 int /*<<< orphan*/  mlx5_eq_notifier_register (struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 
 int mlx5_fw_tracer_create_mkey (struct mlx5_fw_tracer*) ; 
 int /*<<< orphan*/  mlx5_fw_tracer_start (struct mlx5_fw_tracer*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int mlx5_fw_tracer_init(struct mlx5_fw_tracer *tracer)
{
	struct mlx5_core_dev *dev;
	int err;

	if (IS_ERR_OR_NULL(tracer))
		return 0;

	dev = tracer->dev;

	if (!tracer->str_db.loaded)
		queue_work(tracer->work_queue, &tracer->read_fw_strings_work);

	err = mlx5_core_alloc_pd(dev, &tracer->buff.pdn);
	if (err) {
		mlx5_core_warn(dev, "FWTracer: Failed to allocate PD %d\n", err);
		return err;
	}

	err = mlx5_fw_tracer_create_mkey(tracer);
	if (err) {
		mlx5_core_warn(dev, "FWTracer: Failed to create mkey %d\n", err);
		goto err_dealloc_pd;
	}

	MLX5_NB_INIT(&tracer->nb, fw_tracer_event, DEVICE_TRACER);
	mlx5_eq_notifier_register(dev, &tracer->nb);

	mlx5_fw_tracer_start(tracer);

	return 0;

err_dealloc_pd:
	mlx5_core_dealloc_pd(dev, tracer->buff.pdn);
	return err;
}