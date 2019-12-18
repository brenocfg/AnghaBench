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
typedef  enum hdmi_audio_coding_type { ____Placeholder_hdmi_audio_coding_type } hdmi_audio_coding_type ;

/* Variables and functions */
#define  HDMI_AUDIO_CODING_TYPE_AAC_LC 143 
#define  HDMI_AUDIO_CODING_TYPE_AC3 142 
#define  HDMI_AUDIO_CODING_TYPE_ATRAC 141 
#define  HDMI_AUDIO_CODING_TYPE_CXT 140 
#define  HDMI_AUDIO_CODING_TYPE_DSD 139 
#define  HDMI_AUDIO_CODING_TYPE_DST 138 
#define  HDMI_AUDIO_CODING_TYPE_DTS 137 
#define  HDMI_AUDIO_CODING_TYPE_DTS_HD 136 
#define  HDMI_AUDIO_CODING_TYPE_EAC3 135 
#define  HDMI_AUDIO_CODING_TYPE_MLP 134 
#define  HDMI_AUDIO_CODING_TYPE_MP3 133 
#define  HDMI_AUDIO_CODING_TYPE_MPEG1 132 
#define  HDMI_AUDIO_CODING_TYPE_MPEG2 131 
#define  HDMI_AUDIO_CODING_TYPE_PCM 130 
#define  HDMI_AUDIO_CODING_TYPE_STREAM 129 
#define  HDMI_AUDIO_CODING_TYPE_WMA_PRO 128 

__attribute__((used)) static const char *
hdmi_audio_coding_type_get_name(enum hdmi_audio_coding_type coding_type)
{
	switch (coding_type) {
	case HDMI_AUDIO_CODING_TYPE_STREAM:
		return "Refer to Stream Header";
	case HDMI_AUDIO_CODING_TYPE_PCM:
		return "PCM";
	case HDMI_AUDIO_CODING_TYPE_AC3:
		return "AC-3";
	case HDMI_AUDIO_CODING_TYPE_MPEG1:
		return "MPEG1";
	case HDMI_AUDIO_CODING_TYPE_MP3:
		return "MP3";
	case HDMI_AUDIO_CODING_TYPE_MPEG2:
		return "MPEG2";
	case HDMI_AUDIO_CODING_TYPE_AAC_LC:
		return "AAC";
	case HDMI_AUDIO_CODING_TYPE_DTS:
		return "DTS";
	case HDMI_AUDIO_CODING_TYPE_ATRAC:
		return "ATRAC";
	case HDMI_AUDIO_CODING_TYPE_DSD:
		return "One Bit Audio";
	case HDMI_AUDIO_CODING_TYPE_EAC3:
		return "Dolby Digital +";
	case HDMI_AUDIO_CODING_TYPE_DTS_HD:
		return "DTS-HD";
	case HDMI_AUDIO_CODING_TYPE_MLP:
		return "MAT (MLP)";
	case HDMI_AUDIO_CODING_TYPE_DST:
		return "DST";
	case HDMI_AUDIO_CODING_TYPE_WMA_PRO:
		return "WMA PRO";
	case HDMI_AUDIO_CODING_TYPE_CXT:
		return "Refer to CXT";
	}
	return "Invalid";
}