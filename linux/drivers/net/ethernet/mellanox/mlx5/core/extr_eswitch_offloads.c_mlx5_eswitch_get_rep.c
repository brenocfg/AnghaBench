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
typedef  int /*<<< orphan*/  u16 ;
struct mlx5_eswitch_rep {int dummy; } ;
struct TYPE_2__ {struct mlx5_eswitch_rep* vport_reps; } ;
struct mlx5_eswitch {int total_vports; TYPE_1__ offloads; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int mlx5_eswitch_vport_num_to_index (struct mlx5_eswitch*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlx5_eswitch_rep *mlx5_eswitch_get_rep(struct mlx5_eswitch *esw,
						     u16 vport_num)
{
	int idx = mlx5_eswitch_vport_num_to_index(esw, vport_num);

	WARN_ON(idx > esw->total_vports - 1);
	return &esw->offloads.vport_reps[idx];
}