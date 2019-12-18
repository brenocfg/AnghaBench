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
typedef  int u32 ;
struct TYPE_3__ {scalar_t__ flow_source; } ;
struct mlx5_flow_spec {int /*<<< orphan*/  match_value; int /*<<< orphan*/  match_criteria; TYPE_1__ flow_context; } ;
struct mlx5_eswitch {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  source_port; } ;

/* Variables and functions */
 scalar_t__ MLX5_CAP_ESW_FLOWTABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_FLOW_CONTEXT_FLOW_SOURCE_UPLINK ; 
 int MLX5_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_VPORT_UPLINK ; 
 int /*<<< orphan*/  flow_source ; 
 int /*<<< orphan*/  fte_match_param ; 
 TYPE_2__ misc_parameters ; 

__attribute__((used)) static bool mlx5_eswitch_offload_is_uplink_port(const struct mlx5_eswitch *esw,
						const struct mlx5_flow_spec *spec)
{
	u32 port_mask, port_value;

	if (MLX5_CAP_ESW_FLOWTABLE(esw->dev, flow_source))
		return spec->flow_context.flow_source ==
					MLX5_FLOW_CONTEXT_FLOW_SOURCE_UPLINK;

	port_mask = MLX5_GET(fte_match_param, spec->match_criteria,
			     misc_parameters.source_port);
	port_value = MLX5_GET(fte_match_param, spec->match_value,
			      misc_parameters.source_port);
	return (port_mask & port_value & 0xffff) == MLX5_VPORT_UPLINK;
}