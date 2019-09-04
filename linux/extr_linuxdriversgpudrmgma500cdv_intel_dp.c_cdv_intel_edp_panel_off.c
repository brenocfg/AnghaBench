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
struct cdv_intel_dp {int panel_on; int /*<<< orphan*/  panel_power_cycle_delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int EDP_BLC_ENABLE ; 
 int EDP_FORCE_VDD ; 
 int PANEL_UNLOCK_MASK ; 
 int POWER_TARGET_ON ; 
 int /*<<< orphan*/  PP_CONTROL ; 
 int PP_ON ; 
 int /*<<< orphan*/  PP_STATUS ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 scalar_t__ wait_for (int,int) ; 

__attribute__((used)) static void cdv_intel_edp_panel_off (struct gma_encoder *intel_encoder)
{
	struct drm_device *dev = intel_encoder->base.dev;
	u32 pp, idle_off_mask = PP_ON ;
	struct cdv_intel_dp *intel_dp = intel_encoder->dev_priv;

	DRM_DEBUG_KMS("\n");

	pp = REG_READ(PP_CONTROL);

	if ((pp & POWER_TARGET_ON) == 0) 
		return;

	intel_dp->panel_on = false;
	pp &= ~PANEL_UNLOCK_MASK;
	/* ILK workaround: disable reset around power sequence */

	pp &= ~POWER_TARGET_ON;
	pp &= ~EDP_FORCE_VDD;
	pp &= ~EDP_BLC_ENABLE;
	REG_WRITE(PP_CONTROL, pp);
	REG_READ(PP_CONTROL);
	DRM_DEBUG_KMS("PP_STATUS %x\n", REG_READ(PP_STATUS));

	if (wait_for((REG_READ(PP_STATUS) & idle_off_mask) == 0, 1000)) {
		DRM_DEBUG_KMS("Error in turning off Panel\n");	
	}

	msleep(intel_dp->panel_power_cycle_delay);
	DRM_DEBUG_KMS("Over\n");
}