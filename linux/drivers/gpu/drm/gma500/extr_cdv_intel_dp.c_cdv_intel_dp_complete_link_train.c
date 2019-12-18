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
typedef  int uint32_t ;
typedef  int u32 ;
struct TYPE_2__ {struct drm_device* dev; } ;
struct gma_encoder {struct cdv_intel_dp* dev_priv; TYPE_1__ base; } ;
struct drm_device {int dummy; } ;
struct cdv_intel_dp {int DP; int /*<<< orphan*/  output_reg; int /*<<< orphan*/  lane_count; int /*<<< orphan*/ * link_status; int /*<<< orphan*/ * train_set; int /*<<< orphan*/ * link_configuration; } ;

/* Variables and functions */
 int DP_LINK_TRAIN_OFF ; 
 int DP_LINK_TRAIN_PAT_2 ; 
 int /*<<< orphan*/  DP_TRAINING_PATTERN_2 ; 
 int /*<<< orphan*/  DP_TRAINING_PATTERN_DISABLE ; 
 int /*<<< orphan*/  DP_TRAINING_PATTERN_SET ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ cdv_intel_channel_eq_ok (struct gma_encoder*) ; 
 int /*<<< orphan*/  cdv_intel_clock_recovery_ok (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdv_intel_dp_aux_native_write_1 (struct gma_encoder*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdv_intel_dp_get_link_status (struct gma_encoder*) ; 
 int /*<<< orphan*/  cdv_intel_dp_link_down (struct gma_encoder*) ; 
 int /*<<< orphan*/  cdv_intel_dp_set_link_train (struct gma_encoder*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdv_intel_dp_set_vswing_premph (struct gma_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdv_intel_dp_start_link_train (struct gma_encoder*) ; 
 int /*<<< orphan*/  cdv_intel_dplink_set_level (struct gma_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdv_intel_get_adjust_train (struct gma_encoder*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
cdv_intel_dp_complete_link_train(struct gma_encoder *encoder)
{
	struct drm_device *dev = encoder->base.dev;
	struct cdv_intel_dp *intel_dp = encoder->dev_priv;
	bool channel_eq = false;
	int tries, cr_tries;
	u32 reg;
	uint32_t DP = intel_dp->DP;

	/* channel equalization */
	tries = 0;
	cr_tries = 0;
	channel_eq = false;

	DRM_DEBUG_KMS("\n");
		reg = DP | DP_LINK_TRAIN_PAT_2;

	for (;;) {

		DRM_DEBUG_KMS("DP Link Train Set %x, Link_config %x, %x\n",
				intel_dp->train_set[0],
				intel_dp->link_configuration[0],
				intel_dp->link_configuration[1]);
        	/* channel eq pattern */

		if (!cdv_intel_dp_set_link_train(encoder, reg,
					     DP_TRAINING_PATTERN_2)) {
			DRM_DEBUG_KMS("Failure in aux-transfer setting pattern 2\n");
		}
		/* Use intel_dp->train_set[0] to set the voltage and pre emphasis values */

		if (cr_tries > 5) {
			DRM_ERROR("failed to train DP, aborting\n");
			cdv_intel_dp_link_down(encoder);
			break;
		}

		cdv_intel_dp_set_vswing_premph(encoder, intel_dp->train_set[0]);

		cdv_intel_dplink_set_level(encoder, DP_TRAINING_PATTERN_2);

		udelay(1000);
		if (!cdv_intel_dp_get_link_status(encoder))
			break;

		DRM_DEBUG_KMS("DP Link status %x, %x, %x, %x, %x, %x\n",
				intel_dp->link_status[0], intel_dp->link_status[1], intel_dp->link_status[2],
				intel_dp->link_status[3], intel_dp->link_status[4], intel_dp->link_status[5]);

		/* Make sure clock is still ok */
		if (!cdv_intel_clock_recovery_ok(intel_dp->link_status, intel_dp->lane_count)) {
			cdv_intel_dp_start_link_train(encoder);
			cr_tries++;
			continue;
		}

		if (cdv_intel_channel_eq_ok(encoder)) {
			DRM_DEBUG_KMS("PT2 train is done\n");
			channel_eq = true;
			break;
		}

		/* Try 5 times, then try clock recovery if that fails */
		if (tries > 5) {
			cdv_intel_dp_link_down(encoder);
			cdv_intel_dp_start_link_train(encoder);
			tries = 0;
			cr_tries++;
			continue;
		}

		/* Compute new intel_dp->train_set as requested by target */
		cdv_intel_get_adjust_train(encoder);
		++tries;

	}

	reg = DP | DP_LINK_TRAIN_OFF;

	REG_WRITE(intel_dp->output_reg, reg);
	REG_READ(intel_dp->output_reg);
	cdv_intel_dp_aux_native_write_1(encoder,
				    DP_TRAINING_PATTERN_SET, DP_TRAINING_PATTERN_DISABLE);
}