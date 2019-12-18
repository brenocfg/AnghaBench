#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct link_encoder {int dummy; } ;
struct dce110_link_encoder {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  pixel_encoding; } ;
struct dc_stream_state {int signal; TYPE_2__ timing; int /*<<< orphan*/  phy_pix_clk; TYPE_1__* link; } ;
struct TYPE_5__ {int /*<<< orphan*/  connector_signal; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIXEL_ENCODING_RGB ; 
#define  SIGNAL_TYPE_DISPLAY_PORT 135 
#define  SIGNAL_TYPE_DISPLAY_PORT_MST 134 
#define  SIGNAL_TYPE_DVI_DUAL_LINK 133 
#define  SIGNAL_TYPE_DVI_SINGLE_LINK 132 
#define  SIGNAL_TYPE_EDP 131 
#define  SIGNAL_TYPE_HDMI_TYPE_A 130 
#define  SIGNAL_TYPE_LVDS 129 
#define  SIGNAL_TYPE_VIRTUAL 128 
 struct dce110_link_encoder* TO_DCE110_LINK_ENC (struct link_encoder*) ; 
 int dce110_link_encoder_validate_dp_output (struct dce110_link_encoder*,TYPE_2__*) ; 
 int dce110_link_encoder_validate_dvi_output (struct dce110_link_encoder*,int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int dce110_link_encoder_validate_hdmi_output (struct dce110_link_encoder*,TYPE_2__*,int /*<<< orphan*/ ) ; 

bool dce110_link_encoder_validate_output_with_stream(
	struct link_encoder *enc,
	const struct dc_stream_state *stream)
{
	struct dce110_link_encoder *enc110 = TO_DCE110_LINK_ENC(enc);
	bool is_valid;

	switch (stream->signal) {
	case SIGNAL_TYPE_DVI_SINGLE_LINK:
	case SIGNAL_TYPE_DVI_DUAL_LINK:
		is_valid = dce110_link_encoder_validate_dvi_output(
			enc110,
			stream->link->connector_signal,
			stream->signal,
			&stream->timing);
	break;
	case SIGNAL_TYPE_HDMI_TYPE_A:
		is_valid = dce110_link_encoder_validate_hdmi_output(
				enc110,
				&stream->timing,
				stream->phy_pix_clk);
	break;
	case SIGNAL_TYPE_DISPLAY_PORT:
	case SIGNAL_TYPE_DISPLAY_PORT_MST:
		is_valid = dce110_link_encoder_validate_dp_output(
					enc110, &stream->timing);
	break;
	case SIGNAL_TYPE_EDP:
	case SIGNAL_TYPE_LVDS:
		is_valid =
			(stream->timing.
				pixel_encoding == PIXEL_ENCODING_RGB) ? true : false;
	break;
	case SIGNAL_TYPE_VIRTUAL:
		is_valid = true;
		break;
	default:
		is_valid = false;
	break;
	}

	return is_valid;
}