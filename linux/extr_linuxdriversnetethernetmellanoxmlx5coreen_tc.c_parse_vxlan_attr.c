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
struct tc_cls_flower_offload {int /*<<< orphan*/  mask; int /*<<< orphan*/  dissector; int /*<<< orphan*/  key; } ;
struct mlx5_flow_spec {int /*<<< orphan*/  match_value; int /*<<< orphan*/  match_criteria; } ;
struct flow_dissector_key_keyid {int /*<<< orphan*/  keyid; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_ENC_KEYID ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET_TO_ONES (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ dissector_uses_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fte_match_param ; 
 int /*<<< orphan*/  fte_match_set_lyr_2_4 ; 
 int /*<<< orphan*/  fte_match_set_misc ; 
 int /*<<< orphan*/  ip_protocol ; 
 int /*<<< orphan*/  misc_parameters ; 
 int /*<<< orphan*/  outer_headers ; 
 struct flow_dissector_key_keyid* skb_flow_dissector_target (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxlan_vni ; 

__attribute__((used)) static void parse_vxlan_attr(struct mlx5_flow_spec *spec,
			     struct tc_cls_flower_offload *f)
{
	void *headers_c = MLX5_ADDR_OF(fte_match_param, spec->match_criteria,
				       outer_headers);
	void *headers_v = MLX5_ADDR_OF(fte_match_param, spec->match_value,
				       outer_headers);
	void *misc_c = MLX5_ADDR_OF(fte_match_param, spec->match_criteria,
				    misc_parameters);
	void *misc_v = MLX5_ADDR_OF(fte_match_param, spec->match_value,
				    misc_parameters);

	MLX5_SET_TO_ONES(fte_match_set_lyr_2_4, headers_c, ip_protocol);
	MLX5_SET(fte_match_set_lyr_2_4, headers_v, ip_protocol, IPPROTO_UDP);

	if (dissector_uses_key(f->dissector, FLOW_DISSECTOR_KEY_ENC_KEYID)) {
		struct flow_dissector_key_keyid *key =
			skb_flow_dissector_target(f->dissector,
						  FLOW_DISSECTOR_KEY_ENC_KEYID,
						  f->key);
		struct flow_dissector_key_keyid *mask =
			skb_flow_dissector_target(f->dissector,
						  FLOW_DISSECTOR_KEY_ENC_KEYID,
						  f->mask);
		MLX5_SET(fte_match_set_misc, misc_c, vxlan_vni,
			 be32_to_cpu(mask->keyid));
		MLX5_SET(fte_match_set_misc, misc_v, vxlan_vni,
			 be32_to_cpu(key->keyid));
	}
}