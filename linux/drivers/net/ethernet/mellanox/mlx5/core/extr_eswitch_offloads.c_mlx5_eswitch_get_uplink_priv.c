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
struct mlx5_eswitch_rep {TYPE_1__* rep_data; } ;
struct mlx5_eswitch {int dummy; } ;
struct TYPE_2__ {void* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_VPORT_UPLINK ; 
 struct mlx5_eswitch_rep* mlx5_eswitch_get_rep (struct mlx5_eswitch*,int /*<<< orphan*/ ) ; 

void *mlx5_eswitch_get_uplink_priv(struct mlx5_eswitch *esw, u8 rep_type)
{
	struct mlx5_eswitch_rep *rep;

	rep = mlx5_eswitch_get_rep(esw, MLX5_VPORT_UPLINK);
	return rep->rep_data[rep_type].priv;
}