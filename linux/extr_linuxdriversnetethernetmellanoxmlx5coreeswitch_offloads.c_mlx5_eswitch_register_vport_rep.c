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
struct mlx5_eswitch_rep_if {int valid; int /*<<< orphan*/  priv; int /*<<< orphan*/  get_proto_dev; int /*<<< orphan*/  unload; int /*<<< orphan*/  load; } ;
struct mlx5_esw_offload {TYPE_1__* vport_reps; } ;
struct mlx5_eswitch {struct mlx5_esw_offload offloads; } ;
struct TYPE_2__ {struct mlx5_eswitch_rep_if* rep_if; } ;

/* Variables and functions */

void mlx5_eswitch_register_vport_rep(struct mlx5_eswitch *esw,
				     int vport_index,
				     struct mlx5_eswitch_rep_if *__rep_if,
				     u8 rep_type)
{
	struct mlx5_esw_offload *offloads = &esw->offloads;
	struct mlx5_eswitch_rep_if *rep_if;

	rep_if = &offloads->vport_reps[vport_index].rep_if[rep_type];

	rep_if->load   = __rep_if->load;
	rep_if->unload = __rep_if->unload;
	rep_if->get_proto_dev = __rep_if->get_proto_dev;
	rep_if->priv = __rep_if->priv;

	rep_if->valid = true;
}