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
struct ingenic_drm {int panel_is_sharp; int /*<<< orphan*/  map; } ;
struct drm_encoder {int dummy; } ;
struct drm_display_mode {int flags; } ;
struct drm_display_info {int bus_flags; int* bus_formats; } ;
struct drm_crtc_state {struct drm_display_mode adjusted_mode; } ;
struct drm_connector_state {struct drm_connector* connector; } ;
struct drm_connector {scalar_t__ connector_type; struct drm_display_info display_info; } ;

/* Variables and functions */
 int DRM_BUS_FLAG_DE_LOW ; 
 int DRM_BUS_FLAG_PIXDATA_NEGEDGE ; 
 int DRM_BUS_FLAG_SHARP_SIGNALS ; 
 scalar_t__ DRM_MODE_CONNECTOR_TV ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 int DRM_MODE_FLAG_NHSYNC ; 
 int DRM_MODE_FLAG_NVSYNC ; 
 unsigned int JZ_LCD_CFG_CLS_DISABLE ; 
 unsigned int JZ_LCD_CFG_DE_ACTIVE_LOW ; 
 unsigned int JZ_LCD_CFG_HSYNC_ACTIVE_LOW ; 
 unsigned int JZ_LCD_CFG_MODE_8BIT_SERIAL ; 
 unsigned int JZ_LCD_CFG_MODE_GENERIC_16BIT ; 
 unsigned int JZ_LCD_CFG_MODE_GENERIC_18BIT ; 
 unsigned int JZ_LCD_CFG_MODE_GENERIC_24BIT ; 
 unsigned int JZ_LCD_CFG_MODE_SPECIAL_TFT_1 ; 
 unsigned int JZ_LCD_CFG_MODE_TV_OUT_I ; 
 unsigned int JZ_LCD_CFG_MODE_TV_OUT_P ; 
 unsigned int JZ_LCD_CFG_PCLK_FALLING_EDGE ; 
 unsigned int JZ_LCD_CFG_PS_DISABLE ; 
 unsigned int JZ_LCD_CFG_REV_DISABLE ; 
 unsigned int JZ_LCD_CFG_REV_POLARITY ; 
 unsigned int JZ_LCD_CFG_SPL_DISABLE ; 
 unsigned int JZ_LCD_CFG_VSYNC_ACTIVE_LOW ; 
 int /*<<< orphan*/  JZ_REG_LCD_CFG ; 
#define  MEDIA_BUS_FMT_RGB565_1X16 131 
#define  MEDIA_BUS_FMT_RGB666_1X18 130 
#define  MEDIA_BUS_FMT_RGB888_1X24 129 
#define  MEDIA_BUS_FMT_RGB888_3X8 128 
 struct ingenic_drm* drm_encoder_get_priv (struct drm_encoder*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void ingenic_drm_encoder_atomic_mode_set(struct drm_encoder *encoder,
						struct drm_crtc_state *crtc_state,
						struct drm_connector_state *conn_state)
{
	struct ingenic_drm *priv = drm_encoder_get_priv(encoder);
	struct drm_display_mode *mode = &crtc_state->adjusted_mode;
	struct drm_connector *conn = conn_state->connector;
	struct drm_display_info *info = &conn->display_info;
	unsigned int cfg;

	priv->panel_is_sharp = info->bus_flags & DRM_BUS_FLAG_SHARP_SIGNALS;

	if (priv->panel_is_sharp) {
		cfg = JZ_LCD_CFG_MODE_SPECIAL_TFT_1 | JZ_LCD_CFG_REV_POLARITY;
	} else {
		cfg = JZ_LCD_CFG_PS_DISABLE | JZ_LCD_CFG_CLS_DISABLE
		    | JZ_LCD_CFG_SPL_DISABLE | JZ_LCD_CFG_REV_DISABLE;
	}

	if (mode->flags & DRM_MODE_FLAG_NHSYNC)
		cfg |= JZ_LCD_CFG_HSYNC_ACTIVE_LOW;
	if (mode->flags & DRM_MODE_FLAG_NVSYNC)
		cfg |= JZ_LCD_CFG_VSYNC_ACTIVE_LOW;
	if (info->bus_flags & DRM_BUS_FLAG_DE_LOW)
		cfg |= JZ_LCD_CFG_DE_ACTIVE_LOW;
	if (info->bus_flags & DRM_BUS_FLAG_PIXDATA_NEGEDGE)
		cfg |= JZ_LCD_CFG_PCLK_FALLING_EDGE;

	if (!priv->panel_is_sharp) {
		if (conn->connector_type == DRM_MODE_CONNECTOR_TV) {
			if (mode->flags & DRM_MODE_FLAG_INTERLACE)
				cfg |= JZ_LCD_CFG_MODE_TV_OUT_I;
			else
				cfg |= JZ_LCD_CFG_MODE_TV_OUT_P;
		} else {
			switch (*info->bus_formats) {
			case MEDIA_BUS_FMT_RGB565_1X16:
				cfg |= JZ_LCD_CFG_MODE_GENERIC_16BIT;
				break;
			case MEDIA_BUS_FMT_RGB666_1X18:
				cfg |= JZ_LCD_CFG_MODE_GENERIC_18BIT;
				break;
			case MEDIA_BUS_FMT_RGB888_1X24:
				cfg |= JZ_LCD_CFG_MODE_GENERIC_24BIT;
				break;
			case MEDIA_BUS_FMT_RGB888_3X8:
				cfg |= JZ_LCD_CFG_MODE_8BIT_SERIAL;
				break;
			default:
				break;
			}
		}
	}

	regmap_write(priv->map, JZ_REG_LCD_CFG, cfg);
}