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
struct dcn10_link_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPHY_LOAD_BS_COUNT ; 
 int /*<<< orphan*/  DPHY_RX_FAST_TRAINING_CAPABLE ; 
 int /*<<< orphan*/  DP_DPHY_BS_SR_SWAP_CNTL ; 
 int /*<<< orphan*/  DP_DPHY_FAST_TRAINING ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dcn10_link_encoder* TO_DCN10_LINK_ENC (struct link_encoder*) ; 

void dcn10_psr_program_dp_dphy_fast_training(struct link_encoder *enc,
			bool exit_link_training_required)
{
	struct dcn10_link_encoder *enc10 = TO_DCN10_LINK_ENC(enc);

	if (exit_link_training_required)
		REG_UPDATE(DP_DPHY_FAST_TRAINING,
				DPHY_RX_FAST_TRAINING_CAPABLE, 1);
	else {
		REG_UPDATE(DP_DPHY_FAST_TRAINING,
				DPHY_RX_FAST_TRAINING_CAPABLE, 0);
		/*In DCE 11, we are able to pre-program a Force SR register
		 * to be able to trigger SR symbol after 5 idle patterns
		 * transmitted. Upon PSR Exit, DMCU can trigger
		 * DPHY_LOAD_BS_COUNT_START = 1. Upon writing 1 to
		 * DPHY_LOAD_BS_COUNT_START and the internal counter
		 * reaches DPHY_LOAD_BS_COUNT, the next BS symbol will be
		 * replaced by SR symbol once.
		 */

		REG_UPDATE(DP_DPHY_BS_SR_SWAP_CNTL, DPHY_LOAD_BS_COUNT, 0x5);
	}
}