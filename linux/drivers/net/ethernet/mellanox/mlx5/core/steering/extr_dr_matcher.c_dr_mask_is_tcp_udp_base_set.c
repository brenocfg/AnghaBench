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
struct mlx5dr_match_spec {scalar_t__ udp_dport; scalar_t__ udp_sport; scalar_t__ tcp_dport; scalar_t__ tcp_sport; } ;

/* Variables and functions */

__attribute__((used)) static bool dr_mask_is_tcp_udp_base_set(struct mlx5dr_match_spec *spec)
{
	return (spec->tcp_sport || spec->tcp_dport ||
		spec->udp_sport || spec->udp_dport);
}