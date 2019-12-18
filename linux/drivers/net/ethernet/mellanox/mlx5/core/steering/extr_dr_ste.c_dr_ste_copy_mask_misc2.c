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
struct mlx5dr_match_misc2 {void* metadata_reg_b; void* metadata_reg_a; void* metadata_reg_c_0; void* metadata_reg_c_1; void* metadata_reg_c_2; void* metadata_reg_c_3; void* metadata_reg_c_4; void* metadata_reg_c_5; void* metadata_reg_c_6; void* metadata_reg_c_7; void* outer_first_mpls_over_udp_ttl; void* outer_first_mpls_over_udp_s_bos; void* outer_first_mpls_over_udp_exp; void* outer_first_mpls_over_udp_label; void* outer_first_mpls_over_gre_ttl; void* outer_first_mpls_over_gre_s_bos; void* outer_first_mpls_over_gre_exp; void* outer_first_mpls_over_gre_label; void* inner_first_mpls_ttl; void* inner_first_mpls_s_bos; void* inner_first_mpls_exp; void* inner_first_mpls_label; void* outer_first_mpls_ttl; void* outer_first_mpls_s_bos; void* outer_first_mpls_exp; void* outer_first_mpls_label; } ;
struct TYPE_8__ {int /*<<< orphan*/  mpls_ttl; int /*<<< orphan*/  mpls_s_bos; int /*<<< orphan*/  mpls_exp; int /*<<< orphan*/  mpls_label; } ;
struct TYPE_7__ {int /*<<< orphan*/  mpls_ttl; int /*<<< orphan*/  mpls_s_bos; int /*<<< orphan*/  mpls_exp; int /*<<< orphan*/  mpls_label; } ;
struct TYPE_6__ {int /*<<< orphan*/  mpls_ttl; int /*<<< orphan*/  mpls_s_bos; int /*<<< orphan*/  mpls_exp; int /*<<< orphan*/  mpls_label; } ;
struct TYPE_5__ {int /*<<< orphan*/  mpls_ttl; int /*<<< orphan*/  mpls_s_bos; int /*<<< orphan*/  mpls_exp; int /*<<< orphan*/  mpls_label; } ;

/* Variables and functions */
 void* MLX5_GET (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fte_match_set_misc2 ; 
 TYPE_4__ inner_first_mpls ; 
 int /*<<< orphan*/  metadata_reg_a ; 
 int /*<<< orphan*/  metadata_reg_b ; 
 int /*<<< orphan*/  metadata_reg_c_0 ; 
 int /*<<< orphan*/  metadata_reg_c_1 ; 
 int /*<<< orphan*/  metadata_reg_c_2 ; 
 int /*<<< orphan*/  metadata_reg_c_3 ; 
 int /*<<< orphan*/  metadata_reg_c_4 ; 
 int /*<<< orphan*/  metadata_reg_c_5 ; 
 int /*<<< orphan*/  metadata_reg_c_6 ; 
 int /*<<< orphan*/  metadata_reg_c_7 ; 
 TYPE_3__ outer_first_mpls ; 
 TYPE_2__ outer_first_mpls_over_gre ; 
 TYPE_1__ outer_first_mpls_over_udp ; 

__attribute__((used)) static void dr_ste_copy_mask_misc2(char *mask, struct mlx5dr_match_misc2 *spec)
{
	spec->outer_first_mpls_label =
		MLX5_GET(fte_match_set_misc2, mask, outer_first_mpls.mpls_label);
	spec->outer_first_mpls_exp =
		MLX5_GET(fte_match_set_misc2, mask, outer_first_mpls.mpls_exp);
	spec->outer_first_mpls_s_bos =
		MLX5_GET(fte_match_set_misc2, mask, outer_first_mpls.mpls_s_bos);
	spec->outer_first_mpls_ttl =
		MLX5_GET(fte_match_set_misc2, mask, outer_first_mpls.mpls_ttl);
	spec->inner_first_mpls_label =
		MLX5_GET(fte_match_set_misc2, mask, inner_first_mpls.mpls_label);
	spec->inner_first_mpls_exp =
		MLX5_GET(fte_match_set_misc2, mask, inner_first_mpls.mpls_exp);
	spec->inner_first_mpls_s_bos =
		MLX5_GET(fte_match_set_misc2, mask, inner_first_mpls.mpls_s_bos);
	spec->inner_first_mpls_ttl =
		MLX5_GET(fte_match_set_misc2, mask, inner_first_mpls.mpls_ttl);
	spec->outer_first_mpls_over_gre_label =
		MLX5_GET(fte_match_set_misc2, mask, outer_first_mpls_over_gre.mpls_label);
	spec->outer_first_mpls_over_gre_exp =
		MLX5_GET(fte_match_set_misc2, mask, outer_first_mpls_over_gre.mpls_exp);
	spec->outer_first_mpls_over_gre_s_bos =
		MLX5_GET(fte_match_set_misc2, mask, outer_first_mpls_over_gre.mpls_s_bos);
	spec->outer_first_mpls_over_gre_ttl =
		MLX5_GET(fte_match_set_misc2, mask, outer_first_mpls_over_gre.mpls_ttl);
	spec->outer_first_mpls_over_udp_label =
		MLX5_GET(fte_match_set_misc2, mask, outer_first_mpls_over_udp.mpls_label);
	spec->outer_first_mpls_over_udp_exp =
		MLX5_GET(fte_match_set_misc2, mask, outer_first_mpls_over_udp.mpls_exp);
	spec->outer_first_mpls_over_udp_s_bos =
		MLX5_GET(fte_match_set_misc2, mask, outer_first_mpls_over_udp.mpls_s_bos);
	spec->outer_first_mpls_over_udp_ttl =
		MLX5_GET(fte_match_set_misc2, mask, outer_first_mpls_over_udp.mpls_ttl);
	spec->metadata_reg_c_7 = MLX5_GET(fte_match_set_misc2, mask, metadata_reg_c_7);
	spec->metadata_reg_c_6 = MLX5_GET(fte_match_set_misc2, mask, metadata_reg_c_6);
	spec->metadata_reg_c_5 = MLX5_GET(fte_match_set_misc2, mask, metadata_reg_c_5);
	spec->metadata_reg_c_4 = MLX5_GET(fte_match_set_misc2, mask, metadata_reg_c_4);
	spec->metadata_reg_c_3 = MLX5_GET(fte_match_set_misc2, mask, metadata_reg_c_3);
	spec->metadata_reg_c_2 = MLX5_GET(fte_match_set_misc2, mask, metadata_reg_c_2);
	spec->metadata_reg_c_1 = MLX5_GET(fte_match_set_misc2, mask, metadata_reg_c_1);
	spec->metadata_reg_c_0 = MLX5_GET(fte_match_set_misc2, mask, metadata_reg_c_0);
	spec->metadata_reg_a = MLX5_GET(fte_match_set_misc2, mask, metadata_reg_a);
	spec->metadata_reg_b = MLX5_GET(fte_match_set_misc2, mask, metadata_reg_b);
}