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
struct mlx5dr_match_misc3 {void* icmpv6_code; void* icmpv6_type; void* icmpv4_code; void* icmpv4_type; void* icmpv6_header_data; void* icmpv4_header_data; void* outer_vxlan_gpe_flags; void* outer_vxlan_gpe_next_protocol; void* outer_vxlan_gpe_vni; void* outer_tcp_ack_num; void* inner_tcp_ack_num; void* outer_tcp_seq_num; void* inner_tcp_seq_num; } ;

/* Variables and functions */
 void* MLX5_GET (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fte_match_set_misc3 ; 
 int /*<<< orphan*/  icmp_code ; 
 int /*<<< orphan*/  icmp_header_data ; 
 int /*<<< orphan*/  icmp_type ; 
 int /*<<< orphan*/  icmpv6_code ; 
 int /*<<< orphan*/  icmpv6_header_data ; 
 int /*<<< orphan*/  icmpv6_type ; 
 int /*<<< orphan*/  inner_tcp_ack_num ; 
 int /*<<< orphan*/  inner_tcp_seq_num ; 
 int /*<<< orphan*/  outer_tcp_ack_num ; 
 int /*<<< orphan*/  outer_tcp_seq_num ; 
 int /*<<< orphan*/  outer_vxlan_gpe_flags ; 
 int /*<<< orphan*/  outer_vxlan_gpe_next_protocol ; 
 int /*<<< orphan*/  outer_vxlan_gpe_vni ; 

__attribute__((used)) static void dr_ste_copy_mask_misc3(char *mask, struct mlx5dr_match_misc3 *spec)
{
	spec->inner_tcp_seq_num = MLX5_GET(fte_match_set_misc3, mask, inner_tcp_seq_num);
	spec->outer_tcp_seq_num = MLX5_GET(fte_match_set_misc3, mask, outer_tcp_seq_num);
	spec->inner_tcp_ack_num = MLX5_GET(fte_match_set_misc3, mask, inner_tcp_ack_num);
	spec->outer_tcp_ack_num = MLX5_GET(fte_match_set_misc3, mask, outer_tcp_ack_num);
	spec->outer_vxlan_gpe_vni =
		MLX5_GET(fte_match_set_misc3, mask, outer_vxlan_gpe_vni);
	spec->outer_vxlan_gpe_next_protocol =
		MLX5_GET(fte_match_set_misc3, mask, outer_vxlan_gpe_next_protocol);
	spec->outer_vxlan_gpe_flags =
		MLX5_GET(fte_match_set_misc3, mask, outer_vxlan_gpe_flags);
	spec->icmpv4_header_data = MLX5_GET(fte_match_set_misc3, mask, icmp_header_data);
	spec->icmpv6_header_data =
		MLX5_GET(fte_match_set_misc3, mask, icmpv6_header_data);
	spec->icmpv4_type = MLX5_GET(fte_match_set_misc3, mask, icmp_type);
	spec->icmpv4_code = MLX5_GET(fte_match_set_misc3, mask, icmp_code);
	spec->icmpv6_type = MLX5_GET(fte_match_set_misc3, mask, icmpv6_type);
	spec->icmpv6_code = MLX5_GET(fte_match_set_misc3, mask, icmpv6_code);
}