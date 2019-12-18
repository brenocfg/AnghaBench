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
typedef  int /*<<< orphan*/  u8 ;
struct psb_intel_sdvo {int dummy; } ;
typedef  int /*<<< orphan*/  state ;

/* Variables and functions */
#define  DRM_MODE_DPMS_OFF 131 
#define  DRM_MODE_DPMS_ON 130 
#define  DRM_MODE_DPMS_STANDBY 129 
#define  DRM_MODE_DPMS_SUSPEND 128 
 int /*<<< orphan*/  SDVO_CMD_SET_ENCODER_POWER_STATE ; 
 int /*<<< orphan*/  SDVO_ENCODER_STATE_OFF ; 
 int /*<<< orphan*/  SDVO_ENCODER_STATE_ON ; 
 int /*<<< orphan*/  SDVO_ENCODER_STATE_STANDBY ; 
 int /*<<< orphan*/  SDVO_ENCODER_STATE_SUSPEND ; 
 int psb_intel_sdvo_set_value (struct psb_intel_sdvo*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool psb_intel_sdvo_set_encoder_power_state(struct psb_intel_sdvo *psb_intel_sdvo,
					       int mode)
{
	u8 state = SDVO_ENCODER_STATE_ON;

	switch (mode) {
	case DRM_MODE_DPMS_ON:
		state = SDVO_ENCODER_STATE_ON;
		break;
	case DRM_MODE_DPMS_STANDBY:
		state = SDVO_ENCODER_STATE_STANDBY;
		break;
	case DRM_MODE_DPMS_SUSPEND:
		state = SDVO_ENCODER_STATE_SUSPEND;
		break;
	case DRM_MODE_DPMS_OFF:
		state = SDVO_ENCODER_STATE_OFF;
		break;
	}

	return psb_intel_sdvo_set_value(psb_intel_sdvo,
				    SDVO_CMD_SET_ENCODER_POWER_STATE, &state, sizeof(state));
}