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
struct rockchip_crtc_state {int /*<<< orphan*/  output_flags; int /*<<< orphan*/  output_type; int /*<<< orphan*/  output_mode; } ;
struct dw_mipi_dsi_rockchip {int format; scalar_t__ slave; } ;
struct drm_encoder {int dummy; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_connector_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_DSI ; 
 int EINVAL ; 
#define  MIPI_DSI_FMT_RGB565 130 
#define  MIPI_DSI_FMT_RGB666 129 
#define  MIPI_DSI_FMT_RGB888 128 
 int /*<<< orphan*/  ROCKCHIP_OUTPUT_DSI_DUAL ; 
 int /*<<< orphan*/  ROCKCHIP_OUT_MODE_P565 ; 
 int /*<<< orphan*/  ROCKCHIP_OUT_MODE_P666 ; 
 int /*<<< orphan*/  ROCKCHIP_OUT_MODE_P888 ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct dw_mipi_dsi_rockchip* to_dsi (struct drm_encoder*) ; 
 struct rockchip_crtc_state* to_rockchip_crtc_state (struct drm_crtc_state*) ; 

__attribute__((used)) static int
dw_mipi_dsi_encoder_atomic_check(struct drm_encoder *encoder,
				 struct drm_crtc_state *crtc_state,
				 struct drm_connector_state *conn_state)
{
	struct rockchip_crtc_state *s = to_rockchip_crtc_state(crtc_state);
	struct dw_mipi_dsi_rockchip *dsi = to_dsi(encoder);

	switch (dsi->format) {
	case MIPI_DSI_FMT_RGB888:
		s->output_mode = ROCKCHIP_OUT_MODE_P888;
		break;
	case MIPI_DSI_FMT_RGB666:
		s->output_mode = ROCKCHIP_OUT_MODE_P666;
		break;
	case MIPI_DSI_FMT_RGB565:
		s->output_mode = ROCKCHIP_OUT_MODE_P565;
		break;
	default:
		WARN_ON(1);
		return -EINVAL;
	}

	s->output_type = DRM_MODE_CONNECTOR_DSI;
	if (dsi->slave)
		s->output_flags = ROCKCHIP_OUTPUT_DSI_DUAL;

	return 0;
}