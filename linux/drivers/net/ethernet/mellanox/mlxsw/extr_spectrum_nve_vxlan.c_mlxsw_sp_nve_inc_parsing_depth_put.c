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
struct mlxsw_sp {TYPE_2__* nve; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_3__ {int /*<<< orphan*/  udp_dport; } ;
struct TYPE_4__ {TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mlxsw_sp_nve_inc_parsing_depth_put (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 

void mlxsw_sp_nve_inc_parsing_depth_put(struct mlxsw_sp *mlxsw_sp)
{
	__be16 udp_dport = mlxsw_sp->nve->config.udp_dport;

	__mlxsw_sp_nve_inc_parsing_depth_put(mlxsw_sp, udp_dport);
}