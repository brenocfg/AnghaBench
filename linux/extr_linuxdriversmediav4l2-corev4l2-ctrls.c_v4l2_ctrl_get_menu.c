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
typedef  int u32 ;

/* Variables and functions */
#define  V4L2_CID_AUTO_FOCUS_RANGE 184 
#define  V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE 183 
#define  V4L2_CID_COLORFX 182 
#define  V4L2_CID_DETECT_MD_MODE 181 
#define  V4L2_CID_DV_RX_IT_CONTENT_TYPE 180 
#define  V4L2_CID_DV_RX_RGB_RANGE 179 
#define  V4L2_CID_DV_TX_IT_CONTENT_TYPE 178 
#define  V4L2_CID_DV_TX_MODE 177 
#define  V4L2_CID_DV_TX_RGB_RANGE 176 
#define  V4L2_CID_EXPOSURE_AUTO 175 
#define  V4L2_CID_EXPOSURE_METERING 174 
#define  V4L2_CID_FLASH_LED_MODE 173 
#define  V4L2_CID_FLASH_STROBE_SOURCE 172 
#define  V4L2_CID_ISO_SENSITIVITY_AUTO 171 
#define  V4L2_CID_JPEG_CHROMA_SUBSAMPLING 170 
#define  V4L2_CID_MPEG_AUDIO_AC3_BITRATE 169 
#define  V4L2_CID_MPEG_AUDIO_CRC 168 
#define  V4L2_CID_MPEG_AUDIO_DEC_MULTILINGUAL_PLAYBACK 167 
#define  V4L2_CID_MPEG_AUDIO_DEC_PLAYBACK 166 
#define  V4L2_CID_MPEG_AUDIO_EMPHASIS 165 
#define  V4L2_CID_MPEG_AUDIO_ENCODING 164 
#define  V4L2_CID_MPEG_AUDIO_L1_BITRATE 163 
#define  V4L2_CID_MPEG_AUDIO_L2_BITRATE 162 
#define  V4L2_CID_MPEG_AUDIO_L3_BITRATE 161 
#define  V4L2_CID_MPEG_AUDIO_MODE 160 
#define  V4L2_CID_MPEG_AUDIO_MODE_EXTENSION 159 
#define  V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ 158 
#define  V4L2_CID_MPEG_STREAM_TYPE 157 
#define  V4L2_CID_MPEG_STREAM_VBI_FMT 156 
#define  V4L2_CID_MPEG_VIDEO_ASPECT 155 
#define  V4L2_CID_MPEG_VIDEO_BITRATE_MODE 154 
#define  V4L2_CID_MPEG_VIDEO_ENCODING 153 
#define  V4L2_CID_MPEG_VIDEO_H264_ENTROPY_MODE 152 
#define  V4L2_CID_MPEG_VIDEO_H264_FMO_MAP_TYPE 151 
#define  V4L2_CID_MPEG_VIDEO_H264_LEVEL 150 
#define  V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_MODE 149 
#define  V4L2_CID_MPEG_VIDEO_H264_PROFILE 148 
#define  V4L2_CID_MPEG_VIDEO_H264_SEI_FP_ARRANGEMENT_TYPE 147 
#define  V4L2_CID_MPEG_VIDEO_H264_VUI_SAR_IDC 146 
#define  V4L2_CID_MPEG_VIDEO_HEADER_MODE 145 
#define  V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_TYPE 144 
#define  V4L2_CID_MPEG_VIDEO_HEVC_LEVEL 143 
#define  V4L2_CID_MPEG_VIDEO_HEVC_LOOP_FILTER_MODE 142 
#define  V4L2_CID_MPEG_VIDEO_HEVC_PROFILE 141 
#define  V4L2_CID_MPEG_VIDEO_HEVC_REFRESH_TYPE 140 
#define  V4L2_CID_MPEG_VIDEO_HEVC_SIZE_OF_LENGTH_FIELD 139 
#define  V4L2_CID_MPEG_VIDEO_HEVC_TIER 138 
#define  V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL 137 
#define  V4L2_CID_MPEG_VIDEO_MPEG4_PROFILE 136 
#define  V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MODE 135 
#define  V4L2_CID_MPEG_VIDEO_VP8_PROFILE 134 
#define  V4L2_CID_MPEG_VIDEO_VP9_PROFILE 133 
#define  V4L2_CID_MPEG_VIDEO_VPX_GOLDEN_FRAME_SEL 132 
#define  V4L2_CID_POWER_LINE_FREQUENCY 131 
#define  V4L2_CID_SCENE_MODE 130 
#define  V4L2_CID_TUNE_DEEMPHASIS 129 
#define  V4L2_CID_TUNE_PREEMPHASIS 128 

const char * const *v4l2_ctrl_get_menu(u32 id)
{
	static const char * const mpeg_audio_sampling_freq[] = {
		"44.1 kHz",
		"48 kHz",
		"32 kHz",
		NULL
	};
	static const char * const mpeg_audio_encoding[] = {
		"MPEG-1/2 Layer I",
		"MPEG-1/2 Layer II",
		"MPEG-1/2 Layer III",
		"MPEG-2/4 AAC",
		"AC-3",
		NULL
	};
	static const char * const mpeg_audio_l1_bitrate[] = {
		"32 kbps",
		"64 kbps",
		"96 kbps",
		"128 kbps",
		"160 kbps",
		"192 kbps",
		"224 kbps",
		"256 kbps",
		"288 kbps",
		"320 kbps",
		"352 kbps",
		"384 kbps",
		"416 kbps",
		"448 kbps",
		NULL
	};
	static const char * const mpeg_audio_l2_bitrate[] = {
		"32 kbps",
		"48 kbps",
		"56 kbps",
		"64 kbps",
		"80 kbps",
		"96 kbps",
		"112 kbps",
		"128 kbps",
		"160 kbps",
		"192 kbps",
		"224 kbps",
		"256 kbps",
		"320 kbps",
		"384 kbps",
		NULL
	};
	static const char * const mpeg_audio_l3_bitrate[] = {
		"32 kbps",
		"40 kbps",
		"48 kbps",
		"56 kbps",
		"64 kbps",
		"80 kbps",
		"96 kbps",
		"112 kbps",
		"128 kbps",
		"160 kbps",
		"192 kbps",
		"224 kbps",
		"256 kbps",
		"320 kbps",
		NULL
	};
	static const char * const mpeg_audio_ac3_bitrate[] = {
		"32 kbps",
		"40 kbps",
		"48 kbps",
		"56 kbps",
		"64 kbps",
		"80 kbps",
		"96 kbps",
		"112 kbps",
		"128 kbps",
		"160 kbps",
		"192 kbps",
		"224 kbps",
		"256 kbps",
		"320 kbps",
		"384 kbps",
		"448 kbps",
		"512 kbps",
		"576 kbps",
		"640 kbps",
		NULL
	};
	static const char * const mpeg_audio_mode[] = {
		"Stereo",
		"Joint Stereo",
		"Dual",
		"Mono",
		NULL
	};
	static const char * const mpeg_audio_mode_extension[] = {
		"Bound 4",
		"Bound 8",
		"Bound 12",
		"Bound 16",
		NULL
	};
	static const char * const mpeg_audio_emphasis[] = {
		"No Emphasis",
		"50/15 us",
		"CCITT J17",
		NULL
	};
	static const char * const mpeg_audio_crc[] = {
		"No CRC",
		"16-bit CRC",
		NULL
	};
	static const char * const mpeg_audio_dec_playback[] = {
		"Auto",
		"Stereo",
		"Left",
		"Right",
		"Mono",
		"Swapped Stereo",
		NULL
	};
	static const char * const mpeg_video_encoding[] = {
		"MPEG-1",
		"MPEG-2",
		"MPEG-4 AVC",
		NULL
	};
	static const char * const mpeg_video_aspect[] = {
		"1x1",
		"4x3",
		"16x9",
		"2.21x1",
		NULL
	};
	static const char * const mpeg_video_bitrate_mode[] = {
		"Variable Bitrate",
		"Constant Bitrate",
		NULL
	};
	static const char * const mpeg_stream_type[] = {
		"MPEG-2 Program Stream",
		"MPEG-2 Transport Stream",
		"MPEG-1 System Stream",
		"MPEG-2 DVD-compatible Stream",
		"MPEG-1 VCD-compatible Stream",
		"MPEG-2 SVCD-compatible Stream",
		NULL
	};
	static const char * const mpeg_stream_vbi_fmt[] = {
		"No VBI",
		"Private Packet, IVTV Format",
		NULL
	};
	static const char * const camera_power_line_frequency[] = {
		"Disabled",
		"50 Hz",
		"60 Hz",
		"Auto",
		NULL
	};
	static const char * const camera_exposure_auto[] = {
		"Auto Mode",
		"Manual Mode",
		"Shutter Priority Mode",
		"Aperture Priority Mode",
		NULL
	};
	static const char * const camera_exposure_metering[] = {
		"Average",
		"Center Weighted",
		"Spot",
		"Matrix",
		NULL
	};
	static const char * const camera_auto_focus_range[] = {
		"Auto",
		"Normal",
		"Macro",
		"Infinity",
		NULL
	};
	static const char * const colorfx[] = {
		"None",
		"Black & White",
		"Sepia",
		"Negative",
		"Emboss",
		"Sketch",
		"Sky Blue",
		"Grass Green",
		"Skin Whiten",
		"Vivid",
		"Aqua",
		"Art Freeze",
		"Silhouette",
		"Solarization",
		"Antique",
		"Set Cb/Cr",
		NULL
	};
	static const char * const auto_n_preset_white_balance[] = {
		"Manual",
		"Auto",
		"Incandescent",
		"Fluorescent",
		"Fluorescent H",
		"Horizon",
		"Daylight",
		"Flash",
		"Cloudy",
		"Shade",
		NULL,
	};
	static const char * const camera_iso_sensitivity_auto[] = {
		"Manual",
		"Auto",
		NULL
	};
	static const char * const scene_mode[] = {
		"None",
		"Backlight",
		"Beach/Snow",
		"Candle Light",
		"Dusk/Dawn",
		"Fall Colors",
		"Fireworks",
		"Landscape",
		"Night",
		"Party/Indoor",
		"Portrait",
		"Sports",
		"Sunset",
		"Text",
		NULL
	};
	static const char * const tune_emphasis[] = {
		"None",
		"50 Microseconds",
		"75 Microseconds",
		NULL,
	};
	static const char * const header_mode[] = {
		"Separate Buffer",
		"Joined With 1st Frame",
		NULL,
	};
	static const char * const multi_slice[] = {
		"Single",
		"Max Macroblocks",
		"Max Bytes",
		NULL,
	};
	static const char * const entropy_mode[] = {
		"CAVLC",
		"CABAC",
		NULL,
	};
	static const char * const mpeg_h264_level[] = {
		"1",
		"1b",
		"1.1",
		"1.2",
		"1.3",
		"2",
		"2.1",
		"2.2",
		"3",
		"3.1",
		"3.2",
		"4",
		"4.1",
		"4.2",
		"5",
		"5.1",
		NULL,
	};
	static const char * const h264_loop_filter[] = {
		"Enabled",
		"Disabled",
		"Disabled at Slice Boundary",
		NULL,
	};
	static const char * const h264_profile[] = {
		"Baseline",
		"Constrained Baseline",
		"Main",
		"Extended",
		"High",
		"High 10",
		"High 422",
		"High 444 Predictive",
		"High 10 Intra",
		"High 422 Intra",
		"High 444 Intra",
		"CAVLC 444 Intra",
		"Scalable Baseline",
		"Scalable High",
		"Scalable High Intra",
		"Stereo High",
		"Multiview High",
		NULL,
	};
	static const char * const vui_sar_idc[] = {
		"Unspecified",
		"1:1",
		"12:11",
		"10:11",
		"16:11",
		"40:33",
		"24:11",
		"20:11",
		"32:11",
		"80:33",
		"18:11",
		"15:11",
		"64:33",
		"160:99",
		"4:3",
		"3:2",
		"2:1",
		"Extended SAR",
		NULL,
	};
	static const char * const h264_fp_arrangement_type[] = {
		"Checkerboard",
		"Column",
		"Row",
		"Side by Side",
		"Top Bottom",
		"Temporal",
		NULL,
	};
	static const char * const h264_fmo_map_type[] = {
		"Interleaved Slices",
		"Scattered Slices",
		"Foreground with Leftover",
		"Box Out",
		"Raster Scan",
		"Wipe Scan",
		"Explicit",
		NULL,
	};
	static const char * const mpeg_mpeg4_level[] = {
		"0",
		"0b",
		"1",
		"2",
		"3",
		"3b",
		"4",
		"5",
		NULL,
	};
	static const char * const mpeg4_profile[] = {
		"Simple",
		"Advanced Simple",
		"Core",
		"Simple Scalable",
		"Advanced Coding Efficiency",
		NULL,
	};

	static const char * const vpx_golden_frame_sel[] = {
		"Use Previous Frame",
		"Use Previous Specific Frame",
		NULL,
	};
	static const char * const vp8_profile[] = {
		"0",
		"1",
		"2",
		"3",
		NULL,
	};
	static const char * const vp9_profile[] = {
		"0",
		"1",
		"2",
		"3",
		NULL,
	};

	static const char * const flash_led_mode[] = {
		"Off",
		"Flash",
		"Torch",
		NULL,
	};
	static const char * const flash_strobe_source[] = {
		"Software",
		"External",
		NULL,
	};

	static const char * const jpeg_chroma_subsampling[] = {
		"4:4:4",
		"4:2:2",
		"4:2:0",
		"4:1:1",
		"4:1:0",
		"Gray",
		NULL,
	};
	static const char * const dv_tx_mode[] = {
		"DVI-D",
		"HDMI",
		NULL,
	};
	static const char * const dv_rgb_range[] = {
		"Automatic",
		"RGB Limited Range (16-235)",
		"RGB Full Range (0-255)",
		NULL,
	};
	static const char * const dv_it_content_type[] = {
		"Graphics",
		"Photo",
		"Cinema",
		"Game",
		"No IT Content",
		NULL,
	};
	static const char * const detect_md_mode[] = {
		"Disabled",
		"Global",
		"Threshold Grid",
		"Region Grid",
		NULL,
	};

	static const char * const hevc_profile[] = {
		"Main",
		"Main Still Picture",
		"Main 10",
		NULL,
	};
	static const char * const hevc_level[] = {
		"1",
		"2",
		"2.1",
		"3",
		"3.1",
		"4",
		"4.1",
		"5",
		"5.1",
		"5.2",
		"6",
		"6.1",
		"6.2",
		NULL,
	};
	static const char * const hevc_hierarchial_coding_type[] = {
		"B",
		"P",
		NULL,
	};
	static const char * const hevc_refresh_type[] = {
		"None",
		"CRA",
		"IDR",
		NULL,
	};
	static const char * const hevc_size_of_length_field[] = {
		"0",
		"1",
		"2",
		"4",
		NULL,
	};
	static const char * const hevc_tier[] = {
		"Main",
		"High",
		NULL,
	};
	static const char * const hevc_loop_filter_mode[] = {
		"Disabled",
		"Enabled",
		"Disabled at slice boundary",
		"NULL",
	};

	switch (id) {
	case V4L2_CID_MPEG_AUDIO_SAMPLING_FREQ:
		return mpeg_audio_sampling_freq;
	case V4L2_CID_MPEG_AUDIO_ENCODING:
		return mpeg_audio_encoding;
	case V4L2_CID_MPEG_AUDIO_L1_BITRATE:
		return mpeg_audio_l1_bitrate;
	case V4L2_CID_MPEG_AUDIO_L2_BITRATE:
		return mpeg_audio_l2_bitrate;
	case V4L2_CID_MPEG_AUDIO_L3_BITRATE:
		return mpeg_audio_l3_bitrate;
	case V4L2_CID_MPEG_AUDIO_AC3_BITRATE:
		return mpeg_audio_ac3_bitrate;
	case V4L2_CID_MPEG_AUDIO_MODE:
		return mpeg_audio_mode;
	case V4L2_CID_MPEG_AUDIO_MODE_EXTENSION:
		return mpeg_audio_mode_extension;
	case V4L2_CID_MPEG_AUDIO_EMPHASIS:
		return mpeg_audio_emphasis;
	case V4L2_CID_MPEG_AUDIO_CRC:
		return mpeg_audio_crc;
	case V4L2_CID_MPEG_AUDIO_DEC_PLAYBACK:
	case V4L2_CID_MPEG_AUDIO_DEC_MULTILINGUAL_PLAYBACK:
		return mpeg_audio_dec_playback;
	case V4L2_CID_MPEG_VIDEO_ENCODING:
		return mpeg_video_encoding;
	case V4L2_CID_MPEG_VIDEO_ASPECT:
		return mpeg_video_aspect;
	case V4L2_CID_MPEG_VIDEO_BITRATE_MODE:
		return mpeg_video_bitrate_mode;
	case V4L2_CID_MPEG_STREAM_TYPE:
		return mpeg_stream_type;
	case V4L2_CID_MPEG_STREAM_VBI_FMT:
		return mpeg_stream_vbi_fmt;
	case V4L2_CID_POWER_LINE_FREQUENCY:
		return camera_power_line_frequency;
	case V4L2_CID_EXPOSURE_AUTO:
		return camera_exposure_auto;
	case V4L2_CID_EXPOSURE_METERING:
		return camera_exposure_metering;
	case V4L2_CID_AUTO_FOCUS_RANGE:
		return camera_auto_focus_range;
	case V4L2_CID_COLORFX:
		return colorfx;
	case V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE:
		return auto_n_preset_white_balance;
	case V4L2_CID_ISO_SENSITIVITY_AUTO:
		return camera_iso_sensitivity_auto;
	case V4L2_CID_SCENE_MODE:
		return scene_mode;
	case V4L2_CID_TUNE_PREEMPHASIS:
		return tune_emphasis;
	case V4L2_CID_TUNE_DEEMPHASIS:
		return tune_emphasis;
	case V4L2_CID_FLASH_LED_MODE:
		return flash_led_mode;
	case V4L2_CID_FLASH_STROBE_SOURCE:
		return flash_strobe_source;
	case V4L2_CID_MPEG_VIDEO_HEADER_MODE:
		return header_mode;
	case V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MODE:
		return multi_slice;
	case V4L2_CID_MPEG_VIDEO_H264_ENTROPY_MODE:
		return entropy_mode;
	case V4L2_CID_MPEG_VIDEO_H264_LEVEL:
		return mpeg_h264_level;
	case V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_MODE:
		return h264_loop_filter;
	case V4L2_CID_MPEG_VIDEO_H264_PROFILE:
		return h264_profile;
	case V4L2_CID_MPEG_VIDEO_H264_VUI_SAR_IDC:
		return vui_sar_idc;
	case V4L2_CID_MPEG_VIDEO_H264_SEI_FP_ARRANGEMENT_TYPE:
		return h264_fp_arrangement_type;
	case V4L2_CID_MPEG_VIDEO_H264_FMO_MAP_TYPE:
		return h264_fmo_map_type;
	case V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL:
		return mpeg_mpeg4_level;
	case V4L2_CID_MPEG_VIDEO_MPEG4_PROFILE:
		return mpeg4_profile;
	case V4L2_CID_MPEG_VIDEO_VPX_GOLDEN_FRAME_SEL:
		return vpx_golden_frame_sel;
	case V4L2_CID_MPEG_VIDEO_VP8_PROFILE:
		return vp8_profile;
	case V4L2_CID_MPEG_VIDEO_VP9_PROFILE:
		return vp9_profile;
	case V4L2_CID_JPEG_CHROMA_SUBSAMPLING:
		return jpeg_chroma_subsampling;
	case V4L2_CID_DV_TX_MODE:
		return dv_tx_mode;
	case V4L2_CID_DV_TX_RGB_RANGE:
	case V4L2_CID_DV_RX_RGB_RANGE:
		return dv_rgb_range;
	case V4L2_CID_DV_TX_IT_CONTENT_TYPE:
	case V4L2_CID_DV_RX_IT_CONTENT_TYPE:
		return dv_it_content_type;
	case V4L2_CID_DETECT_MD_MODE:
		return detect_md_mode;
	case V4L2_CID_MPEG_VIDEO_HEVC_PROFILE:
		return hevc_profile;
	case V4L2_CID_MPEG_VIDEO_HEVC_LEVEL:
		return hevc_level;
	case V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_TYPE:
		return hevc_hierarchial_coding_type;
	case V4L2_CID_MPEG_VIDEO_HEVC_REFRESH_TYPE:
		return hevc_refresh_type;
	case V4L2_CID_MPEG_VIDEO_HEVC_SIZE_OF_LENGTH_FIELD:
		return hevc_size_of_length_field;
	case V4L2_CID_MPEG_VIDEO_HEVC_TIER:
		return hevc_tier;
	case V4L2_CID_MPEG_VIDEO_HEVC_LOOP_FILTER_MODE:
		return hevc_loop_filter_mode;

	default:
		return NULL;
	}
}