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
struct TYPE_2__ {int flags; } ;
struct mlx5_flow_spec {TYPE_1__ flow_context; int /*<<< orphan*/ * match_criteria; } ;
struct mlx5_flow_act {int action; } ;
struct mlx5_core_dev {int dummy; } ;
typedef  enum valid_spec { ____Placeholder_valid_spec } valid_spec ;

/* Variables and functions */
 int FLOW_CONTEXT_HAS_TAG ; 
 int MLX5_FLOW_CONTEXT_ACTION_DECRYPT ; 
 int MLX5_FLOW_CONTEXT_ACTION_DROP ; 
 int MLX5_FLOW_CONTEXT_ACTION_ENCRYPT ; 
 int VALID_SPEC_INVALID ; 
 int VALID_SPEC_NA ; 
 int VALID_SPEC_VALID ; 
 int mlx5_fs_is_ipsec_flow (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static enum valid_spec
is_valid_esp_aes_gcm(struct mlx5_core_dev *mdev,
		     const struct mlx5_flow_spec *spec,
		     const struct mlx5_flow_act *flow_act,
		     bool egress)
{
	const u32 *match_c = spec->match_criteria;
	bool is_crypto =
		(flow_act->action & (MLX5_FLOW_CONTEXT_ACTION_ENCRYPT |
				     MLX5_FLOW_CONTEXT_ACTION_DECRYPT));
	bool is_ipsec = mlx5_fs_is_ipsec_flow(match_c);
	bool is_drop = flow_act->action & MLX5_FLOW_CONTEXT_ACTION_DROP;

	/*
	 * Currently only crypto is supported in egress, when regular egress
	 * rules would be supported, always return VALID_SPEC_NA.
	 */
	if (!is_crypto)
		return VALID_SPEC_NA;

	return is_crypto && is_ipsec &&
		(!egress || (!is_drop &&
			     !(spec->flow_context.flags & FLOW_CONTEXT_HAS_TAG))) ?
		VALID_SPEC_VALID : VALID_SPEC_INVALID;
}