#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  colorspace; } ;
union hdmi_infoframe {TYPE_2__ avi; } ;
typedef  int /*<<< orphan*/  u8 ;
struct intel_lspcon {int /*<<< orphan*/  active; } ;
struct intel_encoder {int /*<<< orphan*/  base; } ;
struct intel_digital_port {int /*<<< orphan*/  (* write_infoframe ) (struct intel_encoder*,struct intel_crtc_state const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ;struct intel_lspcon lspcon; } ;
struct drm_display_mode {int dummy; } ;
struct TYPE_4__ {struct drm_display_mode adjusted_mode; } ;
struct intel_crtc_state {scalar_t__ output_format; scalar_t__ limited_color_range; scalar_t__ lspcon_downsampling; TYPE_1__ base; } ;
struct drm_connector_state {int /*<<< orphan*/  connector; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  HDMI_COLORSPACE_RGB ; 
 int /*<<< orphan*/  HDMI_COLORSPACE_YUV420 ; 
 int /*<<< orphan*/  HDMI_COLORSPACE_YUV444 ; 
 int /*<<< orphan*/  HDMI_INFOFRAME_TYPE_AVI ; 
 int /*<<< orphan*/  HDMI_QUANTIZATION_RANGE_FULL ; 
 int /*<<< orphan*/  HDMI_QUANTIZATION_RANGE_LIMITED ; 
 scalar_t__ INTEL_OUTPUT_FORMAT_YCBCR444 ; 
 int VIDEO_DIP_DATA_SIZE ; 
 scalar_t__ drm_hdmi_avi_infoframe_from_display_mode (TYPE_2__*,int /*<<< orphan*/ ,struct drm_display_mode const*) ; 
 int /*<<< orphan*/  drm_hdmi_avi_infoframe_quant_range (TYPE_2__*,int /*<<< orphan*/ ,struct drm_display_mode const*,int /*<<< orphan*/ ) ; 
 struct intel_digital_port* enc_to_dig_port (int /*<<< orphan*/ *) ; 
 scalar_t__ hdmi_infoframe_pack (union hdmi_infoframe*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (struct intel_encoder*,struct intel_crtc_state const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

void lspcon_set_infoframes(struct intel_encoder *encoder,
			   bool enable,
			   const struct intel_crtc_state *crtc_state,
			   const struct drm_connector_state *conn_state)
{
	ssize_t ret;
	union hdmi_infoframe frame;
	u8 buf[VIDEO_DIP_DATA_SIZE];
	struct intel_digital_port *dig_port = enc_to_dig_port(&encoder->base);
	struct intel_lspcon *lspcon = &dig_port->lspcon;
	const struct drm_display_mode *adjusted_mode =
		&crtc_state->base.adjusted_mode;

	if (!lspcon->active) {
		DRM_ERROR("Writing infoframes while LSPCON disabled ?\n");
		return;
	}

	/* FIXME precompute infoframes */

	ret = drm_hdmi_avi_infoframe_from_display_mode(&frame.avi,
						       conn_state->connector,
						       adjusted_mode);
	if (ret < 0) {
		DRM_ERROR("couldn't fill AVI infoframe\n");
		return;
	}

	if (crtc_state->output_format == INTEL_OUTPUT_FORMAT_YCBCR444) {
		if (crtc_state->lspcon_downsampling)
			frame.avi.colorspace = HDMI_COLORSPACE_YUV420;
		else
			frame.avi.colorspace = HDMI_COLORSPACE_YUV444;
	} else {
		frame.avi.colorspace = HDMI_COLORSPACE_RGB;
	}

	drm_hdmi_avi_infoframe_quant_range(&frame.avi,
					   conn_state->connector,
					   adjusted_mode,
					   crtc_state->limited_color_range ?
					   HDMI_QUANTIZATION_RANGE_LIMITED :
					   HDMI_QUANTIZATION_RANGE_FULL);

	ret = hdmi_infoframe_pack(&frame, buf, sizeof(buf));
	if (ret < 0) {
		DRM_ERROR("Failed to pack AVI IF\n");
		return;
	}

	dig_port->write_infoframe(encoder, crtc_state, HDMI_INFOFRAME_TYPE_AVI,
				  buf, ret);
}