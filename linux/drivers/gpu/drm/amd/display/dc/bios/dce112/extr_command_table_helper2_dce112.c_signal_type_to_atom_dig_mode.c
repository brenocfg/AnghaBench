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
 int /*<<< orphan*/  ATOM_TRANSMITTER_DIGMODE_V6_DP ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_DIGMODE_V6_DP_MST ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_DIGMODE_V6_DVI ; 
 int /*<<< orphan*/  ATOM_TRANSMITTER_DIGMODE_V6_HDMI ; 
#define  SIGNAL_TYPE_DISPLAY_PORT 133 
#define  SIGNAL_TYPE_DISPLAY_PORT_MST 132 
#define  SIGNAL_TYPE_DVI_DUAL_LINK 131 
#define  SIGNAL_TYPE_DVI_SINGLE_LINK 130 
#define  SIGNAL_TYPE_EDP 129 
#define  SIGNAL_TYPE_HDMI_TYPE_A 128 

__attribute__((used)) static uint8_t signal_type_to_atom_dig_mode(enum signal_type s)
{
	uint8_t atom_dig_mode = ATOM_TRANSMITTER_DIGMODE_V6_DP;

	switch (s) {
	case SIGNAL_TYPE_DISPLAY_PORT:
	case SIGNAL_TYPE_EDP:
		atom_dig_mode = ATOM_TRANSMITTER_DIGMODE_V6_DP;
		break;
	case SIGNAL_TYPE_DVI_SINGLE_LINK:
	case SIGNAL_TYPE_DVI_DUAL_LINK:
		atom_dig_mode = ATOM_TRANSMITTER_DIGMODE_V6_DVI;
		break;
	case SIGNAL_TYPE_HDMI_TYPE_A:
		atom_dig_mode = ATOM_TRANSMITTER_DIGMODE_V6_HDMI;
		break;
	case SIGNAL_TYPE_DISPLAY_PORT_MST:
		atom_dig_mode = ATOM_TRANSMITTER_DIGMODE_V6_DP_MST;
		break;
	default:
		atom_dig_mode = ATOM_TRANSMITTER_DIGMODE_V6_DVI;
		break;
	}

	return atom_dig_mode;
}