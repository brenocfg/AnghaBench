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
struct amdgpu_atombios_dp_link_train_info {int /*<<< orphan*/  aux; int /*<<< orphan*/  encoder; } ;

/* Variables and functions */
 int ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN1 ; 
 int ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN2 ; 
 int ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN3 ; 
#define  DP_TRAINING_PATTERN_1 130 
#define  DP_TRAINING_PATTERN_2 129 
#define  DP_TRAINING_PATTERN_3 128 
 int /*<<< orphan*/  DP_TRAINING_PATTERN_SET ; 
 int /*<<< orphan*/  amdgpu_atombios_encoder_setup_dig_encoder (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dp_dpcd_writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
amdgpu_atombios_dp_set_tp(struct amdgpu_atombios_dp_link_train_info *dp_info, int tp)
{
	int rtp = 0;

	/* set training pattern on the source */
	switch (tp) {
	case DP_TRAINING_PATTERN_1:
		rtp = ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN1;
		break;
	case DP_TRAINING_PATTERN_2:
		rtp = ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN2;
		break;
	case DP_TRAINING_PATTERN_3:
		rtp = ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN3;
			break;
	}
	amdgpu_atombios_encoder_setup_dig_encoder(dp_info->encoder, rtp, 0);

	/* enable training pattern on the sink */
	drm_dp_dpcd_writeb(dp_info->aux, DP_TRAINING_PATTERN_SET, tp);
}