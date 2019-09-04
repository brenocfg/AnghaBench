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
typedef  enum intel_display_power_domain { ____Placeholder_intel_display_power_domain } intel_display_power_domain ;

/* Variables and functions */
 int /*<<< orphan*/  MISSING_CASE (int) ; 
#define  POWER_DOMAIN_AUDIO 172 
#define  POWER_DOMAIN_AUX_A 171 
#define  POWER_DOMAIN_AUX_B 170 
#define  POWER_DOMAIN_AUX_C 169 
#define  POWER_DOMAIN_AUX_D 168 
#define  POWER_DOMAIN_AUX_E 167 
#define  POWER_DOMAIN_AUX_F 166 
#define  POWER_DOMAIN_AUX_IO_A 165 
#define  POWER_DOMAIN_AUX_TBT1 164 
#define  POWER_DOMAIN_AUX_TBT2 163 
#define  POWER_DOMAIN_AUX_TBT3 162 
#define  POWER_DOMAIN_AUX_TBT4 161 
#define  POWER_DOMAIN_GMBUS 160 
#define  POWER_DOMAIN_GT_IRQ 159 
#define  POWER_DOMAIN_INIT 158 
#define  POWER_DOMAIN_MODESET 157 
#define  POWER_DOMAIN_PIPE_A 156 
#define  POWER_DOMAIN_PIPE_A_PANEL_FITTER 155 
#define  POWER_DOMAIN_PIPE_B 154 
#define  POWER_DOMAIN_PIPE_B_PANEL_FITTER 153 
#define  POWER_DOMAIN_PIPE_C 152 
#define  POWER_DOMAIN_PIPE_C_PANEL_FITTER 151 
#define  POWER_DOMAIN_PLLS 150 
#define  POWER_DOMAIN_PORT_CRT 149 
#define  POWER_DOMAIN_PORT_DDI_A_IO 148 
#define  POWER_DOMAIN_PORT_DDI_A_LANES 147 
#define  POWER_DOMAIN_PORT_DDI_B_IO 146 
#define  POWER_DOMAIN_PORT_DDI_B_LANES 145 
#define  POWER_DOMAIN_PORT_DDI_C_IO 144 
#define  POWER_DOMAIN_PORT_DDI_C_LANES 143 
#define  POWER_DOMAIN_PORT_DDI_D_IO 142 
#define  POWER_DOMAIN_PORT_DDI_D_LANES 141 
#define  POWER_DOMAIN_PORT_DDI_E_IO 140 
#define  POWER_DOMAIN_PORT_DDI_E_LANES 139 
#define  POWER_DOMAIN_PORT_DDI_F_IO 138 
#define  POWER_DOMAIN_PORT_DDI_F_LANES 137 
#define  POWER_DOMAIN_PORT_DSI 136 
#define  POWER_DOMAIN_PORT_OTHER 135 
#define  POWER_DOMAIN_TRANSCODER_A 134 
#define  POWER_DOMAIN_TRANSCODER_B 133 
#define  POWER_DOMAIN_TRANSCODER_C 132 
#define  POWER_DOMAIN_TRANSCODER_DSI_A 131 
#define  POWER_DOMAIN_TRANSCODER_DSI_C 130 
#define  POWER_DOMAIN_TRANSCODER_EDP 129 
#define  POWER_DOMAIN_VGA 128 

const char *
intel_display_power_domain_str(enum intel_display_power_domain domain)
{
	switch (domain) {
	case POWER_DOMAIN_PIPE_A:
		return "PIPE_A";
	case POWER_DOMAIN_PIPE_B:
		return "PIPE_B";
	case POWER_DOMAIN_PIPE_C:
		return "PIPE_C";
	case POWER_DOMAIN_PIPE_A_PANEL_FITTER:
		return "PIPE_A_PANEL_FITTER";
	case POWER_DOMAIN_PIPE_B_PANEL_FITTER:
		return "PIPE_B_PANEL_FITTER";
	case POWER_DOMAIN_PIPE_C_PANEL_FITTER:
		return "PIPE_C_PANEL_FITTER";
	case POWER_DOMAIN_TRANSCODER_A:
		return "TRANSCODER_A";
	case POWER_DOMAIN_TRANSCODER_B:
		return "TRANSCODER_B";
	case POWER_DOMAIN_TRANSCODER_C:
		return "TRANSCODER_C";
	case POWER_DOMAIN_TRANSCODER_EDP:
		return "TRANSCODER_EDP";
	case POWER_DOMAIN_TRANSCODER_DSI_A:
		return "TRANSCODER_DSI_A";
	case POWER_DOMAIN_TRANSCODER_DSI_C:
		return "TRANSCODER_DSI_C";
	case POWER_DOMAIN_PORT_DDI_A_LANES:
		return "PORT_DDI_A_LANES";
	case POWER_DOMAIN_PORT_DDI_B_LANES:
		return "PORT_DDI_B_LANES";
	case POWER_DOMAIN_PORT_DDI_C_LANES:
		return "PORT_DDI_C_LANES";
	case POWER_DOMAIN_PORT_DDI_D_LANES:
		return "PORT_DDI_D_LANES";
	case POWER_DOMAIN_PORT_DDI_E_LANES:
		return "PORT_DDI_E_LANES";
	case POWER_DOMAIN_PORT_DDI_F_LANES:
		return "PORT_DDI_F_LANES";
	case POWER_DOMAIN_PORT_DDI_A_IO:
		return "PORT_DDI_A_IO";
	case POWER_DOMAIN_PORT_DDI_B_IO:
		return "PORT_DDI_B_IO";
	case POWER_DOMAIN_PORT_DDI_C_IO:
		return "PORT_DDI_C_IO";
	case POWER_DOMAIN_PORT_DDI_D_IO:
		return "PORT_DDI_D_IO";
	case POWER_DOMAIN_PORT_DDI_E_IO:
		return "PORT_DDI_E_IO";
	case POWER_DOMAIN_PORT_DDI_F_IO:
		return "PORT_DDI_F_IO";
	case POWER_DOMAIN_PORT_DSI:
		return "PORT_DSI";
	case POWER_DOMAIN_PORT_CRT:
		return "PORT_CRT";
	case POWER_DOMAIN_PORT_OTHER:
		return "PORT_OTHER";
	case POWER_DOMAIN_VGA:
		return "VGA";
	case POWER_DOMAIN_AUDIO:
		return "AUDIO";
	case POWER_DOMAIN_PLLS:
		return "PLLS";
	case POWER_DOMAIN_AUX_A:
		return "AUX_A";
	case POWER_DOMAIN_AUX_B:
		return "AUX_B";
	case POWER_DOMAIN_AUX_C:
		return "AUX_C";
	case POWER_DOMAIN_AUX_D:
		return "AUX_D";
	case POWER_DOMAIN_AUX_E:
		return "AUX_E";
	case POWER_DOMAIN_AUX_F:
		return "AUX_F";
	case POWER_DOMAIN_AUX_IO_A:
		return "AUX_IO_A";
	case POWER_DOMAIN_AUX_TBT1:
		return "AUX_TBT1";
	case POWER_DOMAIN_AUX_TBT2:
		return "AUX_TBT2";
	case POWER_DOMAIN_AUX_TBT3:
		return "AUX_TBT3";
	case POWER_DOMAIN_AUX_TBT4:
		return "AUX_TBT4";
	case POWER_DOMAIN_GMBUS:
		return "GMBUS";
	case POWER_DOMAIN_INIT:
		return "INIT";
	case POWER_DOMAIN_MODESET:
		return "MODESET";
	case POWER_DOMAIN_GT_IRQ:
		return "GT_IRQ";
	default:
		MISSING_CASE(domain);
		return "?";
	}
}