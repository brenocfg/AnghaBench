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
struct mlx5dr_match_spec {int dummy; } ;

/* Variables and functions */
 scalar_t__ dr_mask_is_ipv4_set (struct mlx5dr_match_spec*) ; 
 scalar_t__ dr_mask_is_l3_base_set (struct mlx5dr_match_spec*) ; 
 scalar_t__ dr_mask_is_tcp_udp_base_set (struct mlx5dr_match_spec*) ; 

__attribute__((used)) static bool dr_mask_is_ipv4_5_tuple_set(struct mlx5dr_match_spec *spec)
{
	return (dr_mask_is_l3_base_set(spec) ||
		dr_mask_is_tcp_udp_base_set(spec) ||
		dr_mask_is_ipv4_set(spec));
}