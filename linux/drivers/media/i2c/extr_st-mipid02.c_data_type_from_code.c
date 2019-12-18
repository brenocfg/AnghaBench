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
typedef  int __u32 ;

/* Variables and functions */
#define  MEDIA_BUS_FMT_BGR888_1X24 145 
#define  MEDIA_BUS_FMT_RGB565_2X8_BE 144 
#define  MEDIA_BUS_FMT_RGB565_2X8_LE 143 
#define  MEDIA_BUS_FMT_SBGGR10_1X10 142 
#define  MEDIA_BUS_FMT_SBGGR12_1X12 141 
#define  MEDIA_BUS_FMT_SBGGR8_1X8 140 
#define  MEDIA_BUS_FMT_SGBRG10_1X10 139 
#define  MEDIA_BUS_FMT_SGBRG12_1X12 138 
#define  MEDIA_BUS_FMT_SGBRG8_1X8 137 
#define  MEDIA_BUS_FMT_SGRBG10_1X10 136 
#define  MEDIA_BUS_FMT_SGRBG12_1X12 135 
#define  MEDIA_BUS_FMT_SGRBG8_1X8 134 
#define  MEDIA_BUS_FMT_SRGGB10_1X10 133 
#define  MEDIA_BUS_FMT_SRGGB12_1X12 132 
#define  MEDIA_BUS_FMT_SRGGB8_1X8 131 
#define  MEDIA_BUS_FMT_UYVY8_1X16 130 
#define  MEDIA_BUS_FMT_UYVY8_2X8 129 
#define  MEDIA_BUS_FMT_YUYV8_2X8 128 

__attribute__((used)) static u8 data_type_from_code(__u32 code)
{
	switch (code) {
	case MEDIA_BUS_FMT_SBGGR8_1X8:
	case MEDIA_BUS_FMT_SGBRG8_1X8:
	case MEDIA_BUS_FMT_SGRBG8_1X8:
	case MEDIA_BUS_FMT_SRGGB8_1X8:
		return 0x2a;
	case MEDIA_BUS_FMT_SBGGR10_1X10:
	case MEDIA_BUS_FMT_SGBRG10_1X10:
	case MEDIA_BUS_FMT_SGRBG10_1X10:
	case MEDIA_BUS_FMT_SRGGB10_1X10:
		return 0x2b;
	case MEDIA_BUS_FMT_SBGGR12_1X12:
	case MEDIA_BUS_FMT_SGBRG12_1X12:
	case MEDIA_BUS_FMT_SGRBG12_1X12:
	case MEDIA_BUS_FMT_SRGGB12_1X12:
		return 0x2c;
	case MEDIA_BUS_FMT_UYVY8_1X16:
	case MEDIA_BUS_FMT_YUYV8_2X8:
	case MEDIA_BUS_FMT_UYVY8_2X8:
		return 0x1e;
	case MEDIA_BUS_FMT_BGR888_1X24:
		return 0x24;
	case MEDIA_BUS_FMT_RGB565_2X8_LE:
	case MEDIA_BUS_FMT_RGB565_2X8_BE:
		return 0x22;
	default:
		return 0;
	}
}