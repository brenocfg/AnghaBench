#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  flow_source; } ;
struct mlx5_flow_spec {TYPE_3__ flow_context; int /*<<< orphan*/  match_criteria_enable; int /*<<< orphan*/  match_criteria; int /*<<< orphan*/  match_value; } ;
struct mlx5_eswitch {int /*<<< orphan*/  dev; } ;
struct mlx5_esw_flow_attr {TYPE_2__* in_rep; TYPE_4__* in_mdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  eswitch; } ;
struct TYPE_8__ {TYPE_1__ priv; } ;
struct TYPE_6__ {scalar_t__ vport; } ;

/* Variables and functions */
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_ESW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_ESW_FLOWTABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_GEN (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_FLOW_CONTEXT_FLOW_SOURCE_UPLINK ; 
 int /*<<< orphan*/  MLX5_MATCH_MISC_PARAMETERS ; 
 int /*<<< orphan*/  MLX5_MATCH_MISC_PARAMETERS_2 ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  MLX5_SET_TO_ONES (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_VPORT_UPLINK ; 
 int /*<<< orphan*/  flow_source ; 
 int /*<<< orphan*/  fte_match_param ; 
 int /*<<< orphan*/  fte_match_set_misc ; 
 int /*<<< orphan*/  fte_match_set_misc2 ; 
 scalar_t__ memchr_inv (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  merged_eswitch ; 
 int /*<<< orphan*/  metadata_reg_c_0 ; 
 int /*<<< orphan*/  misc_parameters ; 
 int /*<<< orphan*/  misc_parameters_2 ; 
 scalar_t__ mlx5_eswitch_get_vport_metadata_for_match (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ mlx5_eswitch_vport_match_metadata_enabled (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  source_eswitch_owner_vhca_id ; 
 int /*<<< orphan*/  source_port ; 
 int /*<<< orphan*/  vhca_id ; 

__attribute__((used)) static void
mlx5_eswitch_set_rule_source_port(struct mlx5_eswitch *esw,
				  struct mlx5_flow_spec *spec,
				  struct mlx5_esw_flow_attr *attr)
{
	void *misc2;
	void *misc;

	/* Use metadata matching because vport is not represented by single
	 * VHCA in dual-port RoCE mode, and matching on source vport may fail.
	 */
	if (mlx5_eswitch_vport_match_metadata_enabled(esw)) {
		misc2 = MLX5_ADDR_OF(fte_match_param, spec->match_value, misc_parameters_2);
		MLX5_SET(fte_match_set_misc2, misc2, metadata_reg_c_0,
			 mlx5_eswitch_get_vport_metadata_for_match(attr->in_mdev->priv.eswitch,
								   attr->in_rep->vport));

		misc2 = MLX5_ADDR_OF(fte_match_param, spec->match_criteria, misc_parameters_2);
		MLX5_SET_TO_ONES(fte_match_set_misc2, misc2, metadata_reg_c_0);

		spec->match_criteria_enable |= MLX5_MATCH_MISC_PARAMETERS_2;
		misc = MLX5_ADDR_OF(fte_match_param, spec->match_criteria, misc_parameters);
		if (memchr_inv(misc, 0, MLX5_ST_SZ_BYTES(fte_match_set_misc)))
			spec->match_criteria_enable |= MLX5_MATCH_MISC_PARAMETERS;
	} else {
		misc = MLX5_ADDR_OF(fte_match_param, spec->match_value, misc_parameters);
		MLX5_SET(fte_match_set_misc, misc, source_port, attr->in_rep->vport);

		if (MLX5_CAP_ESW(esw->dev, merged_eswitch))
			MLX5_SET(fte_match_set_misc, misc,
				 source_eswitch_owner_vhca_id,
				 MLX5_CAP_GEN(attr->in_mdev, vhca_id));

		misc = MLX5_ADDR_OF(fte_match_param, spec->match_criteria, misc_parameters);
		MLX5_SET_TO_ONES(fte_match_set_misc, misc, source_port);
		if (MLX5_CAP_ESW(esw->dev, merged_eswitch))
			MLX5_SET_TO_ONES(fte_match_set_misc, misc,
					 source_eswitch_owner_vhca_id);

		spec->match_criteria_enable |= MLX5_MATCH_MISC_PARAMETERS;
	}

	if (MLX5_CAP_ESW_FLOWTABLE(esw->dev, flow_source) &&
	    attr->in_rep->vport == MLX5_VPORT_UPLINK)
		spec->flow_context.flow_source = MLX5_FLOW_CONTEXT_FLOW_SOURCE_UPLINK;
}