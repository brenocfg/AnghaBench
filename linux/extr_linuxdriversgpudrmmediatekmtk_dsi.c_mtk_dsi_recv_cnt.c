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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*,...) ; 
#define  MIPI_DSI_RX_ACKNOWLEDGE_AND_ERROR_REPORT 134 
#define  MIPI_DSI_RX_DCS_LONG_READ_RESPONSE 133 
#define  MIPI_DSI_RX_DCS_SHORT_READ_RESPONSE_1BYTE 132 
#define  MIPI_DSI_RX_DCS_SHORT_READ_RESPONSE_2BYTE 131 
#define  MIPI_DSI_RX_GENERIC_LONG_READ_RESPONSE 130 
#define  MIPI_DSI_RX_GENERIC_SHORT_READ_RESPONSE_1BYTE 129 
#define  MIPI_DSI_RX_GENERIC_SHORT_READ_RESPONSE_2BYTE 128 

__attribute__((used)) static u32 mtk_dsi_recv_cnt(u8 type, u8 *read_data)
{
	switch (type) {
	case MIPI_DSI_RX_GENERIC_SHORT_READ_RESPONSE_1BYTE:
	case MIPI_DSI_RX_DCS_SHORT_READ_RESPONSE_1BYTE:
		return 1;
	case MIPI_DSI_RX_GENERIC_SHORT_READ_RESPONSE_2BYTE:
	case MIPI_DSI_RX_DCS_SHORT_READ_RESPONSE_2BYTE:
		return 2;
	case MIPI_DSI_RX_GENERIC_LONG_READ_RESPONSE:
	case MIPI_DSI_RX_DCS_LONG_READ_RESPONSE:
		return read_data[1] + read_data[2] * 16;
	case MIPI_DSI_RX_ACKNOWLEDGE_AND_ERROR_REPORT:
		DRM_INFO("type is 0x02, try again\n");
		break;
	default:
		DRM_INFO("type(0x%x) not recognized\n", type);
		break;
	}

	return 0;
}