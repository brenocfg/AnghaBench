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
struct mlxsw_sp_rif {size_t rif_index; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {TYPE_1__* router; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** rifs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlxsw_sp_rif*) ; 
 int /*<<< orphan*/  mlxsw_sp_rif_ipip_lb_ul_rif_op (struct mlxsw_sp_rif*,int) ; 

__attribute__((used)) static void mlxsw_sp_ul_rif_destroy(struct mlxsw_sp_rif *ul_rif)
{
	struct mlxsw_sp *mlxsw_sp = ul_rif->mlxsw_sp;

	mlxsw_sp_rif_ipip_lb_ul_rif_op(ul_rif, false);
	mlxsw_sp->router->rifs[ul_rif->rif_index] = NULL;
	kfree(ul_rif);
}