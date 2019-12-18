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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int u32 ;
struct TYPE_2__ {struct drm_device* dev; } ;
struct gma_encoder {struct cdv_intel_dp* dev_priv; TYPE_1__ base; } ;
struct drm_device {int dummy; } ;
struct cdv_intel_dp {int DP; int* train_set; int lane_count; int /*<<< orphan*/ * link_status; int /*<<< orphan*/ * link_configuration; int /*<<< orphan*/  output_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_LINK_BW_SET ; 
 int DP_LINK_TRAIN_MASK ; 
 int DP_LINK_TRAIN_PAT_1 ; 
 int DP_PORT_EN ; 
 int /*<<< orphan*/  DP_TRAINING_PATTERN_1 ; 
 int DP_TRAIN_MAX_SWING_REACHED ; 
 int DP_TRAIN_VOLTAGE_SWING_MASK ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int /*<<< orphan*/  REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ cdv_intel_clock_recovery_ok (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cdv_intel_dp_aux_native_write (struct gma_encoder*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cdv_intel_dp_get_link_status (struct gma_encoder*) ; 
 int /*<<< orphan*/  cdv_intel_dp_set_link_train (struct gma_encoder*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdv_intel_dp_set_vswing_premph (struct gma_encoder*,int) ; 
 int /*<<< orphan*/  cdv_intel_dplink_set_level (struct gma_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdv_intel_get_adjust_train (struct gma_encoder*) ; 
 int /*<<< orphan*/  gma_wait_for_vblank (struct drm_device*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
cdv_intel_dp_start_link_train(struct gma_encoder *encoder)
{
	struct drm_device *dev = encoder->base.dev;
	struct cdv_intel_dp *intel_dp = encoder->dev_priv;
	int i;
	uint8_t voltage;
	bool clock_recovery = false;
	int tries;
	u32 reg;
	uint32_t DP = intel_dp->DP;

	DP |= DP_PORT_EN;
	DP &= ~DP_LINK_TRAIN_MASK;
		
	reg = DP;	
	reg |= DP_LINK_TRAIN_PAT_1;
	/* Enable output, wait for it to become active */
	REG_WRITE(intel_dp->output_reg, reg);
	REG_READ(intel_dp->output_reg);
	gma_wait_for_vblank(dev);

	DRM_DEBUG_KMS("Link config\n");
	/* Write the link configuration data */
	cdv_intel_dp_aux_native_write(encoder, DP_LINK_BW_SET,
				  intel_dp->link_configuration,
				  2);

	memset(intel_dp->train_set, 0, 4);
	voltage = 0;
	tries = 0;
	clock_recovery = false;

	DRM_DEBUG_KMS("Start train\n");
		reg = DP | DP_LINK_TRAIN_PAT_1;


	for (;;) {
		/* Use intel_dp->train_set[0] to set the voltage and pre emphasis values */
		DRM_DEBUG_KMS("DP Link Train Set %x, Link_config %x, %x\n",
				intel_dp->train_set[0],
				intel_dp->link_configuration[0],
				intel_dp->link_configuration[1]);

		if (!cdv_intel_dp_set_link_train(encoder, reg, DP_TRAINING_PATTERN_1)) {
			DRM_DEBUG_KMS("Failure in aux-transfer setting pattern 1\n");
		}
		cdv_intel_dp_set_vswing_premph(encoder, intel_dp->train_set[0]);
		/* Set training pattern 1 */

		cdv_intel_dplink_set_level(encoder, DP_TRAINING_PATTERN_1);

		udelay(200);
		if (!cdv_intel_dp_get_link_status(encoder))
			break;

		DRM_DEBUG_KMS("DP Link status %x, %x, %x, %x, %x, %x\n",
				intel_dp->link_status[0], intel_dp->link_status[1], intel_dp->link_status[2],
				intel_dp->link_status[3], intel_dp->link_status[4], intel_dp->link_status[5]);

		if (cdv_intel_clock_recovery_ok(intel_dp->link_status, intel_dp->lane_count)) {
			DRM_DEBUG_KMS("PT1 train is done\n");
			clock_recovery = true;
			break;
		}

		/* Check to see if we've tried the max voltage */
		for (i = 0; i < intel_dp->lane_count; i++)
			if ((intel_dp->train_set[i] & DP_TRAIN_MAX_SWING_REACHED) == 0)
				break;
		if (i == intel_dp->lane_count)
			break;

		/* Check to see if we've tried the same voltage 5 times */
		if ((intel_dp->train_set[0] & DP_TRAIN_VOLTAGE_SWING_MASK) == voltage) {
			++tries;
			if (tries == 5)
				break;
		} else
			tries = 0;
		voltage = intel_dp->train_set[0] & DP_TRAIN_VOLTAGE_SWING_MASK;

		/* Compute new intel_dp->train_set as requested by target */
		cdv_intel_get_adjust_train(encoder);

	}

	if (!clock_recovery) {
		DRM_DEBUG_KMS("failure in DP patter 1 training, train set %x\n", intel_dp->train_set[0]);
	}
	
	intel_dp->DP = DP;
}