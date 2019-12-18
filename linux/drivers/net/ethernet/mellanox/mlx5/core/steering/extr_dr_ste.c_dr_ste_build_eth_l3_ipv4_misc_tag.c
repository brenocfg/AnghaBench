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
struct mlx5dr_match_spec {int dummy; } ;
struct mlx5dr_match_param {struct mlx5dr_match_spec outer; struct mlx5dr_match_spec inner; } ;
struct dr_hw_ste_format {int /*<<< orphan*/ * tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  DR_STE_SET_TAG (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mlx5dr_match_spec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_l3_ipv4_misc ; 
 int /*<<< orphan*/  time_to_live ; 
 int /*<<< orphan*/  ttl_hoplimit ; 

__attribute__((used)) static int dr_ste_build_eth_l3_ipv4_misc_tag(struct mlx5dr_match_param *value,
					     struct mlx5dr_ste_build *sb,
					     u8 *hw_ste_p)
{
	struct dr_hw_ste_format *hw_ste = (struct dr_hw_ste_format *)hw_ste_p;
	struct mlx5dr_match_spec *spec = sb->inner ? &value->inner : &value->outer;
	u8 *tag = hw_ste->tag;

	DR_STE_SET_TAG(eth_l3_ipv4_misc, tag, time_to_live, spec, ttl_hoplimit);

	return 0;
}