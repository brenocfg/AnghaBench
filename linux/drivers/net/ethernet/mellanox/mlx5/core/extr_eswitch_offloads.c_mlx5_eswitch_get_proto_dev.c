#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlx5_eswitch_rep {TYPE_1__* rep_data; } ;
struct TYPE_5__ {TYPE_3__** rep_ops; } ;
struct mlx5_eswitch {TYPE_2__ offloads; } ;
struct TYPE_6__ {void* (* get_proto_dev ) (struct mlx5_eswitch_rep*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 scalar_t__ REP_LOADED ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct mlx5_eswitch_rep* mlx5_eswitch_get_rep (struct mlx5_eswitch*,int /*<<< orphan*/ ) ; 
 void* stub1 (struct mlx5_eswitch_rep*) ; 

void *mlx5_eswitch_get_proto_dev(struct mlx5_eswitch *esw,
				 u16 vport,
				 u8 rep_type)
{
	struct mlx5_eswitch_rep *rep;

	rep = mlx5_eswitch_get_rep(esw, vport);

	if (atomic_read(&rep->rep_data[rep_type].state) == REP_LOADED &&
	    esw->offloads.rep_ops[rep_type]->get_proto_dev)
		return esw->offloads.rep_ops[rep_type]->get_proto_dev(rep);
	return NULL;
}