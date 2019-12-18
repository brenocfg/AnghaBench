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
struct mlx5dr_match_spec {scalar_t__ ip_dscp; scalar_t__ ip_ecn; scalar_t__ tcp_flags; scalar_t__ frag; scalar_t__ ip_protocol; } ;

/* Variables and functions */

__attribute__((used)) static bool dr_mask_is_l3_base_set(struct mlx5dr_match_spec *spec)
{
	return (spec->ip_protocol || spec->frag || spec->tcp_flags ||
		spec->ip_ecn || spec->ip_dscp);
}