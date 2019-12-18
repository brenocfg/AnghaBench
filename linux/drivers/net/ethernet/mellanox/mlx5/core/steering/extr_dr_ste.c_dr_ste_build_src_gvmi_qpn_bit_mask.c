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
struct mlx5dr_match_misc {int source_port; int source_eswitch_owner_vhca_id; } ;
struct mlx5dr_match_param {struct mlx5dr_match_misc misc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DR_STE_SET_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mlx5dr_match_misc*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  source_gvmi ; 
 int /*<<< orphan*/  source_port ; 
 int /*<<< orphan*/  source_qp ; 
 int /*<<< orphan*/  source_sqn ; 
 int /*<<< orphan*/  src_gvmi_qp ; 

__attribute__((used)) static int dr_ste_build_src_gvmi_qpn_bit_mask(struct mlx5dr_match_param *value,
					      u8 *bit_mask)
{
	struct mlx5dr_match_misc *misc_mask = &value->misc;

	/* Partial misc source_port is not supported */
	if (misc_mask->source_port && misc_mask->source_port != 0xffff)
		return -EINVAL;

	/* Partial misc source_eswitch_owner_vhca_id is not supported */
	if (misc_mask->source_eswitch_owner_vhca_id &&
	    misc_mask->source_eswitch_owner_vhca_id != 0xffff)
		return -EINVAL;

	DR_STE_SET_MASK(src_gvmi_qp, bit_mask, source_gvmi, misc_mask, source_port);
	DR_STE_SET_MASK(src_gvmi_qp, bit_mask, source_qp, misc_mask, source_sqn);
	misc_mask->source_eswitch_owner_vhca_id = 0;

	return 0;
}