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
struct imx_crtc_state {int di_hsync_pin; int di_vsync_pin; int /*<<< orphan*/  bus_format; } ;
struct drm_encoder {int dummy; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_connector_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEDIA_BUS_FMT_RGB888_1X24 ; 
 struct imx_crtc_state* to_imx_crtc_state (struct drm_crtc_state*) ; 

__attribute__((used)) static int dw_hdmi_imx_atomic_check(struct drm_encoder *encoder,
				    struct drm_crtc_state *crtc_state,
				    struct drm_connector_state *conn_state)
{
	struct imx_crtc_state *imx_crtc_state = to_imx_crtc_state(crtc_state);

	imx_crtc_state->bus_format = MEDIA_BUS_FMT_RGB888_1X24;
	imx_crtc_state->di_hsync_pin = 2;
	imx_crtc_state->di_vsync_pin = 3;

	return 0;
}