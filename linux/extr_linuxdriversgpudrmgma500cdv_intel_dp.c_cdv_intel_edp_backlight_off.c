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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {struct drm_device* dev; } ;
struct gma_encoder {struct cdv_intel_dp* dev_priv; TYPE_1__ base; } ;
struct drm_device {int dummy; } ;
struct cdv_intel_dp {int backlight_off_delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  EDP_BLC_ENABLE ; 
 int /*<<< orphan*/  PP_CONTROL ; 
 int /*<<< orphan*/  REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gma_backlight_disable (struct drm_device*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void cdv_intel_edp_backlight_off (struct gma_encoder *intel_encoder)
{
	struct drm_device *dev = intel_encoder->base.dev;
	struct cdv_intel_dp *intel_dp = intel_encoder->dev_priv;
	u32 pp;

	DRM_DEBUG_KMS("\n");
	gma_backlight_disable(dev);
	msleep(10);
	pp = REG_READ(PP_CONTROL);

	pp &= ~EDP_BLC_ENABLE;
	REG_WRITE(PP_CONTROL, pp);
	msleep(intel_dp->backlight_off_delay);
}