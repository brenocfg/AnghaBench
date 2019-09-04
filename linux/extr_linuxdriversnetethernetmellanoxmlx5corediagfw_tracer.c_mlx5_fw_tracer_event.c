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
struct TYPE_2__ {int /*<<< orphan*/  loaded; } ;
struct mlx5_fw_tracer {int /*<<< orphan*/  handle_traces_work; int /*<<< orphan*/  work_queue; TYPE_1__ str_db; int /*<<< orphan*/  ownership_change_work; } ;
struct mlx5_eqe {int sub_type; } ;
struct mlx5_core_dev {int /*<<< orphan*/  intf_state; struct mlx5_fw_tracer* tracer; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_INTERFACE_STATE_UP ; 
#define  MLX5_TRACER_SUBTYPE_OWNERSHIP_CHANGE 129 
#define  MLX5_TRACER_SUBTYPE_TRACES_AVAILABLE 128 
 int /*<<< orphan*/  likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_dbg (struct mlx5_core_dev*,char*,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void mlx5_fw_tracer_event(struct mlx5_core_dev *dev, struct mlx5_eqe *eqe)
{
	struct mlx5_fw_tracer *tracer = dev->tracer;

	if (!tracer)
		return;

	switch (eqe->sub_type) {
	case MLX5_TRACER_SUBTYPE_OWNERSHIP_CHANGE:
		if (test_bit(MLX5_INTERFACE_STATE_UP, &dev->intf_state))
			queue_work(tracer->work_queue, &tracer->ownership_change_work);
		break;
	case MLX5_TRACER_SUBTYPE_TRACES_AVAILABLE:
		if (likely(tracer->str_db.loaded))
			queue_work(tracer->work_queue, &tracer->handle_traces_work);
		break;
	default:
		mlx5_core_dbg(dev, "FWTracer: Event with unrecognized subtype: sub_type %d\n",
			      eqe->sub_type);
	}
}