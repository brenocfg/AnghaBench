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
typedef  int u8 ;
struct netlink_ext_ack {int dummy; } ;
struct TYPE_2__ {scalar_t__ trust_state; } ;
struct mlx5e_priv {TYPE_1__ dcbx_dp; } ;
struct mlx5_flow_spec {int /*<<< orphan*/  match_value; int /*<<< orphan*/  match_criteria; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_GET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_QPTS_TRUST_PCP ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int UNKNOWN_MATCH_PRIO ; 
 int /*<<< orphan*/  cvlan_tag ; 
 int /*<<< orphan*/  first_prio ; 
 int /*<<< orphan*/  fte_match_param ; 
 int /*<<< orphan*/  fte_match_set_lyr_2_4 ; 
 int /*<<< orphan*/  outer_headers ; 

__attribute__((used)) static int mlx5e_hairpin_get_prio(struct mlx5e_priv *priv,
				  struct mlx5_flow_spec *spec, u8 *match_prio,
				  struct netlink_ext_ack *extack)
{
	void *headers_c, *headers_v;
	u8 prio_val, prio_mask = 0;
	bool vlan_present;

#ifdef CONFIG_MLX5_CORE_EN_DCB
	if (priv->dcbx_dp.trust_state != MLX5_QPTS_TRUST_PCP) {
		NL_SET_ERR_MSG_MOD(extack,
				   "only PCP trust state supported for hairpin");
		return -EOPNOTSUPP;
	}
#endif
	headers_c = MLX5_ADDR_OF(fte_match_param, spec->match_criteria, outer_headers);
	headers_v = MLX5_ADDR_OF(fte_match_param, spec->match_value, outer_headers);

	vlan_present = MLX5_GET(fte_match_set_lyr_2_4, headers_v, cvlan_tag);
	if (vlan_present) {
		prio_mask = MLX5_GET(fte_match_set_lyr_2_4, headers_c, first_prio);
		prio_val = MLX5_GET(fte_match_set_lyr_2_4, headers_v, first_prio);
	}

	if (!vlan_present || !prio_mask) {
		prio_val = UNKNOWN_MATCH_PRIO;
	} else if (prio_mask != 0x7) {
		NL_SET_ERR_MSG_MOD(extack,
				   "masked priority match not supported for hairpin");
		return -EOPNOTSUPP;
	}

	*match_prio = prio_val;
	return 0;
}