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
typedef  int uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_2__ {int timing_3d_format; int hdmi_vic; int h_total; int v_total; } ;
struct dc_stream_state {scalar_t__ view_format; TYPE_1__ timing; } ;
struct dc_info_packet {int valid; int* sb; int hb1; int hb2; scalar_t__ hb0; } ;
typedef  enum dc_timing_3d_format { ____Placeholder_dc_timing_3d_format } dc_timing_3d_format ;

/* Variables and functions */
 scalar_t__ HDMI_INFOFRAME_TYPE_VENDOR ; 
#define  TIMING_3D_FORMAT_HW_FRAME_PACKING 133 
 int TIMING_3D_FORMAT_NONE ; 
#define  TIMING_3D_FORMAT_SBS_SW_PACKED 132 
#define  TIMING_3D_FORMAT_SIDE_BY_SIDE 131 
#define  TIMING_3D_FORMAT_SW_FRAME_PACKING 130 
#define  TIMING_3D_FORMAT_TB_SW_PACKED 129 
#define  TIMING_3D_FORMAT_TOP_AND_BOTTOM 128 
 scalar_t__ VIEW_3D_FORMAT_NONE ; 

__attribute__((used)) static void set_vendor_info_packet(
		struct dc_info_packet *info_packet,
		struct dc_stream_state *stream)
{
	uint32_t length = 0;
	bool hdmi_vic_mode = false;
	uint8_t checksum = 0;
	uint32_t i = 0;
	enum dc_timing_3d_format format;
	// Can be different depending on packet content /*todo*/
	// unsigned int length = pPathMode->dolbyVision ? 24 : 5;

	info_packet->valid = false;

	format = stream->timing.timing_3d_format;
	if (stream->view_format == VIEW_3D_FORMAT_NONE)
		format = TIMING_3D_FORMAT_NONE;

	/* Can be different depending on packet content */
	length = 5;

	if (stream->timing.hdmi_vic != 0
			&& stream->timing.h_total >= 3840
			&& stream->timing.v_total >= 2160)
		hdmi_vic_mode = true;

	/* According to HDMI 1.4a CTS, VSIF should be sent
	 * for both 3D stereo and HDMI VIC modes.
	 * For all other modes, there is no VSIF sent.  */

	if (format == TIMING_3D_FORMAT_NONE && !hdmi_vic_mode)
		return;

	/* 24bit IEEE Registration identifier (0x000c03). LSB first. */
	info_packet->sb[1] = 0x03;
	info_packet->sb[2] = 0x0C;
	info_packet->sb[3] = 0x00;

	/*PB4: 5 lower bytes = 0 (reserved). 3 higher bits = HDMI_Video_Format.
	 * The value for HDMI_Video_Format are:
	 * 0x0 (0b000) - No additional HDMI video format is presented in this
	 * packet
	 * 0x1 (0b001) - Extended resolution format present. 1 byte of HDMI_VIC
	 * parameter follows
	 * 0x2 (0b010) - 3D format indication present. 3D_Structure and
	 * potentially 3D_Ext_Data follows
	 * 0x3..0x7 (0b011..0b111) - reserved for future use */
	if (format != TIMING_3D_FORMAT_NONE)
		info_packet->sb[4] = (2 << 5);
	else if (hdmi_vic_mode)
		info_packet->sb[4] = (1 << 5);

	/* PB5: If PB4 claims 3D timing (HDMI_Video_Format = 0x2):
	 * 4 lower bites = 0 (reserved). 4 higher bits = 3D_Structure.
	 * The value for 3D_Structure are:
	 * 0x0 - Frame Packing
	 * 0x1 - Field Alternative
	 * 0x2 - Line Alternative
	 * 0x3 - Side-by-Side (full)
	 * 0x4 - L + depth
	 * 0x5 - L + depth + graphics + graphics-depth
	 * 0x6 - Top-and-Bottom
	 * 0x7 - Reserved for future use
	 * 0x8 - Side-by-Side (Half)
	 * 0x9..0xE - Reserved for future use
	 * 0xF - Not used */
	switch (format) {
	case TIMING_3D_FORMAT_HW_FRAME_PACKING:
	case TIMING_3D_FORMAT_SW_FRAME_PACKING:
		info_packet->sb[5] = (0x0 << 4);
		break;

	case TIMING_3D_FORMAT_SIDE_BY_SIDE:
	case TIMING_3D_FORMAT_SBS_SW_PACKED:
		info_packet->sb[5] = (0x8 << 4);
		length = 6;
		break;

	case TIMING_3D_FORMAT_TOP_AND_BOTTOM:
	case TIMING_3D_FORMAT_TB_SW_PACKED:
		info_packet->sb[5] = (0x6 << 4);
		break;

	default:
		break;
	}

	/*PB5: If PB4 is set to 0x1 (extended resolution format)
	 * fill PB5 with the correct HDMI VIC code */
	if (hdmi_vic_mode)
		info_packet->sb[5] = stream->timing.hdmi_vic;

	/* Header */
	info_packet->hb0 = HDMI_INFOFRAME_TYPE_VENDOR; /* VSIF packet type. */
	info_packet->hb1 = 0x01; /* Version */

	/* 4 lower bits = Length, 4 higher bits = 0 (reserved) */
	info_packet->hb2 = (uint8_t) (length);

	/* Calculate checksum */
	checksum = 0;
	checksum += info_packet->hb0;
	checksum += info_packet->hb1;
	checksum += info_packet->hb2;

	for (i = 1; i <= length; i++)
		checksum += info_packet->sb[i];

	info_packet->sb[0] = (uint8_t) (0x100 - checksum);

	info_packet->valid = true;
}