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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
#define  HDMI_INFOFRAME_TYPE_AVI 131 
#define  HDMI_INFOFRAME_TYPE_SPD 130 
#define  HDMI_INFOFRAME_TYPE_VENDOR 129 
#define  HDMI_PACKET_TYPE_GAMUT_METADATA 128 
 int /*<<< orphan*/  MISSING_CASE (unsigned int) ; 
 int /*<<< orphan*/  VIDEO_DIP_SELECT_AVI ; 
 int /*<<< orphan*/  VIDEO_DIP_SELECT_GAMUT ; 
 int /*<<< orphan*/  VIDEO_DIP_SELECT_SPD ; 
 int /*<<< orphan*/  VIDEO_DIP_SELECT_VENDOR ; 

__attribute__((used)) static u32 g4x_infoframe_index(unsigned int type)
{
	switch (type) {
	case HDMI_PACKET_TYPE_GAMUT_METADATA:
		return VIDEO_DIP_SELECT_GAMUT;
	case HDMI_INFOFRAME_TYPE_AVI:
		return VIDEO_DIP_SELECT_AVI;
	case HDMI_INFOFRAME_TYPE_SPD:
		return VIDEO_DIP_SELECT_SPD;
	case HDMI_INFOFRAME_TYPE_VENDOR:
		return VIDEO_DIP_SELECT_VENDOR;
	default:
		MISSING_CASE(type);
		return 0;
	}
}