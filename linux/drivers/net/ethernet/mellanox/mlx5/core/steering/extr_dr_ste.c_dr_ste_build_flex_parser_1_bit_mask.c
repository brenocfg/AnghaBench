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
typedef  int u32 ;
struct mlx5dr_match_misc3 {int icmpv4_header_data; int icmpv4_type; int icmpv4_code; int icmpv6_header_data; int icmpv6_type; int icmpv6_code; } ;
struct mlx5dr_match_param {struct mlx5dr_match_misc3 misc3; } ;
struct mlx5dr_cmd_caps {int flex_parser_id_icmp_dw0; int flex_parser_id_icmp_dw1; int flex_parser_id_icmpv6_dw0; int flex_parser_id_icmpv6_dw1; } ;

/* Variables and functions */
 int DR_MASK_IS_FLEX_PARSER_ICMPV4_SET (struct mlx5dr_match_misc3*) ; 
 int EINVAL ; 
 int ICMP_CODE_OFFSET_FIRST_DW ; 
 int ICMP_HEADER_DATA_OFFSET_SECOND_DW ; 
 int ICMP_TYPE_OFFSET_FIRST_DW ; 
 int MLX5_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  flex_parser_4 ; 
 int /*<<< orphan*/  flex_parser_5 ; 
 int /*<<< orphan*/  ste_flex_parser_1 ; 

__attribute__((used)) static int dr_ste_build_flex_parser_1_bit_mask(struct mlx5dr_match_param *mask,
					       struct mlx5dr_cmd_caps *caps,
					       u8 *bit_mask)
{
	struct mlx5dr_match_misc3 *misc_3_mask = &mask->misc3;
	bool is_ipv4_mask = DR_MASK_IS_FLEX_PARSER_ICMPV4_SET(misc_3_mask);
	u32 icmp_header_data_mask;
	u32 icmp_type_mask;
	u32 icmp_code_mask;
	int dw0_location;
	int dw1_location;

	if (is_ipv4_mask) {
		icmp_header_data_mask	= misc_3_mask->icmpv4_header_data;
		icmp_type_mask		= misc_3_mask->icmpv4_type;
		icmp_code_mask		= misc_3_mask->icmpv4_code;
		dw0_location		= caps->flex_parser_id_icmp_dw0;
		dw1_location		= caps->flex_parser_id_icmp_dw1;
	} else {
		icmp_header_data_mask	= misc_3_mask->icmpv6_header_data;
		icmp_type_mask		= misc_3_mask->icmpv6_type;
		icmp_code_mask		= misc_3_mask->icmpv6_code;
		dw0_location		= caps->flex_parser_id_icmpv6_dw0;
		dw1_location		= caps->flex_parser_id_icmpv6_dw1;
	}

	switch (dw0_location) {
	case 4:
		if (icmp_type_mask) {
			MLX5_SET(ste_flex_parser_1, bit_mask, flex_parser_4,
				 (icmp_type_mask << ICMP_TYPE_OFFSET_FIRST_DW));
			if (is_ipv4_mask)
				misc_3_mask->icmpv4_type = 0;
			else
				misc_3_mask->icmpv6_type = 0;
		}
		if (icmp_code_mask) {
			u32 cur_val = MLX5_GET(ste_flex_parser_1, bit_mask,
					       flex_parser_4);
			MLX5_SET(ste_flex_parser_1, bit_mask, flex_parser_4,
				 cur_val | (icmp_code_mask << ICMP_CODE_OFFSET_FIRST_DW));
			if (is_ipv4_mask)
				misc_3_mask->icmpv4_code = 0;
			else
				misc_3_mask->icmpv6_code = 0;
		}
		break;
	default:
		return -EINVAL;
	}

	switch (dw1_location) {
	case 5:
		if (icmp_header_data_mask) {
			MLX5_SET(ste_flex_parser_1, bit_mask, flex_parser_5,
				 (icmp_header_data_mask << ICMP_HEADER_DATA_OFFSET_SECOND_DW));
			if (is_ipv4_mask)
				misc_3_mask->icmpv4_header_data = 0;
			else
				misc_3_mask->icmpv6_header_data = 0;
		}
		break;
	default:
		return -EINVAL;
	}

	return 0;
}