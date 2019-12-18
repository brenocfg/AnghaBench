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
struct link_encoder {int dummy; } ;
struct encoder_set_dp_phy_pattern_param {int dp_phy_pattern; int /*<<< orphan*/  dp_panel_mode; int /*<<< orphan*/  custom_pattern; } ;
struct dcn10_link_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_CRITICAL (int) ; 
#define  DP_TEST_PATTERN_80BIT_CUSTOM 139 
#define  DP_TEST_PATTERN_CP2520_1 138 
#define  DP_TEST_PATTERN_CP2520_2 137 
#define  DP_TEST_PATTERN_CP2520_3 136 
#define  DP_TEST_PATTERN_D102 135 
#define  DP_TEST_PATTERN_PRBS7 134 
#define  DP_TEST_PATTERN_SYMBOL_ERROR 133 
#define  DP_TEST_PATTERN_TRAINING_PATTERN1 132 
#define  DP_TEST_PATTERN_TRAINING_PATTERN2 131 
#define  DP_TEST_PATTERN_TRAINING_PATTERN3 130 
#define  DP_TEST_PATTERN_TRAINING_PATTERN4 129 
#define  DP_TEST_PATTERN_VIDEO_MODE 128 
 struct dcn10_link_encoder* TO_DCN10_LINK_ENC (struct link_encoder*) ; 
 int /*<<< orphan*/  dcn10_link_encoder_set_dp_phy_pattern_training_pattern (struct link_encoder*,int) ; 
 int /*<<< orphan*/  set_dp_phy_pattern_80bit_custom (struct dcn10_link_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dp_phy_pattern_d102 (struct dcn10_link_encoder*) ; 
 int /*<<< orphan*/  set_dp_phy_pattern_hbr2_compliance_cp2520_2 (struct dcn10_link_encoder*,int) ; 
 int /*<<< orphan*/  set_dp_phy_pattern_passthrough_mode (struct dcn10_link_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dp_phy_pattern_prbs7 (struct dcn10_link_encoder*) ; 
 int /*<<< orphan*/  set_dp_phy_pattern_symbol_error (struct dcn10_link_encoder*) ; 

void dcn10_link_encoder_dp_set_phy_pattern(
	struct link_encoder *enc,
	const struct encoder_set_dp_phy_pattern_param *param)
{
	struct dcn10_link_encoder *enc10 = TO_DCN10_LINK_ENC(enc);

	switch (param->dp_phy_pattern) {
	case DP_TEST_PATTERN_TRAINING_PATTERN1:
		dcn10_link_encoder_set_dp_phy_pattern_training_pattern(enc, 0);
		break;
	case DP_TEST_PATTERN_TRAINING_PATTERN2:
		dcn10_link_encoder_set_dp_phy_pattern_training_pattern(enc, 1);
		break;
	case DP_TEST_PATTERN_TRAINING_PATTERN3:
		dcn10_link_encoder_set_dp_phy_pattern_training_pattern(enc, 2);
		break;
	case DP_TEST_PATTERN_TRAINING_PATTERN4:
		dcn10_link_encoder_set_dp_phy_pattern_training_pattern(enc, 3);
		break;
	case DP_TEST_PATTERN_D102:
		set_dp_phy_pattern_d102(enc10);
		break;
	case DP_TEST_PATTERN_SYMBOL_ERROR:
		set_dp_phy_pattern_symbol_error(enc10);
		break;
	case DP_TEST_PATTERN_PRBS7:
		set_dp_phy_pattern_prbs7(enc10);
		break;
	case DP_TEST_PATTERN_80BIT_CUSTOM:
		set_dp_phy_pattern_80bit_custom(
			enc10, param->custom_pattern);
		break;
	case DP_TEST_PATTERN_CP2520_1:
		set_dp_phy_pattern_hbr2_compliance_cp2520_2(enc10, 1);
		break;
	case DP_TEST_PATTERN_CP2520_2:
		set_dp_phy_pattern_hbr2_compliance_cp2520_2(enc10, 2);
		break;
	case DP_TEST_PATTERN_CP2520_3:
		set_dp_phy_pattern_hbr2_compliance_cp2520_2(enc10, 3);
		break;
	case DP_TEST_PATTERN_VIDEO_MODE: {
		set_dp_phy_pattern_passthrough_mode(
			enc10, param->dp_panel_mode);
		break;
	}

	default:
		/* invalid phy pattern */
		ASSERT_CRITICAL(false);
		break;
	}
}