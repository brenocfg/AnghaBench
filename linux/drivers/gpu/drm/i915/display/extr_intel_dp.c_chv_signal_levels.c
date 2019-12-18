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
typedef  int u8 ;
typedef  int u32 ;
struct intel_encoder {int dummy; } ;
struct intel_dp {int* train_set; } ;
struct TYPE_2__ {struct intel_encoder base; } ;

/* Variables and functions */
 int DP_TRAIN_PRE_EMPHASIS_MASK ; 
#define  DP_TRAIN_PRE_EMPH_LEVEL_0 135 
#define  DP_TRAIN_PRE_EMPH_LEVEL_1 134 
#define  DP_TRAIN_PRE_EMPH_LEVEL_2 133 
#define  DP_TRAIN_PRE_EMPH_LEVEL_3 132 
#define  DP_TRAIN_VOLTAGE_SWING_LEVEL_0 131 
#define  DP_TRAIN_VOLTAGE_SWING_LEVEL_1 130 
#define  DP_TRAIN_VOLTAGE_SWING_LEVEL_2 129 
#define  DP_TRAIN_VOLTAGE_SWING_LEVEL_3 128 
 int DP_TRAIN_VOLTAGE_SWING_MASK ; 
 int /*<<< orphan*/  chv_set_phy_signal_level (struct intel_encoder*,int,int,int) ; 
 TYPE_1__* dp_to_dig_port (struct intel_dp*) ; 

__attribute__((used)) static u32 chv_signal_levels(struct intel_dp *intel_dp)
{
	struct intel_encoder *encoder = &dp_to_dig_port(intel_dp)->base;
	u32 deemph_reg_value, margin_reg_value;
	bool uniq_trans_scale = false;
	u8 train_set = intel_dp->train_set[0];

	switch (train_set & DP_TRAIN_PRE_EMPHASIS_MASK) {
	case DP_TRAIN_PRE_EMPH_LEVEL_0:
		switch (train_set & DP_TRAIN_VOLTAGE_SWING_MASK) {
		case DP_TRAIN_VOLTAGE_SWING_LEVEL_0:
			deemph_reg_value = 128;
			margin_reg_value = 52;
			break;
		case DP_TRAIN_VOLTAGE_SWING_LEVEL_1:
			deemph_reg_value = 128;
			margin_reg_value = 77;
			break;
		case DP_TRAIN_VOLTAGE_SWING_LEVEL_2:
			deemph_reg_value = 128;
			margin_reg_value = 102;
			break;
		case DP_TRAIN_VOLTAGE_SWING_LEVEL_3:
			deemph_reg_value = 128;
			margin_reg_value = 154;
			uniq_trans_scale = true;
			break;
		default:
			return 0;
		}
		break;
	case DP_TRAIN_PRE_EMPH_LEVEL_1:
		switch (train_set & DP_TRAIN_VOLTAGE_SWING_MASK) {
		case DP_TRAIN_VOLTAGE_SWING_LEVEL_0:
			deemph_reg_value = 85;
			margin_reg_value = 78;
			break;
		case DP_TRAIN_VOLTAGE_SWING_LEVEL_1:
			deemph_reg_value = 85;
			margin_reg_value = 116;
			break;
		case DP_TRAIN_VOLTAGE_SWING_LEVEL_2:
			deemph_reg_value = 85;
			margin_reg_value = 154;
			break;
		default:
			return 0;
		}
		break;
	case DP_TRAIN_PRE_EMPH_LEVEL_2:
		switch (train_set & DP_TRAIN_VOLTAGE_SWING_MASK) {
		case DP_TRAIN_VOLTAGE_SWING_LEVEL_0:
			deemph_reg_value = 64;
			margin_reg_value = 104;
			break;
		case DP_TRAIN_VOLTAGE_SWING_LEVEL_1:
			deemph_reg_value = 64;
			margin_reg_value = 154;
			break;
		default:
			return 0;
		}
		break;
	case DP_TRAIN_PRE_EMPH_LEVEL_3:
		switch (train_set & DP_TRAIN_VOLTAGE_SWING_MASK) {
		case DP_TRAIN_VOLTAGE_SWING_LEVEL_0:
			deemph_reg_value = 43;
			margin_reg_value = 154;
			break;
		default:
			return 0;
		}
		break;
	default:
		return 0;
	}

	chv_set_phy_signal_level(encoder, deemph_reg_value,
				 margin_reg_value, uniq_trans_scale);

	return 0;
}