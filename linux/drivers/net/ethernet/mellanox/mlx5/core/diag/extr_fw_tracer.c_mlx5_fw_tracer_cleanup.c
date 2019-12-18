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
struct TYPE_2__ {int /*<<< orphan*/  pdn; int /*<<< orphan*/  mkey; } ;
struct mlx5_fw_tracer {TYPE_1__ buff; int /*<<< orphan*/  dev; scalar_t__ owner; int /*<<< orphan*/  handle_traces_work; int /*<<< orphan*/  ownership_change_work; int /*<<< orphan*/  nb; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct mlx5_fw_tracer*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_core_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  mlx5_core_dealloc_pd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_destroy_mkey (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_eq_notifier_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_fw_tracer_ownership_release (struct mlx5_fw_tracer*) ; 

void mlx5_fw_tracer_cleanup(struct mlx5_fw_tracer *tracer)
{
	if (IS_ERR_OR_NULL(tracer))
		return;

	mlx5_core_dbg(tracer->dev, "FWTracer: Cleanup, is owner ? (%d)\n",
		      tracer->owner);
	mlx5_eq_notifier_unregister(tracer->dev, &tracer->nb);
	cancel_work_sync(&tracer->ownership_change_work);
	cancel_work_sync(&tracer->handle_traces_work);

	if (tracer->owner)
		mlx5_fw_tracer_ownership_release(tracer);

	mlx5_core_destroy_mkey(tracer->dev, &tracer->buff.mkey);
	mlx5_core_dealloc_pd(tracer->dev, tracer->buff.pdn);
}