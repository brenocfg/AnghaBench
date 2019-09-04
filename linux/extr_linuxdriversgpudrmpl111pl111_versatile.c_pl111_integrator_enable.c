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
typedef  int u32 ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  DRM_FORMAT_XBGR1555 131 
#define  DRM_FORMAT_XBGR8888 130 
#define  DRM_FORMAT_XRGB1555 129 
#define  DRM_FORMAT_XRGB8888 128 
 int INTEGRATOR_CLCD_LCD0_EN ; 
 int INTEGRATOR_CLCD_LCD1_EN ; 
 int INTEGRATOR_CLCD_LCDMUX_VGA24 ; 
 int INTEGRATOR_CLCD_LCDMUX_VGA555 ; 
 int INTEGRATOR_CLCD_LCD_STATIC1 ; 
 int INTEGRATOR_CLCD_LCD_STATIC2 ; 
 int /*<<< orphan*/  INTEGRATOR_CLCD_MASK ; 
 int /*<<< orphan*/  INTEGRATOR_HDR_CTRL_OFFSET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  versatile_syscon_map ; 

__attribute__((used)) static void pl111_integrator_enable(struct drm_device *drm, u32 format)
{
	u32 val;

	dev_info(drm->dev, "enable Integrator CLCD connectors\n");

	/* FIXME: really needed? */
	val = INTEGRATOR_CLCD_LCD_STATIC1 | INTEGRATOR_CLCD_LCD_STATIC2 |
		INTEGRATOR_CLCD_LCD0_EN | INTEGRATOR_CLCD_LCD1_EN;

	switch (format) {
	case DRM_FORMAT_XBGR8888:
	case DRM_FORMAT_XRGB8888:
		/* 24bit formats */
		val |= INTEGRATOR_CLCD_LCDMUX_VGA24;
		break;
	case DRM_FORMAT_XBGR1555:
	case DRM_FORMAT_XRGB1555:
		/* Pseudocolor, RGB555, BGR555 */
		val |= INTEGRATOR_CLCD_LCDMUX_VGA555;
		break;
	default:
		dev_err(drm->dev, "unhandled format on Integrator 0x%08x\n",
			format);
		break;
	}

	regmap_update_bits(versatile_syscon_map,
			   INTEGRATOR_HDR_CTRL_OFFSET,
			   INTEGRATOR_CLCD_MASK,
			   val);
}