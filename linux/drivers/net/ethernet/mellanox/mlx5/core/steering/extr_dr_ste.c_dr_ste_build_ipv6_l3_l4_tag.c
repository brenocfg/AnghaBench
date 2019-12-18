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
typedef  int /*<<< orphan*/  u8 ;
struct mlx5dr_ste_build {scalar_t__ inner; } ;
struct mlx5dr_match_spec {scalar_t__ tcp_flags; } ;
struct mlx5dr_match_param {struct mlx5dr_match_spec outer; struct mlx5dr_match_spec inner; } ;
struct dr_hw_ste_format {int /*<<< orphan*/ * tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  DR_STE_SET_TAG (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mlx5dr_match_spec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DR_STE_SET_TCP_FLAGS (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mlx5dr_match_spec*) ; 
 int /*<<< orphan*/  dscp ; 
 int /*<<< orphan*/  dst_port ; 
 int /*<<< orphan*/  ecn ; 
 int /*<<< orphan*/  eth_l4 ; 
 int /*<<< orphan*/  frag ; 
 int /*<<< orphan*/  fragmented ; 
 int /*<<< orphan*/  ip_dscp ; 
 int /*<<< orphan*/  ip_ecn ; 
 int /*<<< orphan*/  ip_protocol ; 
 int /*<<< orphan*/  ipv6_hop_limit ; 
 int /*<<< orphan*/  protocol ; 
 int /*<<< orphan*/  src_port ; 
 int /*<<< orphan*/  tcp_dport ; 
 int /*<<< orphan*/  tcp_sport ; 
 int /*<<< orphan*/  ttl_hoplimit ; 
 int /*<<< orphan*/  udp_dport ; 
 int /*<<< orphan*/  udp_sport ; 

__attribute__((used)) static int dr_ste_build_ipv6_l3_l4_tag(struct mlx5dr_match_param *value,
				       struct mlx5dr_ste_build *sb,
				       u8 *hw_ste_p)
{
	struct mlx5dr_match_spec *spec = sb->inner ? &value->inner : &value->outer;
	struct dr_hw_ste_format *hw_ste = (struct dr_hw_ste_format *)hw_ste_p;
	u8 *tag = hw_ste->tag;

	DR_STE_SET_TAG(eth_l4, tag, dst_port, spec, tcp_dport);
	DR_STE_SET_TAG(eth_l4, tag, src_port, spec, tcp_sport);
	DR_STE_SET_TAG(eth_l4, tag, dst_port, spec, udp_dport);
	DR_STE_SET_TAG(eth_l4, tag, src_port, spec, udp_sport);
	DR_STE_SET_TAG(eth_l4, tag, protocol, spec, ip_protocol);
	DR_STE_SET_TAG(eth_l4, tag, fragmented, spec, frag);
	DR_STE_SET_TAG(eth_l4, tag, dscp, spec, ip_dscp);
	DR_STE_SET_TAG(eth_l4, tag, ecn, spec, ip_ecn);
	DR_STE_SET_TAG(eth_l4, tag, ipv6_hop_limit, spec, ttl_hoplimit);

	if (spec->tcp_flags) {
		DR_STE_SET_TCP_FLAGS(eth_l4, tag, spec);
		spec->tcp_flags = 0;
	}

	return 0;
}