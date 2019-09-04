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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  enum signal_type { ____Placeholder_signal_type } signal_type ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_ENCODER_MODE_CRT ; 
 int /*<<< orphan*/  ATOM_ENCODER_MODE_DP ; 
 int /*<<< orphan*/  ATOM_ENCODER_MODE_DP_AUDIO ; 
 int /*<<< orphan*/  ATOM_ENCODER_MODE_DVI ; 
 int /*<<< orphan*/  ATOM_ENCODER_MODE_HDMI ; 
 int /*<<< orphan*/  ATOM_ENCODER_MODE_LVDS ; 
#define  SIGNAL_TYPE_DISPLAY_PORT 136 
#define  SIGNAL_TYPE_DISPLAY_PORT_MST 135 
#define  SIGNAL_TYPE_DVI_DUAL_LINK 134 
#define  SIGNAL_TYPE_DVI_SINGLE_LINK 133 
#define  SIGNAL_TYPE_EDP 132 
#define  SIGNAL_TYPE_HDMI_TYPE_A 131 
#define  SIGNAL_TYPE_LVDS 130 
#define  SIGNAL_TYPE_RGB 129 
#define  SIGNAL_TYPE_VIRTUAL 128 

uint32_t dal_cmd_table_helper_encoder_mode_bp_to_atom(
	enum signal_type s,
	bool enable_dp_audio)
{
	switch (s) {
	case SIGNAL_TYPE_DVI_SINGLE_LINK:
	case SIGNAL_TYPE_DVI_DUAL_LINK:
		return ATOM_ENCODER_MODE_DVI;
	case SIGNAL_TYPE_HDMI_TYPE_A:
		return ATOM_ENCODER_MODE_HDMI;
	case SIGNAL_TYPE_LVDS:
		return ATOM_ENCODER_MODE_LVDS;
	case SIGNAL_TYPE_EDP:
	case SIGNAL_TYPE_DISPLAY_PORT_MST:
	case SIGNAL_TYPE_DISPLAY_PORT:
	case SIGNAL_TYPE_VIRTUAL:
		if (enable_dp_audio)
			return ATOM_ENCODER_MODE_DP_AUDIO;
		else
			return ATOM_ENCODER_MODE_DP;
	case SIGNAL_TYPE_RGB:
		return ATOM_ENCODER_MODE_CRT;
	default:
		return ATOM_ENCODER_MODE_CRT;
	}
}