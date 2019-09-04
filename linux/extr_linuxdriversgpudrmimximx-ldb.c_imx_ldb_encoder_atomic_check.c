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
typedef  int u32 ;
struct imx_ldb_channel {int bus_format; int /*<<< orphan*/  bus_flags; } ;
struct imx_crtc_state {int di_hsync_pin; int di_vsync_pin; int /*<<< orphan*/  bus_format; int /*<<< orphan*/  bus_flags; } ;
struct drm_encoder {int dummy; } ;
struct drm_display_info {int* bus_formats; int /*<<< orphan*/  bus_flags; scalar_t__ num_bus_formats; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_connector_state {TYPE_1__* connector; } ;
struct TYPE_2__ {struct drm_display_info display_info; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_RGB666_1X18 ; 
#define  MEDIA_BUS_FMT_RGB666_1X7X3_SPWG 130 
 int /*<<< orphan*/  MEDIA_BUS_FMT_RGB888_1X24 ; 
#define  MEDIA_BUS_FMT_RGB888_1X7X4_JEIDA 129 
#define  MEDIA_BUS_FMT_RGB888_1X7X4_SPWG 128 
 struct imx_ldb_channel* enc_to_imx_ldb_ch (struct drm_encoder*) ; 
 struct imx_crtc_state* to_imx_crtc_state (struct drm_crtc_state*) ; 

__attribute__((used)) static int imx_ldb_encoder_atomic_check(struct drm_encoder *encoder,
					struct drm_crtc_state *crtc_state,
					struct drm_connector_state *conn_state)
{
	struct imx_crtc_state *imx_crtc_state = to_imx_crtc_state(crtc_state);
	struct imx_ldb_channel *imx_ldb_ch = enc_to_imx_ldb_ch(encoder);
	struct drm_display_info *di = &conn_state->connector->display_info;
	u32 bus_format = imx_ldb_ch->bus_format;

	/* Bus format description in DT overrides connector display info. */
	if (!bus_format && di->num_bus_formats) {
		bus_format = di->bus_formats[0];
		imx_crtc_state->bus_flags = di->bus_flags;
	} else {
		bus_format = imx_ldb_ch->bus_format;
		imx_crtc_state->bus_flags = imx_ldb_ch->bus_flags;
	}
	switch (bus_format) {
	case MEDIA_BUS_FMT_RGB666_1X7X3_SPWG:
		imx_crtc_state->bus_format = MEDIA_BUS_FMT_RGB666_1X18;
		break;
	case MEDIA_BUS_FMT_RGB888_1X7X4_SPWG:
	case MEDIA_BUS_FMT_RGB888_1X7X4_JEIDA:
		imx_crtc_state->bus_format = MEDIA_BUS_FMT_RGB888_1X24;
		break;
	default:
		return -EINVAL;
	}

	imx_crtc_state->di_hsync_pin = 2;
	imx_crtc_state->di_vsync_pin = 3;

	return 0;
}