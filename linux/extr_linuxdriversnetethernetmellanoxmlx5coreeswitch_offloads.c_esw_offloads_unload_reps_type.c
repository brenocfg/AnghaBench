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
struct mlx5_eswitch_rep {TYPE_2__* rep_if; } ;
struct TYPE_3__ {struct mlx5_eswitch_rep* vport_reps; } ;
struct mlx5_eswitch {TYPE_1__ offloads; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* unload ) (struct mlx5_eswitch_rep*) ;int /*<<< orphan*/  valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct mlx5_eswitch_rep*) ; 

__attribute__((used)) static void esw_offloads_unload_reps_type(struct mlx5_eswitch *esw, int nvports,
					  u8 rep_type)
{
	struct mlx5_eswitch_rep *rep;
	int vport;

	for (vport = nvports - 1; vport >= 0; vport--) {
		rep = &esw->offloads.vport_reps[vport];
		if (!rep->rep_if[rep_type].valid)
			continue;

		rep->rep_if[rep_type].unload(rep);
	}
}