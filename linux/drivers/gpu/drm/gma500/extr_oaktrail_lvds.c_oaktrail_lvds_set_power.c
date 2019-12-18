#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct gma_encoder {int dummy; } ;
struct drm_psb_private {int is_lvds_on; TYPE_1__* ops; } ;
struct drm_device {TYPE_2__* pdev; struct drm_psb_private* dev_private; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* lvds_bl_power ) (struct drm_device*,int) ;} ;

/* Variables and functions */
 int POWER_TARGET_ON ; 
 int /*<<< orphan*/  PP_CONTROL ; 
 int PP_ON ; 
 int PP_READY ; 
 int /*<<< orphan*/  PP_STATUS ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gma_power_begin (struct drm_device*,int) ; 
 int /*<<< orphan*/  gma_power_end (struct drm_device*) ; 
 int /*<<< orphan*/  pm_request_idle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct drm_device*,int) ; 
 int /*<<< orphan*/  stub2 (struct drm_device*,int) ; 

__attribute__((used)) static void oaktrail_lvds_set_power(struct drm_device *dev,
				struct gma_encoder *gma_encoder,
				bool on)
{
	u32 pp_status;
	struct drm_psb_private *dev_priv = dev->dev_private;

	if (!gma_power_begin(dev, true))
		return;

	if (on) {
		REG_WRITE(PP_CONTROL, REG_READ(PP_CONTROL) |
			  POWER_TARGET_ON);
		do {
			pp_status = REG_READ(PP_STATUS);
		} while ((pp_status & (PP_ON | PP_READY)) == PP_READY);
		dev_priv->is_lvds_on = true;
		if (dev_priv->ops->lvds_bl_power)
			dev_priv->ops->lvds_bl_power(dev, true);
	} else {
		if (dev_priv->ops->lvds_bl_power)
			dev_priv->ops->lvds_bl_power(dev, false);
		REG_WRITE(PP_CONTROL, REG_READ(PP_CONTROL) &
			  ~POWER_TARGET_ON);
		do {
			pp_status = REG_READ(PP_STATUS);
		} while (pp_status & PP_ON);
		dev_priv->is_lvds_on = false;
		pm_request_idle(&dev->pdev->dev);
	}
	gma_power_end(dev);
}