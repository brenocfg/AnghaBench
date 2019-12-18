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
struct ingenic_drm {int /*<<< orphan*/  map; } ;
struct drm_format_info {int format; } ;

/* Variables and functions */
#define  DRM_FORMAT_RGB565 130 
#define  DRM_FORMAT_XRGB1555 129 
#define  DRM_FORMAT_XRGB8888 128 
 unsigned int JZ_LCD_CTRL_BPP_15_16 ; 
 unsigned int JZ_LCD_CTRL_BPP_18_24 ; 
 unsigned int JZ_LCD_CTRL_BPP_MASK ; 
 unsigned int JZ_LCD_CTRL_BURST_16 ; 
 unsigned int JZ_LCD_CTRL_OFUP ; 
 unsigned int JZ_LCD_CTRL_RGB555 ; 
 int /*<<< orphan*/  JZ_REG_LCD_CTRL ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static void ingenic_drm_crtc_update_ctrl(struct ingenic_drm *priv,
					 const struct drm_format_info *finfo)
{
	unsigned int ctrl = JZ_LCD_CTRL_OFUP | JZ_LCD_CTRL_BURST_16;

	switch (finfo->format) {
	case DRM_FORMAT_XRGB1555:
		ctrl |= JZ_LCD_CTRL_RGB555;
		/* fall-through */
	case DRM_FORMAT_RGB565:
		ctrl |= JZ_LCD_CTRL_BPP_15_16;
		break;
	case DRM_FORMAT_XRGB8888:
		ctrl |= JZ_LCD_CTRL_BPP_18_24;
		break;
	}

	regmap_update_bits(priv->map, JZ_REG_LCD_CTRL,
			   JZ_LCD_CTRL_OFUP | JZ_LCD_CTRL_BURST_16 |
			   JZ_LCD_CTRL_BPP_MASK, ctrl);
}