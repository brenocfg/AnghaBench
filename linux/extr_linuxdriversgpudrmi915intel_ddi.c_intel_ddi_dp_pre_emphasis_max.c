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
typedef  int u8 ;
struct intel_encoder {int dummy; } ;

/* Variables and functions */
 int DP_TRAIN_PRE_EMPH_LEVEL_0 ; 
 int DP_TRAIN_PRE_EMPH_LEVEL_1 ; 
 int DP_TRAIN_PRE_EMPH_LEVEL_2 ; 
 int DP_TRAIN_PRE_EMPH_LEVEL_3 ; 
#define  DP_TRAIN_VOLTAGE_SWING_LEVEL_0 131 
#define  DP_TRAIN_VOLTAGE_SWING_LEVEL_1 130 
#define  DP_TRAIN_VOLTAGE_SWING_LEVEL_2 129 
#define  DP_TRAIN_VOLTAGE_SWING_LEVEL_3 128 
 int DP_TRAIN_VOLTAGE_SWING_MASK ; 

u8 intel_ddi_dp_pre_emphasis_max(struct intel_encoder *encoder, u8 voltage_swing)
{
	switch (voltage_swing & DP_TRAIN_VOLTAGE_SWING_MASK) {
	case DP_TRAIN_VOLTAGE_SWING_LEVEL_0:
		return DP_TRAIN_PRE_EMPH_LEVEL_3;
	case DP_TRAIN_VOLTAGE_SWING_LEVEL_1:
		return DP_TRAIN_PRE_EMPH_LEVEL_2;
	case DP_TRAIN_VOLTAGE_SWING_LEVEL_2:
		return DP_TRAIN_PRE_EMPH_LEVEL_1;
	case DP_TRAIN_VOLTAGE_SWING_LEVEL_3:
	default:
		return DP_TRAIN_PRE_EMPH_LEVEL_0;
	}
}