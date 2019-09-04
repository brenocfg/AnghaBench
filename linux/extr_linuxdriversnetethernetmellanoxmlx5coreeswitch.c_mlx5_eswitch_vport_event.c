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
typedef  size_t u16 ;
struct mlx5_vport {int /*<<< orphan*/  vport_change_handler; scalar_t__ enabled; } ;
struct mlx5_eswitch {int /*<<< orphan*/  work_queue; struct mlx5_vport* vports; } ;
struct mlx5_eqe_vport_change {int /*<<< orphan*/  vport_num; } ;
struct TYPE_2__ {struct mlx5_eqe_vport_change vport_change; } ;
struct mlx5_eqe {TYPE_1__ data; } ;

/* Variables and functions */
 size_t be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,size_t) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void mlx5_eswitch_vport_event(struct mlx5_eswitch *esw, struct mlx5_eqe *eqe)
{
	struct mlx5_eqe_vport_change *vc_eqe = &eqe->data.vport_change;
	u16 vport_num = be16_to_cpu(vc_eqe->vport_num);
	struct mlx5_vport *vport;

	if (!esw) {
		pr_warn("MLX5 E-Switch: vport %d got an event while eswitch is not initialized\n",
			vport_num);
		return;
	}

	vport = &esw->vports[vport_num];
	if (vport->enabled)
		queue_work(esw->work_queue, &vport->vport_change_handler);
}