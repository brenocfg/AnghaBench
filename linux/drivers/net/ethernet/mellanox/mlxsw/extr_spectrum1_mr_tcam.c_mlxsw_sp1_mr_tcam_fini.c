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
struct mlxsw_sp1_mr_tcam_region {int dummy; } ;
struct mlxsw_sp1_mr_tcam {struct mlxsw_sp1_mr_tcam_region* tcam_regions; } ;

/* Variables and functions */
 size_t MLXSW_SP_L3_PROTO_IPV4 ; 
 size_t MLXSW_SP_L3_PROTO_IPV6 ; 
 int /*<<< orphan*/  mlxsw_sp1_mr_tcam_region_fini (struct mlxsw_sp1_mr_tcam_region*) ; 

__attribute__((used)) static void mlxsw_sp1_mr_tcam_fini(void *priv)
{
	struct mlxsw_sp1_mr_tcam *mr_tcam = priv;
	struct mlxsw_sp1_mr_tcam_region *region = &mr_tcam->tcam_regions[0];

	mlxsw_sp1_mr_tcam_region_fini(&region[MLXSW_SP_L3_PROTO_IPV6]);
	mlxsw_sp1_mr_tcam_region_fini(&region[MLXSW_SP_L3_PROTO_IPV4]);
}