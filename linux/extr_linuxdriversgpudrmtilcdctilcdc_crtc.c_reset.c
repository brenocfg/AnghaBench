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
struct tilcdc_drm_private {int rev; } ;
struct drm_device {struct tilcdc_drm_private* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCDC_CLK_MAIN_RESET ; 
 int /*<<< orphan*/  LCDC_CLK_RESET_REG ; 
 int /*<<< orphan*/  tilcdc_clear (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tilcdc_set (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void reset(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	struct tilcdc_drm_private *priv = dev->dev_private;

	if (priv->rev != 2)
		return;

	tilcdc_set(dev, LCDC_CLK_RESET_REG, LCDC_CLK_MAIN_RESET);
	usleep_range(250, 1000);
	tilcdc_clear(dev, LCDC_CLK_RESET_REG, LCDC_CLK_MAIN_RESET);
}