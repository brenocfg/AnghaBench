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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  enum signal_type { ____Placeholder_signal_type } signal_type ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_TRANSMITTER_DIGMODE_V5_DP ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_DIGMODE_V5_DP_MST ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_DIGMODE_V5_DVI ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_DIGMODE_V5_HDMI ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_DIGMODE_V5_LVDS ; 
#define  SIGNAL_TYPE_DISPLAY_PORT 134 
#define  SIGNAL_TYPE_DISPLAY_PORT_MST 133 
#define  SIGNAL_TYPE_DVI_DUAL_LINK 132 
#define  SIGNAL_TYPE_DVI_SINGLE_LINK 131 
#define  SIGNAL_TYPE_EDP 130 
#define  SIGNAL_TYPE_HDMI_TYPE_A 129 
#define  SIGNAL_TYPE_LVDS 128 

__attribute__((used)) static uint8_t signal_type_to_atom_dig_mode(enum signal_type s)
{
	uint8_t atom_dig_mode = ATOM_TRANSMITTER_DIGMODE_V5_DP;

	switch (s) {
	case SIGNAL_TYPE_DISPLAY_PORT:
	case SIGNAL_TYPE_EDP:
		atom_dig_mode = ATOM_TRANSMITTER_DIGMODE_V5_DP;
		break;
	case SIGNAL_TYPE_LVDS:
		atom_dig_mode = ATOM_TRANSMITTER_DIGMODE_V5_LVDS;
		break;
	case SIGNAL_TYPE_DVI_SINGLE_LINK:
	case SIGNAL_TYPE_DVI_DUAL_LINK:
		atom_dig_mode = ATOM_TRANSMITTER_DIGMODE_V5_DVI;
		break;
	case SIGNAL_TYPE_HDMI_TYPE_A:
		atom_dig_mode = ATOM_TRANSMITTER_DIGMODE_V5_HDMI;
		break;
	case SIGNAL_TYPE_DISPLAY_PORT_MST:
		atom_dig_mode = ATOM_TRANSMITTER_DIGMODE_V5_DP_MST;
		break;
	default:
		atom_dig_mode = ATOM_TRANSMITTER_DIGMODE_V5_DVI;
		break;
	}

	return atom_dig_mode;
}