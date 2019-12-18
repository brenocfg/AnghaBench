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
struct mlxsw_sp_rif {struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_SP_RIF_COUNTER_EGRESS ; 
 int /*<<< orphan*/  mlxsw_sp_rif_counter_free (struct mlxsw_sp*,struct mlxsw_sp_rif*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_sp_rif_counters_free(struct mlxsw_sp_rif *rif)
{
	struct mlxsw_sp *mlxsw_sp = rif->mlxsw_sp;

	mlxsw_sp_rif_counter_free(mlxsw_sp, rif, MLXSW_SP_RIF_COUNTER_EGRESS);
}