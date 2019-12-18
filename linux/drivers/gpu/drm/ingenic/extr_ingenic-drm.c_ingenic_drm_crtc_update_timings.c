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
struct ingenic_drm {int /*<<< orphan*/  map; scalar_t__ panel_is_sharp; } ;
struct drm_display_mode {unsigned int vsync_end; unsigned int vsync_start; unsigned int vtotal; unsigned int vdisplay; unsigned int hsync_end; unsigned int hsync_start; unsigned int htotal; unsigned int hdisplay; } ;

/* Variables and functions */
 unsigned int JZ_LCD_DAH_HDE_OFFSET ; 
 unsigned int JZ_LCD_DAH_HDS_OFFSET ; 
 unsigned int JZ_LCD_DAV_VDE_OFFSET ; 
 unsigned int JZ_LCD_DAV_VDS_OFFSET ; 
 unsigned int JZ_LCD_HSYNC_HPE_OFFSET ; 
 unsigned int JZ_LCD_HSYNC_HPS_OFFSET ; 
 unsigned int JZ_LCD_VAT_HT_OFFSET ; 
 unsigned int JZ_LCD_VAT_VT_OFFSET ; 
 unsigned int JZ_LCD_VSYNC_VPE_OFFSET ; 
 unsigned int JZ_LCD_VSYNC_VPS_OFFSET ; 
 int /*<<< orphan*/  JZ_REG_LCD_CLS ; 
 int /*<<< orphan*/  JZ_REG_LCD_DAH ; 
 int /*<<< orphan*/  JZ_REG_LCD_DAV ; 
 int /*<<< orphan*/  JZ_REG_LCD_HSYNC ; 
 int /*<<< orphan*/  JZ_REG_LCD_PS ; 
 int /*<<< orphan*/  JZ_REG_LCD_REV ; 
 int /*<<< orphan*/  JZ_REG_LCD_SPL ; 
 int /*<<< orphan*/  JZ_REG_LCD_VAT ; 
 int /*<<< orphan*/  JZ_REG_LCD_VSYNC ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ingenic_drm_crtc_update_timings(struct ingenic_drm *priv,
					    struct drm_display_mode *mode)
{
	unsigned int vpe, vds, vde, vt, hpe, hds, hde, ht;

	vpe = mode->vsync_end - mode->vsync_start;
	vds = mode->vtotal - mode->vsync_start;
	vde = vds + mode->vdisplay;
	vt = vde + mode->vsync_start - mode->vdisplay;

	hpe = mode->hsync_end - mode->hsync_start;
	hds = mode->htotal - mode->hsync_start;
	hde = hds + mode->hdisplay;
	ht = hde + mode->hsync_start - mode->hdisplay;

	regmap_write(priv->map, JZ_REG_LCD_VSYNC,
		     0 << JZ_LCD_VSYNC_VPS_OFFSET |
		     vpe << JZ_LCD_VSYNC_VPE_OFFSET);

	regmap_write(priv->map, JZ_REG_LCD_HSYNC,
		     0 << JZ_LCD_HSYNC_HPS_OFFSET |
		     hpe << JZ_LCD_HSYNC_HPE_OFFSET);

	regmap_write(priv->map, JZ_REG_LCD_VAT,
		     ht << JZ_LCD_VAT_HT_OFFSET |
		     vt << JZ_LCD_VAT_VT_OFFSET);

	regmap_write(priv->map, JZ_REG_LCD_DAH,
		     hds << JZ_LCD_DAH_HDS_OFFSET |
		     hde << JZ_LCD_DAH_HDE_OFFSET);
	regmap_write(priv->map, JZ_REG_LCD_DAV,
		     vds << JZ_LCD_DAV_VDS_OFFSET |
		     vde << JZ_LCD_DAV_VDE_OFFSET);

	if (priv->panel_is_sharp) {
		regmap_write(priv->map, JZ_REG_LCD_PS, hde << 16 | (hde + 1));
		regmap_write(priv->map, JZ_REG_LCD_CLS, hde << 16 | (hde + 1));
		regmap_write(priv->map, JZ_REG_LCD_SPL, hpe << 16 | (hpe + 1));
		regmap_write(priv->map, JZ_REG_LCD_REV, mode->htotal << 16);
	}
}