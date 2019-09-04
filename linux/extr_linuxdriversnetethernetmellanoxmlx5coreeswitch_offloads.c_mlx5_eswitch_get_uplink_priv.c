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
typedef  size_t u8 ;
struct mlx5_eswitch_rep {TYPE_1__* rep_if; } ;
struct mlx5_esw_offload {struct mlx5_eswitch_rep* vport_reps; } ;
struct mlx5_eswitch {struct mlx5_esw_offload offloads; } ;
struct TYPE_2__ {void* priv; } ;

/* Variables and functions */

void *mlx5_eswitch_get_uplink_priv(struct mlx5_eswitch *esw, u8 rep_type)
{
#define UPLINK_REP_INDEX 0
	struct mlx5_esw_offload *offloads = &esw->offloads;
	struct mlx5_eswitch_rep *rep;

	rep = &offloads->vport_reps[UPLINK_REP_INDEX];
	return rep->rep_if[rep_type].priv;
}