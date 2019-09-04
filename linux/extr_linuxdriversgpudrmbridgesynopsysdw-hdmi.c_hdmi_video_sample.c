#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {int enc_in_bus_format; } ;
struct dw_hdmi {TYPE_1__ hdmi_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_TX_BCBDATA0 ; 
 int /*<<< orphan*/  HDMI_TX_BCBDATA1 ; 
 int /*<<< orphan*/  HDMI_TX_GYDATA0 ; 
 int /*<<< orphan*/  HDMI_TX_GYDATA1 ; 
 int /*<<< orphan*/  HDMI_TX_INSTUFFING ; 
 int HDMI_TX_INSTUFFING_BDBDATA_STUFFING_ENABLE ; 
 int HDMI_TX_INSTUFFING_GYDATA_STUFFING_ENABLE ; 
 int HDMI_TX_INSTUFFING_RCRDATA_STUFFING_ENABLE ; 
 int /*<<< orphan*/  HDMI_TX_INVID0 ; 
 int HDMI_TX_INVID0_INTERNAL_DE_GENERATOR_DISABLE ; 
 int HDMI_TX_INVID0_VIDEO_MAPPING_MASK ; 
 int HDMI_TX_INVID0_VIDEO_MAPPING_OFFSET ; 
 int /*<<< orphan*/  HDMI_TX_RCRDATA0 ; 
 int /*<<< orphan*/  HDMI_TX_RCRDATA1 ; 
#define  MEDIA_BUS_FMT_RGB101010_1X30 142 
#define  MEDIA_BUS_FMT_RGB121212_1X36 141 
#define  MEDIA_BUS_FMT_RGB161616_1X48 140 
#define  MEDIA_BUS_FMT_RGB888_1X24 139 
#define  MEDIA_BUS_FMT_UYVY10_1X20 138 
#define  MEDIA_BUS_FMT_UYVY12_1X24 137 
#define  MEDIA_BUS_FMT_UYVY8_1X16 136 
#define  MEDIA_BUS_FMT_UYYVYY10_0_5X30 135 
#define  MEDIA_BUS_FMT_UYYVYY12_0_5X36 134 
#define  MEDIA_BUS_FMT_UYYVYY16_0_5X48 133 
#define  MEDIA_BUS_FMT_UYYVYY8_0_5X24 132 
#define  MEDIA_BUS_FMT_YUV10_1X30 131 
#define  MEDIA_BUS_FMT_YUV12_1X36 130 
#define  MEDIA_BUS_FMT_YUV16_1X48 129 
#define  MEDIA_BUS_FMT_YUV8_1X24 128 
 int /*<<< orphan*/  hdmi_writeb (struct dw_hdmi*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hdmi_video_sample(struct dw_hdmi *hdmi)
{
	int color_format = 0;
	u8 val;

	switch (hdmi->hdmi_data.enc_in_bus_format) {
	case MEDIA_BUS_FMT_RGB888_1X24:
		color_format = 0x01;
		break;
	case MEDIA_BUS_FMT_RGB101010_1X30:
		color_format = 0x03;
		break;
	case MEDIA_BUS_FMT_RGB121212_1X36:
		color_format = 0x05;
		break;
	case MEDIA_BUS_FMT_RGB161616_1X48:
		color_format = 0x07;
		break;

	case MEDIA_BUS_FMT_YUV8_1X24:
	case MEDIA_BUS_FMT_UYYVYY8_0_5X24:
		color_format = 0x09;
		break;
	case MEDIA_BUS_FMT_YUV10_1X30:
	case MEDIA_BUS_FMT_UYYVYY10_0_5X30:
		color_format = 0x0B;
		break;
	case MEDIA_BUS_FMT_YUV12_1X36:
	case MEDIA_BUS_FMT_UYYVYY12_0_5X36:
		color_format = 0x0D;
		break;
	case MEDIA_BUS_FMT_YUV16_1X48:
	case MEDIA_BUS_FMT_UYYVYY16_0_5X48:
		color_format = 0x0F;
		break;

	case MEDIA_BUS_FMT_UYVY8_1X16:
		color_format = 0x16;
		break;
	case MEDIA_BUS_FMT_UYVY10_1X20:
		color_format = 0x14;
		break;
	case MEDIA_BUS_FMT_UYVY12_1X24:
		color_format = 0x12;
		break;

	default:
		return;
	}

	val = HDMI_TX_INVID0_INTERNAL_DE_GENERATOR_DISABLE |
		((color_format << HDMI_TX_INVID0_VIDEO_MAPPING_OFFSET) &
		HDMI_TX_INVID0_VIDEO_MAPPING_MASK);
	hdmi_writeb(hdmi, val, HDMI_TX_INVID0);

	/* Enable TX stuffing: When DE is inactive, fix the output data to 0 */
	val = HDMI_TX_INSTUFFING_BDBDATA_STUFFING_ENABLE |
		HDMI_TX_INSTUFFING_RCRDATA_STUFFING_ENABLE |
		HDMI_TX_INSTUFFING_GYDATA_STUFFING_ENABLE;
	hdmi_writeb(hdmi, val, HDMI_TX_INSTUFFING);
	hdmi_writeb(hdmi, 0x0, HDMI_TX_GYDATA0);
	hdmi_writeb(hdmi, 0x0, HDMI_TX_GYDATA1);
	hdmi_writeb(hdmi, 0x0, HDMI_TX_RCRDATA0);
	hdmi_writeb(hdmi, 0x0, HDMI_TX_RCRDATA1);
	hdmi_writeb(hdmi, 0x0, HDMI_TX_BCBDATA0);
	hdmi_writeb(hdmi, 0x0, HDMI_TX_BCBDATA1);
}