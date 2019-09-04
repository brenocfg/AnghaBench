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
struct mlx5_eswitch {int /*<<< orphan*/  dev; TYPE_1__ offloads; } ;
struct TYPE_4__ {int (* load ) (int /*<<< orphan*/ ,struct mlx5_eswitch_rep*) ;int /*<<< orphan*/  valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  esw_offloads_unload_reps_type (struct mlx5_eswitch*,int,size_t) ; 
 int stub1 (int /*<<< orphan*/ ,struct mlx5_eswitch_rep*) ; 

__attribute__((used)) static int esw_offloads_load_reps_type(struct mlx5_eswitch *esw, int nvports,
				       u8 rep_type)
{
	struct mlx5_eswitch_rep *rep;
	int vport;
	int err;

	for (vport = 0; vport < nvports; vport++) {
		rep = &esw->offloads.vport_reps[vport];
		if (!rep->rep_if[rep_type].valid)
			continue;

		err = rep->rep_if[rep_type].load(esw->dev, rep);
		if (err)
			goto err_reps;
	}

	return 0;

err_reps:
	esw_offloads_unload_reps_type(esw, vport, rep_type);
	return err;
}