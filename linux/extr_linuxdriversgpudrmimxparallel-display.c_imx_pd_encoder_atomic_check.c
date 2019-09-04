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
struct imx_parallel_display {scalar_t__ bus_format; int /*<<< orphan*/  bus_flags; } ;
struct imx_crtc_state {int di_hsync_pin; int di_vsync_pin; scalar_t__ bus_format; int /*<<< orphan*/  bus_flags; } ;
struct drm_encoder {int dummy; } ;
struct drm_display_info {scalar_t__* bus_formats; int /*<<< orphan*/  bus_flags; scalar_t__ num_bus_formats; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_connector_state {TYPE_1__* connector; } ;
struct TYPE_2__ {struct drm_display_info display_info; } ;

/* Variables and functions */
 struct imx_parallel_display* enc_to_imxpd (struct drm_encoder*) ; 
 struct imx_crtc_state* to_imx_crtc_state (struct drm_crtc_state*) ; 

__attribute__((used)) static int imx_pd_encoder_atomic_check(struct drm_encoder *encoder,
				       struct drm_crtc_state *crtc_state,
				       struct drm_connector_state *conn_state)
{
	struct imx_crtc_state *imx_crtc_state = to_imx_crtc_state(crtc_state);
	struct drm_display_info *di = &conn_state->connector->display_info;
	struct imx_parallel_display *imxpd = enc_to_imxpd(encoder);

	if (!imxpd->bus_format && di->num_bus_formats) {
		imx_crtc_state->bus_flags = di->bus_flags;
		imx_crtc_state->bus_format = di->bus_formats[0];
	} else {
		imx_crtc_state->bus_flags = imxpd->bus_flags;
		imx_crtc_state->bus_format = imxpd->bus_format;
	}
	imx_crtc_state->di_hsync_pin = 2;
	imx_crtc_state->di_vsync_pin = 3;

	return 0;
}