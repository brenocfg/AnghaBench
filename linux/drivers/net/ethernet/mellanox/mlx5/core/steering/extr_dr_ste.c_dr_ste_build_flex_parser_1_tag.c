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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct mlx5dr_ste_build {TYPE_1__* caps; } ;
struct mlx5dr_match_misc3 {int icmpv4_header_data; int icmpv4_type; int icmpv4_code; int icmpv6_header_data; int icmpv6_type; int icmpv6_code; } ;
struct mlx5dr_match_param {struct mlx5dr_match_misc3 misc3; } ;
struct dr_hw_ste_format {int /*<<< orphan*/ * tag; } ;
struct TYPE_2__ {int flex_parser_id_icmp_dw0; int flex_parser_id_icmp_dw1; int flex_parser_id_icmpv6_dw0; int flex_parser_id_icmpv6_dw1; } ;

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

__attribute__((used)) static int dr_ste_build_flex_parser_1_tag(struct mlx5dr_match_param *value,
					  struct mlx5dr_ste_build *sb,
					  u8 *hw_ste_p)
{
	struct dr_hw_ste_format *hw_ste = (struct dr_hw_ste_format *)hw_ste_p;
	struct mlx5dr_match_misc3 *misc_3 = &value->misc3;
	u8 *tag = hw_ste->tag;
	u32 icmp_header_data;
	int dw0_location;
	int dw1_location;
	u32 icmp_type;
	u32 icmp_code;
	bool is_ipv4;

	is_ipv4 = DR_MASK_IS_FLEX_PARSER_ICMPV4_SET(misc_3);
	if (is_ipv4) {
		icmp_header_data	= misc_3->icmpv4_header_data;
		icmp_type		= misc_3->icmpv4_type;
		icmp_code		= misc_3->icmpv4_code;
		dw0_location		= sb->caps->flex_parser_id_icmp_dw0;
		dw1_location		= sb->caps->flex_parser_id_icmp_dw1;
	} else {
		icmp_header_data	= misc_3->icmpv6_header_data;
		icmp_type		= misc_3->icmpv6_type;
		icmp_code		= misc_3->icmpv6_code;
		dw0_location		= sb->caps->flex_parser_id_icmpv6_dw0;
		dw1_location		= sb->caps->flex_parser_id_icmpv6_dw1;
	}

	switch (dw0_location) {
	case 4:
		if (icmp_type) {
			MLX5_SET(ste_flex_parser_1, tag, flex_parser_4,
				 (icmp_type << ICMP_TYPE_OFFSET_FIRST_DW));
			if (is_ipv4)
				misc_3->icmpv4_type = 0;
			else
				misc_3->icmpv6_type = 0;
		}

		if (icmp_code) {
			u32 cur_val = MLX5_GET(ste_flex_parser_1, tag,
					       flex_parser_4);
			MLX5_SET(ste_flex_parser_1, tag, flex_parser_4,
				 cur_val | (icmp_code << ICMP_CODE_OFFSET_FIRST_DW));
			if (is_ipv4)
				misc_3->icmpv4_code = 0;
			else
				misc_3->icmpv6_code = 0;
		}
		break;
	default:
		return -EINVAL;
	}

	switch (dw1_location) {
	case 5:
		if (icmp_header_data) {
			MLX5_SET(ste_flex_parser_1, tag, flex_parser_5,
				 (icmp_header_data << ICMP_HEADER_DATA_OFFSET_SECOND_DW));
			if (is_ipv4)
				misc_3->icmpv4_header_data = 0;
			else
				misc_3->icmpv6_header_data = 0;
		}
		break;
	default:
		return -EINVAL;
	}

	return 0;
}