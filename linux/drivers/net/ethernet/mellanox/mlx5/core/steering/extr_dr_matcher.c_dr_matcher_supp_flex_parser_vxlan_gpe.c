#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flex_protocols; } ;
struct TYPE_4__ {TYPE_1__ caps; } ;
struct mlx5dr_domain {TYPE_2__ info; } ;

/* Variables and functions */
 int MLX5_FLEX_PARSER_VXLAN_GPE_ENABLED ; 

__attribute__((used)) static bool
dr_matcher_supp_flex_parser_vxlan_gpe(struct mlx5dr_domain *dmn)
{
	return dmn->info.caps.flex_protocols &
	       MLX5_FLEX_PARSER_VXLAN_GPE_ENABLED;
}