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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct psb_intel_sdvo {int /*<<< orphan*/  attached_output; int /*<<< orphan*/  sdvo_reg; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
#define  DRM_MODE_DPMS_OFF 129 
#define  DRM_MODE_DPMS_ON 128 
 scalar_t__ IS_MRST (struct drm_device*) ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int REG_READ_AUX (int /*<<< orphan*/ ) ; 
 scalar_t__ SDVO_CMD_STATUS_SUCCESS ; 
 int SDVO_ENABLE ; 
 int /*<<< orphan*/  SDVO_NAME (struct psb_intel_sdvo*) ; 
 int /*<<< orphan*/  gma_wait_for_vblank (struct drm_device*) ; 
 scalar_t__ psb_intel_sdvo_get_trained_inputs (struct psb_intel_sdvo*,int*,int*) ; 
 int /*<<< orphan*/  psb_intel_sdvo_set_active_outputs (struct psb_intel_sdvo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psb_intel_sdvo_set_encoder_power_state (struct psb_intel_sdvo*,int) ; 
 int /*<<< orphan*/  psb_intel_sdvo_write_sdvox (struct psb_intel_sdvo*,int) ; 
 struct psb_intel_sdvo* to_psb_intel_sdvo (struct drm_encoder*) ; 

__attribute__((used)) static void psb_intel_sdvo_dpms(struct drm_encoder *encoder, int mode)
{
	struct drm_device *dev = encoder->dev;
	struct psb_intel_sdvo *psb_intel_sdvo = to_psb_intel_sdvo(encoder);
	u32 temp;
	int i;
	int need_aux = IS_MRST(dev) ? 1 : 0;

	switch (mode) {
	case DRM_MODE_DPMS_ON:
		DRM_DEBUG("DPMS_ON");
		break;
	case DRM_MODE_DPMS_OFF:
		DRM_DEBUG("DPMS_OFF");
		break;
	default:
		DRM_DEBUG("DPMS: %d", mode);
	}

	if (mode != DRM_MODE_DPMS_ON) {
		psb_intel_sdvo_set_active_outputs(psb_intel_sdvo, 0);
		if (0)
			psb_intel_sdvo_set_encoder_power_state(psb_intel_sdvo, mode);

		if (mode == DRM_MODE_DPMS_OFF) {
			if (need_aux)
				temp = REG_READ_AUX(psb_intel_sdvo->sdvo_reg);
			else
				temp = REG_READ(psb_intel_sdvo->sdvo_reg);

			if ((temp & SDVO_ENABLE) != 0) {
				psb_intel_sdvo_write_sdvox(psb_intel_sdvo, temp & ~SDVO_ENABLE);
			}
		}
	} else {
		bool input1, input2;
		u8 status;

		if (need_aux)
			temp = REG_READ_AUX(psb_intel_sdvo->sdvo_reg);
		else
			temp = REG_READ(psb_intel_sdvo->sdvo_reg);

		if ((temp & SDVO_ENABLE) == 0)
			psb_intel_sdvo_write_sdvox(psb_intel_sdvo, temp | SDVO_ENABLE);

		for (i = 0; i < 2; i++)
			gma_wait_for_vblank(dev);

		status = psb_intel_sdvo_get_trained_inputs(psb_intel_sdvo, &input1, &input2);
		/* Warn if the device reported failure to sync.
		 * A lot of SDVO devices fail to notify of sync, but it's
		 * a given it the status is a success, we succeeded.
		 */
		if (status == SDVO_CMD_STATUS_SUCCESS && !input1) {
			DRM_DEBUG_KMS("First %s output reported failure to "
					"sync\n", SDVO_NAME(psb_intel_sdvo));
		}

		if (0)
			psb_intel_sdvo_set_encoder_power_state(psb_intel_sdvo, mode);
		psb_intel_sdvo_set_active_outputs(psb_intel_sdvo, psb_intel_sdvo->attached_output);
	}
	return;
}