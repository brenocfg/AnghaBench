#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__* sb; int /*<<< orphan*/  hb2; int /*<<< orphan*/  hb1; int /*<<< orphan*/  hb0; } ;
struct TYPE_8__ {int version; scalar_t__ length; scalar_t__ info_frame_type; } ;
struct TYPE_10__ {int Y0_Y1_Y2; int S0_S1; scalar_t__ C0_C1; scalar_t__ EC0_EC2; int M0_M1; unsigned int CN0_CN1; unsigned int VIC0_VIC7; TYPE_3__ header; scalar_t__ ACE0_ACE3; scalar_t__ bar_right; int /*<<< orphan*/  bar_left; scalar_t__ bar_bottom; int /*<<< orphan*/  bar_top; scalar_t__ PR0_PR3; void* YQ0_YQ1; void* Q0_Q1; scalar_t__ ITC; int /*<<< orphan*/  R0_R3; int /*<<< orphan*/  SC0_SC1; int /*<<< orphan*/  B0_B1; int /*<<< orphan*/  A0; } ;
union hdmi_info_packet {TYPE_2__ packet_raw_data; TYPE_5__ bits; } ;
struct TYPE_6__ {int graphics_content; int photo_content; int cinema_content; int game_content; int /*<<< orphan*/  valid_content_type; } ;
union display_content_support {TYPE_1__ bits; int /*<<< orphan*/  member_0; } ;
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct pipe_ctx {struct dc_stream_state* stream; } ;
struct TYPE_9__ {unsigned int vic; int pixel_encoding; int aspect_ratio; int timing_3d_format; int hdmi_vic; scalar_t__ h_border_right; scalar_t__ h_total; int /*<<< orphan*/  h_border_left; scalar_t__ v_border_bottom; scalar_t__ v_total; int /*<<< orphan*/  v_border_top; } ;
struct dc_stream_state {int output_color_space; int qs_bit; int qy_bit; TYPE_4__ timing; union display_content_support content_support; } ;
struct dc_info_packet {scalar_t__* sb; int valid; int /*<<< orphan*/  hb2; int /*<<< orphan*/  hb1; int /*<<< orphan*/  hb0; } ;
typedef  enum scanning_type { ____Placeholder_scanning_type } scanning_type ;
typedef  enum dc_timing_3d_format { ____Placeholder_dc_timing_3d_format } dc_timing_3d_format ;
typedef  enum dc_color_space { ____Placeholder_dc_color_space } dc_color_space ;
typedef  enum dc_aspect_ratio { ____Placeholder_dc_aspect_ratio } dc_aspect_ratio ;

/* Variables and functions */
 int /*<<< orphan*/  ACTIVE_FORMAT_ASPECT_RATIO_SAME_AS_PICTURE ; 
 int /*<<< orphan*/  ACTIVE_FORMAT_VALID ; 
#define  ASPECT_RATIO_16_9 136 
#define  ASPECT_RATIO_256_135 135 
#define  ASPECT_RATIO_4_3 134 
#define  ASPECT_RATIO_64_27 133 
#define  ASPECT_RATIO_NO_DATA 132 
 int /*<<< orphan*/  BAR_INFO_BOTH_VALID ; 
 scalar_t__ COLORIMETRYEX_ADOBERGB ; 
 scalar_t__ COLORIMETRYEX_BT2020RGBYCBCR ; 
 scalar_t__ COLORIMETRYEX_RESERVED ; 
 scalar_t__ COLORIMETRY_EXTENDED ; 
 scalar_t__ COLORIMETRY_ITU601 ; 
 scalar_t__ COLORIMETRY_ITU709 ; 
 scalar_t__ COLORIMETRY_NO_DATA ; 
 int COLOR_SPACE_2020_RGB_FULLRANGE ; 
 int COLOR_SPACE_2020_RGB_LIMITEDRANGE ; 
 int COLOR_SPACE_2020_YCBCR ; 
 int COLOR_SPACE_ADOBERGB ; 
 int COLOR_SPACE_SRGB ; 
 int COLOR_SPACE_SRGB_LIMITED ; 
 int COLOR_SPACE_UNKNOWN ; 
 int COLOR_SPACE_YCBCR601 ; 
 int COLOR_SPACE_YCBCR601_LIMITED ; 
 int COLOR_SPACE_YCBCR709 ; 
 int COLOR_SPACE_YCBCR709_LIMITED ; 
 scalar_t__ DISPLAY_CONTENT_TYPE_CINEMA ; 
 scalar_t__ DISPLAY_CONTENT_TYPE_GAME ; 
 scalar_t__ DISPLAY_CONTENT_TYPE_GRAPHICS ; 
 scalar_t__ DISPLAY_CONTENT_TYPE_PHOTO ; 
 scalar_t__ HDMI_AVI_INFOFRAME_SIZE ; 
 scalar_t__ HDMI_INFOFRAME_TYPE_AVI ; 
 int /*<<< orphan*/  PICTURE_SCALING_UNIFORM ; 
#define  PIXEL_ENCODING_RGB 131 
#define  PIXEL_ENCODING_YCBCR420 130 
#define  PIXEL_ENCODING_YCBCR422 129 
#define  PIXEL_ENCODING_YCBCR444 128 
 void* RGB_QUANTIZATION_DEFAULT_RANGE ; 
 void* RGB_QUANTIZATION_FULL_RANGE ; 
 void* RGB_QUANTIZATION_LIMITED_RANGE ; 
 int SCANNING_TYPE_NODATA ; 
 int SCANNING_TYPE_UNDERSCAN ; 
 int TIMING_3D_FORMAT_NONE ; 
 void* YYC_QUANTIZATION_FULL_RANGE ; 
 void* YYC_QUANTIZATION_LIMITED_RANGE ; 
 int /*<<< orphan*/  memset (union hdmi_info_packet*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_avi_info_frame(
		struct dc_info_packet *info_packet,
		struct pipe_ctx *pipe_ctx)
{
	struct dc_stream_state *stream = pipe_ctx->stream;
	enum dc_color_space color_space = COLOR_SPACE_UNKNOWN;
	uint32_t pixel_encoding = 0;
	enum scanning_type scan_type = SCANNING_TYPE_NODATA;
	enum dc_aspect_ratio aspect = ASPECT_RATIO_NO_DATA;
	bool itc = false;
	uint8_t itc_value = 0;
	uint8_t cn0_cn1 = 0;
	unsigned int cn0_cn1_value = 0;
	uint8_t *check_sum = NULL;
	uint8_t byte_index = 0;
	union hdmi_info_packet hdmi_info;
	union display_content_support support = {0};
	unsigned int vic = pipe_ctx->stream->timing.vic;
	enum dc_timing_3d_format format;

	memset(&hdmi_info, 0, sizeof(union hdmi_info_packet));

	color_space = pipe_ctx->stream->output_color_space;
	if (color_space == COLOR_SPACE_UNKNOWN)
		color_space = (stream->timing.pixel_encoding == PIXEL_ENCODING_RGB) ?
			COLOR_SPACE_SRGB:COLOR_SPACE_YCBCR709;

	/* Initialize header */
	hdmi_info.bits.header.info_frame_type = HDMI_INFOFRAME_TYPE_AVI;
	/* InfoFrameVersion_3 is defined by CEA861F (Section 6.4), but shall
	* not be used in HDMI 2.0 (Section 10.1) */
	hdmi_info.bits.header.version = 2;
	hdmi_info.bits.header.length = HDMI_AVI_INFOFRAME_SIZE;

	/*
	 * IDO-defined (Y2,Y1,Y0 = 1,1,1) shall not be used by devices built
	 * according to HDMI 2.0 spec (Section 10.1)
	 */

	switch (stream->timing.pixel_encoding) {
	case PIXEL_ENCODING_YCBCR422:
		pixel_encoding = 1;
		break;

	case PIXEL_ENCODING_YCBCR444:
		pixel_encoding = 2;
		break;
	case PIXEL_ENCODING_YCBCR420:
		pixel_encoding = 3;
		break;

	case PIXEL_ENCODING_RGB:
	default:
		pixel_encoding = 0;
	}

	/* Y0_Y1_Y2 : The pixel encoding */
	/* H14b AVI InfoFrame has extension on Y-field from 2 bits to 3 bits */
	hdmi_info.bits.Y0_Y1_Y2 = pixel_encoding;

	/* A0 = 1 Active Format Information valid */
	hdmi_info.bits.A0 = ACTIVE_FORMAT_VALID;

	/* B0, B1 = 3; Bar info data is valid */
	hdmi_info.bits.B0_B1 = BAR_INFO_BOTH_VALID;

	hdmi_info.bits.SC0_SC1 = PICTURE_SCALING_UNIFORM;

	/* S0, S1 : Underscan / Overscan */
	/* TODO: un-hardcode scan type */
	scan_type = SCANNING_TYPE_UNDERSCAN;
	hdmi_info.bits.S0_S1 = scan_type;

	/* C0, C1 : Colorimetry */
	if (color_space == COLOR_SPACE_YCBCR709 ||
			color_space == COLOR_SPACE_YCBCR709_LIMITED)
		hdmi_info.bits.C0_C1 = COLORIMETRY_ITU709;
	else if (color_space == COLOR_SPACE_YCBCR601 ||
			color_space == COLOR_SPACE_YCBCR601_LIMITED)
		hdmi_info.bits.C0_C1 = COLORIMETRY_ITU601;
	else {
		hdmi_info.bits.C0_C1 = COLORIMETRY_NO_DATA;
	}
	if (color_space == COLOR_SPACE_2020_RGB_FULLRANGE ||
			color_space == COLOR_SPACE_2020_RGB_LIMITEDRANGE ||
			color_space == COLOR_SPACE_2020_YCBCR) {
		hdmi_info.bits.EC0_EC2 = COLORIMETRYEX_BT2020RGBYCBCR;
		hdmi_info.bits.C0_C1   = COLORIMETRY_EXTENDED;
	} else if (color_space == COLOR_SPACE_ADOBERGB) {
		hdmi_info.bits.EC0_EC2 = COLORIMETRYEX_ADOBERGB;
		hdmi_info.bits.C0_C1   = COLORIMETRY_EXTENDED;
	}

	/* TODO: un-hardcode aspect ratio */
	aspect = stream->timing.aspect_ratio;

	switch (aspect) {
	case ASPECT_RATIO_4_3:
	case ASPECT_RATIO_16_9:
		hdmi_info.bits.M0_M1 = aspect;
		break;

	case ASPECT_RATIO_NO_DATA:
	case ASPECT_RATIO_64_27:
	case ASPECT_RATIO_256_135:
	default:
		hdmi_info.bits.M0_M1 = 0;
	}

	/* Active Format Aspect ratio - same as Picture Aspect Ratio. */
	hdmi_info.bits.R0_R3 = ACTIVE_FORMAT_ASPECT_RATIO_SAME_AS_PICTURE;

	/* TODO: un-hardcode cn0_cn1 and itc */

	cn0_cn1 = 0;
	cn0_cn1_value = 0;

	itc = true;
	itc_value = 1;

	support = stream->content_support;

	if (itc) {
		if (!support.bits.valid_content_type) {
			cn0_cn1_value = 0;
		} else {
			if (cn0_cn1 == DISPLAY_CONTENT_TYPE_GRAPHICS) {
				if (support.bits.graphics_content == 1) {
					cn0_cn1_value = 0;
				}
			} else if (cn0_cn1 == DISPLAY_CONTENT_TYPE_PHOTO) {
				if (support.bits.photo_content == 1) {
					cn0_cn1_value = 1;
				} else {
					cn0_cn1_value = 0;
					itc_value = 0;
				}
			} else if (cn0_cn1 == DISPLAY_CONTENT_TYPE_CINEMA) {
				if (support.bits.cinema_content == 1) {
					cn0_cn1_value = 2;
				} else {
					cn0_cn1_value = 0;
					itc_value = 0;
				}
			} else if (cn0_cn1 == DISPLAY_CONTENT_TYPE_GAME) {
				if (support.bits.game_content == 1) {
					cn0_cn1_value = 3;
				} else {
					cn0_cn1_value = 0;
					itc_value = 0;
				}
			}
		}
		hdmi_info.bits.CN0_CN1 = cn0_cn1_value;
		hdmi_info.bits.ITC = itc_value;
	}

	/* TODO : We should handle YCC quantization */
	/* but we do not have matrix calculation */
	if (stream->qs_bit == 1 &&
			stream->qy_bit == 1) {
		if (color_space == COLOR_SPACE_SRGB ||
			color_space == COLOR_SPACE_2020_RGB_FULLRANGE) {
			hdmi_info.bits.Q0_Q1   = RGB_QUANTIZATION_FULL_RANGE;
			hdmi_info.bits.YQ0_YQ1 = YYC_QUANTIZATION_FULL_RANGE;
		} else if (color_space == COLOR_SPACE_SRGB_LIMITED ||
					color_space == COLOR_SPACE_2020_RGB_LIMITEDRANGE) {
			hdmi_info.bits.Q0_Q1   = RGB_QUANTIZATION_LIMITED_RANGE;
			hdmi_info.bits.YQ0_YQ1 = YYC_QUANTIZATION_LIMITED_RANGE;
		} else {
			hdmi_info.bits.Q0_Q1   = RGB_QUANTIZATION_DEFAULT_RANGE;
			hdmi_info.bits.YQ0_YQ1 = YYC_QUANTIZATION_LIMITED_RANGE;
		}
	} else {
		hdmi_info.bits.Q0_Q1   = RGB_QUANTIZATION_DEFAULT_RANGE;
		hdmi_info.bits.YQ0_YQ1   = YYC_QUANTIZATION_LIMITED_RANGE;
	}

	///VIC
	format = stream->timing.timing_3d_format;
	/*todo, add 3DStereo support*/
	if (format != TIMING_3D_FORMAT_NONE) {
		// Based on HDMI specs hdmi vic needs to be converted to cea vic when 3D is enabled
		switch (pipe_ctx->stream->timing.hdmi_vic) {
		case 1:
			vic = 95;
			break;
		case 2:
			vic = 94;
			break;
		case 3:
			vic = 93;
			break;
		case 4:
			vic = 98;
			break;
		default:
			break;
		}
	}
	/* If VIC >= 128, the Source shall use AVI InfoFrame Version 3*/
	hdmi_info.bits.VIC0_VIC7 = vic;
	if (vic >= 128)
		hdmi_info.bits.header.version = 3;
	/* If (C1, C0)=(1, 1) and (EC2, EC1, EC0)=(1, 1, 1),
	 * the Source shall use 20 AVI InfoFrame Version 4
	 */
	if (hdmi_info.bits.C0_C1 == COLORIMETRY_EXTENDED &&
			hdmi_info.bits.EC0_EC2 == COLORIMETRYEX_RESERVED) {
		hdmi_info.bits.header.version = 4;
		hdmi_info.bits.header.length = 14;
	}

	/* pixel repetition
	 * PR0 - PR3 start from 0 whereas pHwPathMode->mode.timing.flags.pixel
	 * repetition start from 1 */
	hdmi_info.bits.PR0_PR3 = 0;

	/* Bar Info
	 * barTop:    Line Number of End of Top Bar.
	 * barBottom: Line Number of Start of Bottom Bar.
	 * barLeft:   Pixel Number of End of Left Bar.
	 * barRight:  Pixel Number of Start of Right Bar. */
	hdmi_info.bits.bar_top = stream->timing.v_border_top;
	hdmi_info.bits.bar_bottom = (stream->timing.v_total
			- stream->timing.v_border_bottom + 1);
	hdmi_info.bits.bar_left  = stream->timing.h_border_left;
	hdmi_info.bits.bar_right = (stream->timing.h_total
			- stream->timing.h_border_right + 1);

    /* Additional Colorimetry Extension
     * Used in conduction with C0-C1 and EC0-EC2
     * 0 = DCI-P3 RGB (D65)
     * 1 = DCI-P3 RGB (theater)
     */
	hdmi_info.bits.ACE0_ACE3 = 0;

	/* check_sum - Calculate AFMT_AVI_INFO0 ~ AFMT_AVI_INFO3 */
	check_sum = &hdmi_info.packet_raw_data.sb[0];

	*check_sum = HDMI_INFOFRAME_TYPE_AVI + hdmi_info.bits.header.length + hdmi_info.bits.header.version;

	for (byte_index = 1; byte_index <= hdmi_info.bits.header.length; byte_index++)
		*check_sum += hdmi_info.packet_raw_data.sb[byte_index];

	/* one byte complement */
	*check_sum = (uint8_t) (0x100 - *check_sum);

	/* Store in hw_path_mode */
	info_packet->hb0 = hdmi_info.packet_raw_data.hb0;
	info_packet->hb1 = hdmi_info.packet_raw_data.hb1;
	info_packet->hb2 = hdmi_info.packet_raw_data.hb2;

	for (byte_index = 0; byte_index < sizeof(hdmi_info.packet_raw_data.sb); byte_index++)
		info_packet->sb[byte_index] = hdmi_info.packet_raw_data.sb[byte_index];

	info_packet->valid = true;
}