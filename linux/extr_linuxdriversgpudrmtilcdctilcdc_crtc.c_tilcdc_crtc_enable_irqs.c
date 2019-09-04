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

/* Variables and functions */
 int /*<<< orphan*/  LCDC_DMA_CTRL_REG ; 
 int LCDC_FRAME_DONE ; 
 int /*<<< orphan*/  LCDC_INT_ENABLE_SET_REG ; 
 int /*<<< orphan*/  LCDC_RASTER_CTRL_REG ; 
 int LCDC_SYNC_LOST ; 
 int LCDC_V1_END_OF_FRAME_INT_ENA ; 
 int LCDC_V1_FRAME_DONE_INT_ENA ; 
 int LCDC_V1_SYNC_LOST_INT_ENA ; 
 int LCDC_V1_UNDERFLOW_INT_ENA ; 
 int LCDC_V2_END_OF_FRAME0_INT_ENA ; 
 int LCDC_V2_UNDERFLOW_INT_ENA ; 
 int /*<<< orphan*/  tilcdc_clear_irqstatus (struct drm_device*,int) ; 
 int /*<<< orphan*/  tilcdc_set (struct drm_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tilcdc_write (struct drm_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tilcdc_crtc_enable_irqs(struct drm_device *dev)
{
	struct tilcdc_drm_private *priv = dev->dev_private;

	tilcdc_clear_irqstatus(dev, 0xffffffff);

	if (priv->rev == 1) {
		tilcdc_set(dev, LCDC_RASTER_CTRL_REG,
			LCDC_V1_SYNC_LOST_INT_ENA | LCDC_V1_FRAME_DONE_INT_ENA |
			LCDC_V1_UNDERFLOW_INT_ENA);
		tilcdc_set(dev, LCDC_DMA_CTRL_REG,
			LCDC_V1_END_OF_FRAME_INT_ENA);
	} else {
		tilcdc_write(dev, LCDC_INT_ENABLE_SET_REG,
			LCDC_V2_UNDERFLOW_INT_ENA |
			LCDC_V2_END_OF_FRAME0_INT_ENA |
			LCDC_FRAME_DONE | LCDC_SYNC_LOST);
	}
}