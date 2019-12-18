#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlx5dr_ste_build {int rx; int inner; int /*<<< orphan*/ * ste_build_tag_func; int /*<<< orphan*/  bit_mask; int /*<<< orphan*/  byte_mask; int /*<<< orphan*/  lu_type; struct mlx5dr_domain* dmn; int /*<<< orphan*/  vhca_id_valid; } ;
struct TYPE_2__ {int /*<<< orphan*/  source_eswitch_owner_vhca_id; } ;
struct mlx5dr_match_param {TYPE_1__ misc; } ;
struct mlx5dr_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5DR_STE_LU_TYPE_SRC_GVMI_AND_QP ; 
 int dr_ste_build_src_gvmi_qpn_bit_mask (struct mlx5dr_match_param*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dr_ste_build_src_gvmi_qpn_tag ; 
 int /*<<< orphan*/  dr_ste_conv_bit_to_byte_mask (int /*<<< orphan*/ ) ; 

int mlx5dr_ste_build_src_gvmi_qpn(struct mlx5dr_ste_build *sb,
				  struct mlx5dr_match_param *mask,
				  struct mlx5dr_domain *dmn,
				  bool inner, bool rx)
{
	int ret;

	/* Set vhca_id_valid before we reset source_eswitch_owner_vhca_id */
	sb->vhca_id_valid = mask->misc.source_eswitch_owner_vhca_id;

	ret = dr_ste_build_src_gvmi_qpn_bit_mask(mask, sb->bit_mask);
	if (ret)
		return ret;

	sb->rx = rx;
	sb->dmn = dmn;
	sb->inner = inner;
	sb->lu_type = MLX5DR_STE_LU_TYPE_SRC_GVMI_AND_QP;
	sb->byte_mask = dr_ste_conv_bit_to_byte_mask(sb->bit_mask);
	sb->ste_build_tag_func = &dr_ste_build_src_gvmi_qpn_tag;

	return 0;
}