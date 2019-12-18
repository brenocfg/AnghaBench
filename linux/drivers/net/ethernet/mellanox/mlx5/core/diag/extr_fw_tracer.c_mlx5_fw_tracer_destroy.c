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
struct mlx5_fw_tracer {int /*<<< orphan*/  work_queue; int /*<<< orphan*/  read_fw_strings_work; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct mlx5_fw_tracer*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx5_fw_tracer*) ; 
 int /*<<< orphan*/  mlx5_core_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlx5_fw_tracer_clean_print_hash (struct mlx5_fw_tracer*) ; 
 int /*<<< orphan*/  mlx5_fw_tracer_clean_ready_list (struct mlx5_fw_tracer*) ; 
 int /*<<< orphan*/  mlx5_fw_tracer_clean_saved_traces_array (struct mlx5_fw_tracer*) ; 
 int /*<<< orphan*/  mlx5_fw_tracer_destroy_log_buf (struct mlx5_fw_tracer*) ; 
 int /*<<< orphan*/  mlx5_fw_tracer_free_strings_db (struct mlx5_fw_tracer*) ; 

void mlx5_fw_tracer_destroy(struct mlx5_fw_tracer *tracer)
{
	if (IS_ERR_OR_NULL(tracer))
		return;

	mlx5_core_dbg(tracer->dev, "FWTracer: Destroy\n");

	cancel_work_sync(&tracer->read_fw_strings_work);
	mlx5_fw_tracer_clean_ready_list(tracer);
	mlx5_fw_tracer_clean_print_hash(tracer);
	mlx5_fw_tracer_clean_saved_traces_array(tracer);
	mlx5_fw_tracer_free_strings_db(tracer);
	mlx5_fw_tracer_destroy_log_buf(tracer);
	flush_workqueue(tracer->work_queue);
	destroy_workqueue(tracer->work_queue);
	kfree(tracer);
}