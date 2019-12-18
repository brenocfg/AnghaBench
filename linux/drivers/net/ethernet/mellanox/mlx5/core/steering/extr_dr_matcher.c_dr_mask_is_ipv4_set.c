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
struct mlx5dr_match_spec {scalar_t__ src_ip_31_0; scalar_t__ dst_ip_31_0; } ;

/* Variables and functions */

__attribute__((used)) static bool dr_mask_is_ipv4_set(struct mlx5dr_match_spec *spec)
{
	return (spec->dst_ip_31_0 || spec->src_ip_31_0);
}