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
typedef  size_t u8 ;
struct mlx5_eswitch_rep {TYPE_1__* rep_if; } ;
struct mlx5_esw_offload {struct mlx5_eswitch_rep* vport_reps; } ;
struct mlx5_eswitch {scalar_t__ mode; TYPE_2__* vports; struct mlx5_esw_offload offloads; } ;
struct TYPE_4__ {scalar_t__ enabled; } ;
struct TYPE_3__ {int valid; int /*<<< orphan*/  (* unload ) (struct mlx5_eswitch_rep*) ;} ;

/* Variables and functions */
 scalar_t__ SRIOV_OFFLOADS ; 
 int /*<<< orphan*/  stub1 (struct mlx5_eswitch_rep*) ; 

void mlx5_eswitch_unregister_vport_rep(struct mlx5_eswitch *esw,
				       int vport_index, u8 rep_type)
{
	struct mlx5_esw_offload *offloads = &esw->offloads;
	struct mlx5_eswitch_rep *rep;

	rep = &offloads->vport_reps[vport_index];

	if (esw->mode == SRIOV_OFFLOADS && esw->vports[vport_index].enabled)
		rep->rep_if[rep_type].unload(rep);

	rep->rep_if[rep_type].valid = false;
}