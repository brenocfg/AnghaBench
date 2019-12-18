#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  YCrCr420_CONVERSION; int /*<<< orphan*/  YCrCr422_CONVERSION; int /*<<< orphan*/  YCrCr420_PASS_THROUGH; int /*<<< orphan*/  YCrCr422_PASS_THROUGH; int /*<<< orphan*/  FRAME_SEQ_TO_FRAME_PACK; } ;
union dwnstream_port_caps_byte3_hdmi {int raw; TYPE_4__ bits; } ;
struct TYPE_12__ {int /*<<< orphan*/  MAX_BITS_PER_COLOR_COMPONENT; } ;
union dwnstream_port_caps_byte2 {int raw; TYPE_5__ bits; } ;
struct TYPE_10__ {int DWN_STRM_PORTX_TYPE; } ;
union dwnstream_port_caps_byte0 {TYPE_3__ bits; } ;
struct TYPE_9__ {int PORT_PRESENT; int PORT_TYPE; int /*<<< orphan*/  DETAILED_CAPS; } ;
union dp_downstream_port_present {int byte; TYPE_2__ fields; } ;
typedef  int uint8_t ;
struct dp_sink_hw_fw_revision {int /*<<< orphan*/  ieee_fw_rev; int /*<<< orphan*/  ieee_hw_rev; } ;
struct TYPE_13__ {int dp_hdmi_max_pixel_clk_in_khz; int extendedCapValid; int /*<<< orphan*/  dp_hdmi_max_bpc; int /*<<< orphan*/  is_dp_hdmi_ycbcr420_converter; int /*<<< orphan*/  is_dp_hdmi_ycbcr422_converter; int /*<<< orphan*/  is_dp_hdmi_ycbcr420_pass_through; int /*<<< orphan*/  is_dp_hdmi_ycbcr422_pass_through; int /*<<< orphan*/  is_dp_hdmi_s3d_converter; void* dongle_type; } ;
struct TYPE_8__ {scalar_t__ raw; } ;
struct TYPE_14__ {int is_branch_dev; int /*<<< orphan*/  branch_fw_revision; int /*<<< orphan*/  branch_hw_revision; void* dongle_type; TYPE_6__ dongle_caps; TYPE_1__ dpcd_rev; } ;
struct dc_link {TYPE_7__ dpcd_caps; int /*<<< orphan*/  ddc; } ;
typedef  int /*<<< orphan*/  dp_hw_fw_revision ;
typedef  int /*<<< orphan*/  det_caps ;

/* Variables and functions */
 void* DISPLAY_DONGLE_DP_DVI_CONVERTER ; 
 void* DISPLAY_DONGLE_DP_HDMI_CONVERTER ; 
 void* DISPLAY_DONGLE_DP_VGA_CONVERTER ; 
 void* DISPLAY_DONGLE_NONE ; 
 int DOWNSTREAM_DP ; 
#define  DOWNSTREAM_DVI_HDMI_DP_PLUS_PLUS 134 
#define  DOWNSTREAM_VGA 133 
#define  DOWN_STREAM_DETAILED_DP 132 
#define  DOWN_STREAM_DETAILED_DP_PLUS_PLUS 131 
#define  DOWN_STREAM_DETAILED_DVI 130 
#define  DOWN_STREAM_DETAILED_HDMI 129 
#define  DOWN_STREAM_DETAILED_VGA 128 
 scalar_t__ DPCD_REV_11 ; 
 int /*<<< orphan*/  DP_BRANCH_REVISION_START ; 
 int /*<<< orphan*/  DP_DOWNSTREAM_PORT_0 ; 
 int /*<<< orphan*/  core_link_read_dpcd (struct dc_link*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  ddc_service_set_dongle_type (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  translate_dpcd_max_bpc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_active_converter_info(
	uint8_t data, struct dc_link *link)
{
	union dp_downstream_port_present ds_port = { .byte = data };

	/* decode converter info*/
	if (!ds_port.fields.PORT_PRESENT) {
		link->dpcd_caps.dongle_type = DISPLAY_DONGLE_NONE;
		ddc_service_set_dongle_type(link->ddc,
				link->dpcd_caps.dongle_type);
		link->dpcd_caps.is_branch_dev = false;
		return;
	}

	/* DPCD 0x5 bit 0 = 1, it indicate it's branch device */
	if (ds_port.fields.PORT_TYPE == DOWNSTREAM_DP) {
		link->dpcd_caps.is_branch_dev = false;
	}

	else {
		link->dpcd_caps.is_branch_dev = ds_port.fields.PORT_PRESENT;
	}

	switch (ds_port.fields.PORT_TYPE) {
	case DOWNSTREAM_VGA:
		link->dpcd_caps.dongle_type = DISPLAY_DONGLE_DP_VGA_CONVERTER;
		break;
	case DOWNSTREAM_DVI_HDMI_DP_PLUS_PLUS:
		/* At this point we don't know is it DVI or HDMI or DP++,
		 * assume DVI.*/
		link->dpcd_caps.dongle_type = DISPLAY_DONGLE_DP_DVI_CONVERTER;
		break;
	default:
		link->dpcd_caps.dongle_type = DISPLAY_DONGLE_NONE;
		break;
	}

	if (link->dpcd_caps.dpcd_rev.raw >= DPCD_REV_11) {
		uint8_t det_caps[16]; /* CTS 4.2.2.7 expects source to read Detailed Capabilities Info : 00080h-0008F.*/
		union dwnstream_port_caps_byte0 *port_caps =
			(union dwnstream_port_caps_byte0 *)det_caps;
		core_link_read_dpcd(link, DP_DOWNSTREAM_PORT_0,
				det_caps, sizeof(det_caps));

		switch (port_caps->bits.DWN_STRM_PORTX_TYPE) {
		/*Handle DP case as DONGLE_NONE*/
		case DOWN_STREAM_DETAILED_DP:
			link->dpcd_caps.dongle_type = DISPLAY_DONGLE_NONE;
			break;
		case DOWN_STREAM_DETAILED_VGA:
			link->dpcd_caps.dongle_type =
				DISPLAY_DONGLE_DP_VGA_CONVERTER;
			break;
		case DOWN_STREAM_DETAILED_DVI:
			link->dpcd_caps.dongle_type =
				DISPLAY_DONGLE_DP_DVI_CONVERTER;
			break;
		case DOWN_STREAM_DETAILED_HDMI:
		case DOWN_STREAM_DETAILED_DP_PLUS_PLUS:
			/*Handle DP++ active converter case, process DP++ case as HDMI case according DP1.4 spec*/
			link->dpcd_caps.dongle_type =
				DISPLAY_DONGLE_DP_HDMI_CONVERTER;

			link->dpcd_caps.dongle_caps.dongle_type = link->dpcd_caps.dongle_type;
			if (ds_port.fields.DETAILED_CAPS) {

				union dwnstream_port_caps_byte3_hdmi
					hdmi_caps = {.raw = det_caps[3] };
				union dwnstream_port_caps_byte2
					hdmi_color_caps = {.raw = det_caps[2] };
				link->dpcd_caps.dongle_caps.dp_hdmi_max_pixel_clk_in_khz =
					det_caps[1] * 2500;

				link->dpcd_caps.dongle_caps.is_dp_hdmi_s3d_converter =
					hdmi_caps.bits.FRAME_SEQ_TO_FRAME_PACK;
				/*YCBCR capability only for HDMI case*/
				if (port_caps->bits.DWN_STRM_PORTX_TYPE
						== DOWN_STREAM_DETAILED_HDMI) {
					link->dpcd_caps.dongle_caps.is_dp_hdmi_ycbcr422_pass_through =
							hdmi_caps.bits.YCrCr422_PASS_THROUGH;
					link->dpcd_caps.dongle_caps.is_dp_hdmi_ycbcr420_pass_through =
							hdmi_caps.bits.YCrCr420_PASS_THROUGH;
					link->dpcd_caps.dongle_caps.is_dp_hdmi_ycbcr422_converter =
							hdmi_caps.bits.YCrCr422_CONVERSION;
					link->dpcd_caps.dongle_caps.is_dp_hdmi_ycbcr420_converter =
							hdmi_caps.bits.YCrCr420_CONVERSION;
				}

				link->dpcd_caps.dongle_caps.dp_hdmi_max_bpc =
					translate_dpcd_max_bpc(
						hdmi_color_caps.bits.MAX_BITS_PER_COLOR_COMPONENT);

				if (link->dpcd_caps.dongle_caps.dp_hdmi_max_pixel_clk_in_khz != 0)
					link->dpcd_caps.dongle_caps.extendedCapValid = true;
			}

			break;
		}
	}

	ddc_service_set_dongle_type(link->ddc, link->dpcd_caps.dongle_type);

	{
		struct dp_sink_hw_fw_revision dp_hw_fw_revision;

		core_link_read_dpcd(
			link,
			DP_BRANCH_REVISION_START,
			(uint8_t *)&dp_hw_fw_revision,
			sizeof(dp_hw_fw_revision));

		link->dpcd_caps.branch_hw_revision =
			dp_hw_fw_revision.ieee_hw_rev;

		memmove(
			link->dpcd_caps.branch_fw_revision,
			dp_hw_fw_revision.ieee_fw_rev,
			sizeof(dp_hw_fw_revision.ieee_fw_rev));
	}
}