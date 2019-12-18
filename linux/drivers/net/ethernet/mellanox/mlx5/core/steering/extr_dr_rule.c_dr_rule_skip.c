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
struct TYPE_4__ {int metadata_reg_c_0; } ;
struct TYPE_3__ {int source_port; } ;
struct mlx5dr_match_param {TYPE_2__ misc2; TYPE_1__ misc; } ;
typedef  enum mlx5dr_ste_entry_type { ____Placeholder_mlx5dr_ste_entry_type } mlx5dr_ste_entry_type ;
typedef  enum mlx5dr_domain_type { ____Placeholder_mlx5dr_domain_type } mlx5dr_domain_type ;

/* Variables and functions */
 int MLX5DR_DOMAIN_TYPE_FDB ; 
 int MLX5DR_STE_TYPE_RX ; 
 int MLX5DR_STE_TYPE_TX ; 
 int WIRE_PORT ; 

__attribute__((used)) static bool dr_rule_skip(enum mlx5dr_domain_type domain,
			 enum mlx5dr_ste_entry_type ste_type,
			 struct mlx5dr_match_param *mask,
			 struct mlx5dr_match_param *value)
{
	if (domain != MLX5DR_DOMAIN_TYPE_FDB)
		return false;

	if (mask->misc.source_port) {
		if (ste_type == MLX5DR_STE_TYPE_RX)
			if (value->misc.source_port != WIRE_PORT)
				return true;

		if (ste_type == MLX5DR_STE_TYPE_TX)
			if (value->misc.source_port == WIRE_PORT)
				return true;
	}

	/* Metadata C can be used to describe the source vport */
	if (mask->misc2.metadata_reg_c_0) {
		if (ste_type == MLX5DR_STE_TYPE_RX)
			if ((value->misc2.metadata_reg_c_0 & WIRE_PORT) != WIRE_PORT)
				return true;

		if (ste_type == MLX5DR_STE_TYPE_TX)
			if ((value->misc2.metadata_reg_c_0 & WIRE_PORT) == WIRE_PORT)
				return true;
	}
	return false;
}