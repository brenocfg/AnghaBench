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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5dr_match_spec {void* dst_ip_31_0; void* dst_ip_63_32; void* dst_ip_95_64; void* dst_ip_127_96; void* src_ip_31_0; void* src_ip_63_32; void* src_ip_95_64; void* src_ip_127_96; void* udp_dport; void* udp_sport; void* ttl_hoplimit; void* tcp_dport; void* tcp_sport; void* tcp_flags; void* ip_version; void* frag; void* svlan_tag; void* cvlan_tag; void* ip_ecn; void* ip_dscp; void* ip_protocol; void* first_vid; void* first_cfi; void* first_prio; void* dmac_15_0; void* dmac_47_16; void* ethertype; void* smac_15_0; void* smac_47_16; } ;
typedef  int /*<<< orphan*/  raw_ip ;
struct TYPE_6__ {int /*<<< orphan*/  ipv6; } ;
struct TYPE_8__ {TYPE_2__ ipv6_layout; } ;
struct TYPE_5__ {int /*<<< orphan*/  ipv6; } ;
struct TYPE_7__ {TYPE_1__ ipv6_layout; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_ADDR_OF (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 void* MLX5_GET (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvlan_tag ; 
 int /*<<< orphan*/  dmac_15_0 ; 
 int /*<<< orphan*/  dmac_47_16 ; 
 TYPE_4__ dst_ipv4_dst_ipv6 ; 
 int /*<<< orphan*/  ethertype ; 
 int /*<<< orphan*/  first_cfi ; 
 int /*<<< orphan*/  first_prio ; 
 int /*<<< orphan*/  first_vid ; 
 int /*<<< orphan*/  frag ; 
 int /*<<< orphan*/  fte_match_set_lyr_2_4 ; 
 int /*<<< orphan*/  ip_dscp ; 
 int /*<<< orphan*/  ip_ecn ; 
 int /*<<< orphan*/  ip_protocol ; 
 int /*<<< orphan*/  ip_version ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smac_15_0 ; 
 int /*<<< orphan*/  smac_47_16 ; 
 TYPE_3__ src_ipv4_src_ipv6 ; 
 int /*<<< orphan*/  svlan_tag ; 
 int /*<<< orphan*/  tcp_dport ; 
 int /*<<< orphan*/  tcp_flags ; 
 int /*<<< orphan*/  tcp_sport ; 
 int /*<<< orphan*/  ttl_hoplimit ; 
 int /*<<< orphan*/  udp_dport ; 
 int /*<<< orphan*/  udp_sport ; 

__attribute__((used)) static void dr_ste_copy_mask_spec(char *mask, struct mlx5dr_match_spec *spec)
{
	u32 raw_ip[4];

	spec->smac_47_16 = MLX5_GET(fte_match_set_lyr_2_4, mask, smac_47_16);

	spec->smac_15_0 = MLX5_GET(fte_match_set_lyr_2_4, mask, smac_15_0);
	spec->ethertype = MLX5_GET(fte_match_set_lyr_2_4, mask, ethertype);

	spec->dmac_47_16 = MLX5_GET(fte_match_set_lyr_2_4, mask, dmac_47_16);

	spec->dmac_15_0 = MLX5_GET(fte_match_set_lyr_2_4, mask, dmac_15_0);
	spec->first_prio = MLX5_GET(fte_match_set_lyr_2_4, mask, first_prio);
	spec->first_cfi = MLX5_GET(fte_match_set_lyr_2_4, mask, first_cfi);
	spec->first_vid = MLX5_GET(fte_match_set_lyr_2_4, mask, first_vid);

	spec->ip_protocol = MLX5_GET(fte_match_set_lyr_2_4, mask, ip_protocol);
	spec->ip_dscp = MLX5_GET(fte_match_set_lyr_2_4, mask, ip_dscp);
	spec->ip_ecn = MLX5_GET(fte_match_set_lyr_2_4, mask, ip_ecn);
	spec->cvlan_tag = MLX5_GET(fte_match_set_lyr_2_4, mask, cvlan_tag);
	spec->svlan_tag = MLX5_GET(fte_match_set_lyr_2_4, mask, svlan_tag);
	spec->frag = MLX5_GET(fte_match_set_lyr_2_4, mask, frag);
	spec->ip_version = MLX5_GET(fte_match_set_lyr_2_4, mask, ip_version);
	spec->tcp_flags = MLX5_GET(fte_match_set_lyr_2_4, mask, tcp_flags);
	spec->tcp_sport = MLX5_GET(fte_match_set_lyr_2_4, mask, tcp_sport);
	spec->tcp_dport = MLX5_GET(fte_match_set_lyr_2_4, mask, tcp_dport);

	spec->ttl_hoplimit = MLX5_GET(fte_match_set_lyr_2_4, mask, ttl_hoplimit);

	spec->udp_sport = MLX5_GET(fte_match_set_lyr_2_4, mask, udp_sport);
	spec->udp_dport = MLX5_GET(fte_match_set_lyr_2_4, mask, udp_dport);

	memcpy(raw_ip, MLX5_ADDR_OF(fte_match_set_lyr_2_4, mask,
				    src_ipv4_src_ipv6.ipv6_layout.ipv6),
				    sizeof(raw_ip));

	spec->src_ip_127_96 = be32_to_cpu(raw_ip[0]);
	spec->src_ip_95_64 = be32_to_cpu(raw_ip[1]);
	spec->src_ip_63_32 = be32_to_cpu(raw_ip[2]);
	spec->src_ip_31_0 = be32_to_cpu(raw_ip[3]);

	memcpy(raw_ip, MLX5_ADDR_OF(fte_match_set_lyr_2_4, mask,
				    dst_ipv4_dst_ipv6.ipv6_layout.ipv6),
				    sizeof(raw_ip));

	spec->dst_ip_127_96 = be32_to_cpu(raw_ip[0]);
	spec->dst_ip_95_64 = be32_to_cpu(raw_ip[1]);
	spec->dst_ip_63_32 = be32_to_cpu(raw_ip[2]);
	spec->dst_ip_31_0 = be32_to_cpu(raw_ip[3]);
}