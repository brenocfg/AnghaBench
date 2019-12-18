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
struct mlxsw_sp_rif_ipip_lb {int /*<<< orphan*/  ul_rif_id; } ;
struct mlxsw_sp_rif {struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 struct mlxsw_sp_rif* mlxsw_sp_rif_by_index (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_rif_ipip_lb_op (struct mlxsw_sp_rif_ipip_lb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct mlxsw_sp_rif_ipip_lb* mlxsw_sp_rif_ipip_lb_rif (struct mlxsw_sp_rif*) ; 
 int /*<<< orphan*/  mlxsw_sp_ul_rif_put (struct mlxsw_sp_rif*) ; 

__attribute__((used)) static void mlxsw_sp2_rif_ipip_lb_deconfigure(struct mlxsw_sp_rif *rif)
{
	struct mlxsw_sp_rif_ipip_lb *lb_rif = mlxsw_sp_rif_ipip_lb_rif(rif);
	struct mlxsw_sp *mlxsw_sp = rif->mlxsw_sp;
	struct mlxsw_sp_rif *ul_rif;

	ul_rif = mlxsw_sp_rif_by_index(mlxsw_sp, lb_rif->ul_rif_id);
	mlxsw_sp_rif_ipip_lb_op(lb_rif, 0, lb_rif->ul_rif_id, false);
	mlxsw_sp_ul_rif_put(ul_rif);
}