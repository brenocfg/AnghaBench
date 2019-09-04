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
struct intel_vgpu_dpcd_data {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPCD_INTERLANE_ALIGN_DONE ; 
 size_t DPCD_LANE0_1_STATUS ; 
 size_t DPCD_LANE2_3_STATUS ; 
 int /*<<< orphan*/  DPCD_LANES_CR_DONE ; 
 int /*<<< orphan*/  DPCD_LANES_EQ_DONE ; 
 size_t DPCD_LANE_ALIGN_STATUS_UPDATED ; 
 int DPCD_LINK_TRAINING_DISABLED ; 
 int /*<<< orphan*/  DPCD_SINK_IN_SYNC ; 
 size_t DPCD_SINK_STATUS ; 
 int /*<<< orphan*/  DPCD_SYMBOL_LOCKED ; 
 int DPCD_TRAINING_PATTERN_1 ; 
 int DPCD_TRAINING_PATTERN_2 ; 
 int DPCD_TRAINING_PATTERN_SET_MASK ; 

__attribute__((used)) static void dp_aux_ch_ctl_link_training(struct intel_vgpu_dpcd_data *dpcd,
		uint8_t t)
{
	if ((t & DPCD_TRAINING_PATTERN_SET_MASK) == DPCD_TRAINING_PATTERN_1) {
		/* training pattern 1 for CR */
		/* set LANE0_CR_DONE, LANE1_CR_DONE */
		dpcd->data[DPCD_LANE0_1_STATUS] |= DPCD_LANES_CR_DONE;
		/* set LANE2_CR_DONE, LANE3_CR_DONE */
		dpcd->data[DPCD_LANE2_3_STATUS] |= DPCD_LANES_CR_DONE;
	} else if ((t & DPCD_TRAINING_PATTERN_SET_MASK) ==
			DPCD_TRAINING_PATTERN_2) {
		/* training pattern 2 for EQ */
		/* Set CHANNEL_EQ_DONE and  SYMBOL_LOCKED for Lane0_1 */
		dpcd->data[DPCD_LANE0_1_STATUS] |= DPCD_LANES_EQ_DONE;
		dpcd->data[DPCD_LANE0_1_STATUS] |= DPCD_SYMBOL_LOCKED;
		/* Set CHANNEL_EQ_DONE and  SYMBOL_LOCKED for Lane2_3 */
		dpcd->data[DPCD_LANE2_3_STATUS] |= DPCD_LANES_EQ_DONE;
		dpcd->data[DPCD_LANE2_3_STATUS] |= DPCD_SYMBOL_LOCKED;
		/* set INTERLANE_ALIGN_DONE */
		dpcd->data[DPCD_LANE_ALIGN_STATUS_UPDATED] |=
			DPCD_INTERLANE_ALIGN_DONE;
	} else if ((t & DPCD_TRAINING_PATTERN_SET_MASK) ==
			DPCD_LINK_TRAINING_DISABLED) {
		/* finish link training */
		/* set sink status as synchronized */
		dpcd->data[DPCD_SINK_STATUS] = DPCD_SINK_IN_SYNC;
	}
}