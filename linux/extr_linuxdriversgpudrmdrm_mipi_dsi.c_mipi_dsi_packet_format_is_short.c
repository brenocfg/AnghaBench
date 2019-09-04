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
typedef  int u8 ;

/* Variables and functions */
#define  MIPI_DSI_COLOR_MODE_OFF 147 
#define  MIPI_DSI_COLOR_MODE_ON 146 
#define  MIPI_DSI_DCS_COMPRESSION_MODE 145 
#define  MIPI_DSI_DCS_READ 144 
#define  MIPI_DSI_DCS_SHORT_WRITE 143 
#define  MIPI_DSI_DCS_SHORT_WRITE_PARAM 142 
#define  MIPI_DSI_END_OF_TRANSMISSION 141 
#define  MIPI_DSI_GENERIC_READ_REQUEST_0_PARAM 140 
#define  MIPI_DSI_GENERIC_READ_REQUEST_1_PARAM 139 
#define  MIPI_DSI_GENERIC_READ_REQUEST_2_PARAM 138 
#define  MIPI_DSI_GENERIC_SHORT_WRITE_0_PARAM 137 
#define  MIPI_DSI_GENERIC_SHORT_WRITE_1_PARAM 136 
#define  MIPI_DSI_GENERIC_SHORT_WRITE_2_PARAM 135 
#define  MIPI_DSI_H_SYNC_END 134 
#define  MIPI_DSI_H_SYNC_START 133 
#define  MIPI_DSI_SET_MAXIMUM_RETURN_PACKET_SIZE 132 
#define  MIPI_DSI_SHUTDOWN_PERIPHERAL 131 
#define  MIPI_DSI_TURN_ON_PERIPHERAL 130 
#define  MIPI_DSI_V_SYNC_END 129 
#define  MIPI_DSI_V_SYNC_START 128 

bool mipi_dsi_packet_format_is_short(u8 type)
{
	switch (type) {
	case MIPI_DSI_V_SYNC_START:
	case MIPI_DSI_V_SYNC_END:
	case MIPI_DSI_H_SYNC_START:
	case MIPI_DSI_H_SYNC_END:
	case MIPI_DSI_END_OF_TRANSMISSION:
	case MIPI_DSI_COLOR_MODE_OFF:
	case MIPI_DSI_COLOR_MODE_ON:
	case MIPI_DSI_SHUTDOWN_PERIPHERAL:
	case MIPI_DSI_TURN_ON_PERIPHERAL:
	case MIPI_DSI_GENERIC_SHORT_WRITE_0_PARAM:
	case MIPI_DSI_GENERIC_SHORT_WRITE_1_PARAM:
	case MIPI_DSI_GENERIC_SHORT_WRITE_2_PARAM:
	case MIPI_DSI_GENERIC_READ_REQUEST_0_PARAM:
	case MIPI_DSI_GENERIC_READ_REQUEST_1_PARAM:
	case MIPI_DSI_GENERIC_READ_REQUEST_2_PARAM:
	case MIPI_DSI_DCS_SHORT_WRITE:
	case MIPI_DSI_DCS_SHORT_WRITE_PARAM:
	case MIPI_DSI_DCS_READ:
	case MIPI_DSI_DCS_COMPRESSION_MODE:
	case MIPI_DSI_SET_MAXIMUM_RETURN_PACKET_SIZE:
		return true;
	}

	return false;
}