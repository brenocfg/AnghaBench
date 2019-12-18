#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct mlx5_eswitch_rep {int dummy; } ;
struct mlx5_eswitch {int dummy; } ;

/* Variables and functions */
 struct mlx5_eswitch_rep* mlx5_eswitch_get_rep (struct mlx5_eswitch*,int /*<<< orphan*/ ) ; 

struct mlx5_eswitch_rep *mlx5_eswitch_vport_rep(struct mlx5_eswitch *esw,
						u16 vport)
{
	return mlx5_eswitch_get_rep(esw, vport);
}