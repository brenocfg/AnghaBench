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
typedef  int u32 ;
struct TYPE_2__ {struct drm_device* dev; } ;
struct gma_encoder {struct cdv_intel_dp* dev_priv; TYPE_1__ base; } ;
struct drm_device {int dummy; } ;
struct cdv_intel_dp {int panel_on; int /*<<< orphan*/  panel_power_up_delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int PANEL_UNLOCK_MASK ; 
 int PANEL_UNLOCK_REGS ; 
 int POWER_TARGET_ON ; 
 int /*<<< orphan*/  PP_CONTROL ; 
 int PP_ON ; 
 int PP_SEQUENCE_NONE ; 
 int /*<<< orphan*/  PP_STATUS ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 scalar_t__ wait_for (int,int) ; 

__attribute__((used)) static bool cdv_intel_edp_panel_on(struct gma_encoder *intel_encoder)
{
	struct drm_device *dev = intel_encoder->base.dev;
	struct cdv_intel_dp *intel_dp = intel_encoder->dev_priv;
	u32 pp, idle_on_mask = PP_ON | PP_SEQUENCE_NONE;

	if (intel_dp->panel_on)
		return true;

	DRM_DEBUG_KMS("\n");
	pp = REG_READ(PP_CONTROL);
	pp &= ~PANEL_UNLOCK_MASK;

	pp |= (PANEL_UNLOCK_REGS | POWER_TARGET_ON);
	REG_WRITE(PP_CONTROL, pp);
	REG_READ(PP_CONTROL);

	if (wait_for(((REG_READ(PP_STATUS) & idle_on_mask) == idle_on_mask), 1000)) {
		DRM_DEBUG_KMS("Error in Powering up eDP panel, status %x\n", REG_READ(PP_STATUS));
		intel_dp->panel_on = false;
	} else
		intel_dp->panel_on = true;	
	msleep(intel_dp->panel_power_up_delay);

	return false;
}