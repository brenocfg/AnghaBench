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
struct TYPE_2__ {void* (* get_proto_dev ) (struct mlx5_eswitch_rep*) ;scalar_t__ valid; } ;

/* Variables and functions */
 int FDB_UPLINK_VPORT ; 
 int UPLINK_REP_INDEX ; 
 void* stub1 (struct mlx5_eswitch_rep*) ; 

void *mlx5_eswitch_get_proto_dev(struct mlx5_eswitch *esw,
				 int vport,
				 u8 rep_type)
{
	struct mlx5_esw_offload *offloads = &esw->offloads;
	struct mlx5_eswitch_rep *rep;

	if (vport == FDB_UPLINK_VPORT)
		vport = UPLINK_REP_INDEX;

	rep = &offloads->vport_reps[vport];

	if (rep->rep_if[rep_type].valid &&
	    rep->rep_if[rep_type].get_proto_dev)
		return rep->rep_if[rep_type].get_proto_dev(rep);
	return NULL;
}