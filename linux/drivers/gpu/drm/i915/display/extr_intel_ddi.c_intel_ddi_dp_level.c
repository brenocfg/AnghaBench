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
typedef  int /*<<< orphan*/  u32 ;
struct intel_dp {int* train_set; } ;

/* Variables and functions */
 int DP_TRAIN_PRE_EMPHASIS_MASK ; 
 int DP_TRAIN_VOLTAGE_SWING_MASK ; 
 int /*<<< orphan*/  translate_signal_level (int) ; 

__attribute__((used)) static u32 intel_ddi_dp_level(struct intel_dp *intel_dp)
{
	u8 train_set = intel_dp->train_set[0];
	int signal_levels = train_set & (DP_TRAIN_VOLTAGE_SWING_MASK |
					 DP_TRAIN_PRE_EMPHASIS_MASK);

	return translate_signal_level(signal_levels);
}