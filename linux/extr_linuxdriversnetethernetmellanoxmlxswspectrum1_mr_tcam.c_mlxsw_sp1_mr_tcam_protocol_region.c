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
typedef  enum mlxsw_sp_l3proto { ____Placeholder_mlxsw_sp_l3proto } mlxsw_sp_l3proto ;

/* Variables and functions */

__attribute__((used)) static struct mlxsw_sp1_mr_tcam_region *
mlxsw_sp1_mr_tcam_protocol_region(struct mlxsw_sp1_mr_tcam *mr_tcam,
				  enum mlxsw_sp_l3proto proto)
{
	return &mr_tcam->tcam_regions[proto];
}