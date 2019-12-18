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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_eswitch {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  source_port; } ;
struct TYPE_3__ {int /*<<< orphan*/  metadata_reg_c_0; } ;

/* Variables and functions */
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_MATCH_MISC_PARAMETERS ; 
 int /*<<< orphan*/  MLX5_MATCH_MISC_PARAMETERS_2 ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET_TO_ONES (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_flow_group_in ; 
 int /*<<< orphan*/  fte_match_param ; 
 void* match_criteria ; 
 int /*<<< orphan*/  match_criteria_enable ; 
 TYPE_2__ misc_parameters ; 
 TYPE_1__ misc_parameters_2 ; 
 scalar_t__ mlx5_eswitch_vport_match_metadata_enabled (struct mlx5_eswitch*) ; 

__attribute__((used)) static void esw_set_flow_group_source_port(struct mlx5_eswitch *esw,
					   u32 *flow_group_in)
{
	void *match_criteria = MLX5_ADDR_OF(create_flow_group_in,
					    flow_group_in,
					    match_criteria);

	if (mlx5_eswitch_vport_match_metadata_enabled(esw)) {
		MLX5_SET(create_flow_group_in, flow_group_in,
			 match_criteria_enable,
			 MLX5_MATCH_MISC_PARAMETERS_2);

		MLX5_SET_TO_ONES(fte_match_param, match_criteria,
				 misc_parameters_2.metadata_reg_c_0);
	} else {
		MLX5_SET(create_flow_group_in, flow_group_in,
			 match_criteria_enable,
			 MLX5_MATCH_MISC_PARAMETERS);

		MLX5_SET_TO_ONES(fte_match_param, match_criteria,
				 misc_parameters.source_port);
	}
}