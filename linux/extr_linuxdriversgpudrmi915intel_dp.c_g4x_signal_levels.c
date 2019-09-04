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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_PRE_EMPHASIS_0 ; 
 int /*<<< orphan*/  DP_PRE_EMPHASIS_3_5 ; 
 int /*<<< orphan*/  DP_PRE_EMPHASIS_6 ; 
 int /*<<< orphan*/  DP_PRE_EMPHASIS_9_5 ; 
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
 int /*<<< orphan*/  DP_VOLTAGE_0_4 ; 
 int /*<<< orphan*/  DP_VOLTAGE_0_6 ; 
 int /*<<< orphan*/  DP_VOLTAGE_0_8 ; 
 int /*<<< orphan*/  DP_VOLTAGE_1_2 ; 

__attribute__((used)) static uint32_t
g4x_signal_levels(uint8_t train_set)
{
	uint32_t	signal_levels = 0;

	switch (train_set & DP_TRAIN_VOLTAGE_SWING_MASK) {
	case DP_TRAIN_VOLTAGE_SWING_LEVEL_0:
	default:
		signal_levels |= DP_VOLTAGE_0_4;
		break;
	case DP_TRAIN_VOLTAGE_SWING_LEVEL_1:
		signal_levels |= DP_VOLTAGE_0_6;
		break;
	case DP_TRAIN_VOLTAGE_SWING_LEVEL_2:
		signal_levels |= DP_VOLTAGE_0_8;
		break;
	case DP_TRAIN_VOLTAGE_SWING_LEVEL_3:
		signal_levels |= DP_VOLTAGE_1_2;
		break;
	}
	switch (train_set & DP_TRAIN_PRE_EMPHASIS_MASK) {
	case DP_TRAIN_PRE_EMPH_LEVEL_0:
	default:
		signal_levels |= DP_PRE_EMPHASIS_0;
		break;
	case DP_TRAIN_PRE_EMPH_LEVEL_1:
		signal_levels |= DP_PRE_EMPHASIS_3_5;
		break;
	case DP_TRAIN_PRE_EMPH_LEVEL_2:
		signal_levels |= DP_PRE_EMPHASIS_6;
		break;
	case DP_TRAIN_PRE_EMPH_LEVEL_3:
		signal_levels |= DP_PRE_EMPHASIS_9_5;
		break;
	}
	return signal_levels;
}