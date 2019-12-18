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
typedef  int /*<<< orphan*/  u32 ;
struct pedit_headers_action {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct mlx5e_tc_flow_parse_attr {int /*<<< orphan*/  spec; } ;
struct mlx5e_priv {int dummy; } ;
struct TYPE_2__ {int prio; int /*<<< orphan*/  vid; } ;
struct flow_action_entry {TYPE_1__ vlan; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_FLOW_NAMESPACE_FDB ; 
 int MLX5_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int add_vlan_rewrite_action (struct mlx5e_priv*,int /*<<< orphan*/ ,struct flow_action_entry const*,struct mlx5e_tc_flow_parse_attr*,struct pedit_headers_action*,int /*<<< orphan*/ *,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  first_prio ; 
 int /*<<< orphan*/  fte_match_set_lyr_2_4 ; 
 int /*<<< orphan*/  get_match_headers_criteria (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_match_headers_value (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
add_vlan_prio_tag_rewrite_action(struct mlx5e_priv *priv,
				 struct mlx5e_tc_flow_parse_attr *parse_attr,
				 struct pedit_headers_action *hdrs,
				 u32 *action, struct netlink_ext_ack *extack)
{
	const struct flow_action_entry prio_tag_act = {
		.vlan.vid = 0,
		.vlan.prio =
			MLX5_GET(fte_match_set_lyr_2_4,
				 get_match_headers_value(*action,
							 &parse_attr->spec),
				 first_prio) &
			MLX5_GET(fte_match_set_lyr_2_4,
				 get_match_headers_criteria(*action,
							    &parse_attr->spec),
				 first_prio),
	};

	return add_vlan_rewrite_action(priv, MLX5_FLOW_NAMESPACE_FDB,
				       &prio_tag_act, parse_attr, hdrs, action,
				       extack);
}