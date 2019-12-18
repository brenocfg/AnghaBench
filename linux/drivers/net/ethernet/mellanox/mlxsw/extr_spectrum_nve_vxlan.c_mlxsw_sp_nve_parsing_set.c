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
struct mlxsw_sp {TYPE_1__* nve; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {scalar_t__ inc_parsing_depth_refs; } ;

/* Variables and functions */
 int MLXSW_SP_NVE_DEFAULT_PARSING_DEPTH ; 
 int MLXSW_SP_NVE_VXLAN_PARSING_DEPTH ; 
 int __mlxsw_sp_nve_parsing_set (struct mlxsw_sp*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_sp_nve_parsing_set(struct mlxsw_sp *mlxsw_sp,
				    __be16 udp_dport)
{
	int parsing_depth = mlxsw_sp->nve->inc_parsing_depth_refs ?
				MLXSW_SP_NVE_VXLAN_PARSING_DEPTH :
				MLXSW_SP_NVE_DEFAULT_PARSING_DEPTH;

	return __mlxsw_sp_nve_parsing_set(mlxsw_sp, parsing_depth, udp_dport);
}