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
typedef  enum hdmi_spd_sdi { ____Placeholder_hdmi_spd_sdi } hdmi_spd_sdi ;

/* Variables and functions */
#define  HDMI_SPD_SDI_BD 141 
#define  HDMI_SPD_SDI_DSC 140 
#define  HDMI_SPD_SDI_DSTB 139 
#define  HDMI_SPD_SDI_DVC 138 
#define  HDMI_SPD_SDI_DVDP 137 
#define  HDMI_SPD_SDI_DVHS 136 
#define  HDMI_SPD_SDI_GAME 135 
#define  HDMI_SPD_SDI_HDDVD 134 
#define  HDMI_SPD_SDI_HDDVR 133 
#define  HDMI_SPD_SDI_PC 132 
#define  HDMI_SPD_SDI_PMP 131 
#define  HDMI_SPD_SDI_SACD 130 
#define  HDMI_SPD_SDI_UNKNOWN 129 
#define  HDMI_SPD_SDI_VCD 128 

__attribute__((used)) static const char *hdmi_spd_sdi_get_name(enum hdmi_spd_sdi sdi)
{
	if (sdi < 0 || sdi > 0xff)
		return "Invalid";
	switch (sdi) {
	case HDMI_SPD_SDI_UNKNOWN:
		return "Unknown";
	case HDMI_SPD_SDI_DSTB:
		return "Digital STB";
	case HDMI_SPD_SDI_DVDP:
		return "DVD Player";
	case HDMI_SPD_SDI_DVHS:
		return "D-VHS";
	case HDMI_SPD_SDI_HDDVR:
		return "HDD Videorecorder";
	case HDMI_SPD_SDI_DVC:
		return "DVC";
	case HDMI_SPD_SDI_DSC:
		return "DSC";
	case HDMI_SPD_SDI_VCD:
		return "Video CD";
	case HDMI_SPD_SDI_GAME:
		return "Game";
	case HDMI_SPD_SDI_PC:
		return "PC General";
	case HDMI_SPD_SDI_BD:
		return "Blu-Ray Disc (BD)";
	case HDMI_SPD_SDI_SACD:
		return "Super Audio CD";
	case HDMI_SPD_SDI_HDDVD:
		return "HD DVD";
	case HDMI_SPD_SDI_PMP:
		return "PMP";
	}
	return "Reserved";
}