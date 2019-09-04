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
#define  MIPI_DSI_BLANKING_PACKET 142 
#define  MIPI_DSI_DCS_LONG_WRITE 141 
#define  MIPI_DSI_GENERIC_LONG_WRITE 140 
#define  MIPI_DSI_LOOSELY_PACKED_PIXEL_STREAM_YCBCR20 139 
#define  MIPI_DSI_NULL_PACKET 138 
#define  MIPI_DSI_PACKED_PIXEL_STREAM_16 137 
#define  MIPI_DSI_PACKED_PIXEL_STREAM_18 136 
#define  MIPI_DSI_PACKED_PIXEL_STREAM_24 135 
#define  MIPI_DSI_PACKED_PIXEL_STREAM_30 134 
#define  MIPI_DSI_PACKED_PIXEL_STREAM_36 133 
#define  MIPI_DSI_PACKED_PIXEL_STREAM_YCBCR12 132 
#define  MIPI_DSI_PACKED_PIXEL_STREAM_YCBCR16 131 
#define  MIPI_DSI_PACKED_PIXEL_STREAM_YCBCR24 130 
#define  MIPI_DSI_PIXEL_STREAM_3BYTE_18 129 
#define  MIPI_DSI_PPS_LONG_WRITE 128 

bool mipi_dsi_packet_format_is_long(u8 type)
{
	switch (type) {
	case MIPI_DSI_PPS_LONG_WRITE:
	case MIPI_DSI_NULL_PACKET:
	case MIPI_DSI_BLANKING_PACKET:
	case MIPI_DSI_GENERIC_LONG_WRITE:
	case MIPI_DSI_DCS_LONG_WRITE:
	case MIPI_DSI_LOOSELY_PACKED_PIXEL_STREAM_YCBCR20:
	case MIPI_DSI_PACKED_PIXEL_STREAM_YCBCR24:
	case MIPI_DSI_PACKED_PIXEL_STREAM_YCBCR16:
	case MIPI_DSI_PACKED_PIXEL_STREAM_30:
	case MIPI_DSI_PACKED_PIXEL_STREAM_36:
	case MIPI_DSI_PACKED_PIXEL_STREAM_YCBCR12:
	case MIPI_DSI_PACKED_PIXEL_STREAM_16:
	case MIPI_DSI_PACKED_PIXEL_STREAM_18:
	case MIPI_DSI_PIXEL_STREAM_3BYTE_18:
	case MIPI_DSI_PACKED_PIXEL_STREAM_24:
		return true;
	}

	return false;
}