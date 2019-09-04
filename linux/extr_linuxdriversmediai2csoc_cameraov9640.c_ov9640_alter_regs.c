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
typedef  int u32 ;
struct ov9640_reg_alt {int com13; int /*<<< orphan*/  com15; void* com7; int /*<<< orphan*/  com12; } ;

/* Variables and functions */
#define  MEDIA_BUS_FMT_RGB555_2X8_PADHI_LE 130 
#define  MEDIA_BUS_FMT_RGB565_2X8_LE 129 
#define  MEDIA_BUS_FMT_UYVY8_2X8 128 
 int /*<<< orphan*/  OV9640_COM12_YUV_AVG ; 
 void* OV9640_COM13_RGB_AVG ; 
 int OV9640_COM13_YUV_DLY (int) ; 
 int OV9640_COM13_Y_DELAY_EN ; 
 int /*<<< orphan*/  OV9640_COM15_RGB_555 ; 
 int /*<<< orphan*/  OV9640_COM15_RGB_565 ; 
 void* OV9640_COM7_RGB ; 

__attribute__((used)) static void ov9640_alter_regs(u32 code,
			      struct ov9640_reg_alt *alt)
{
	switch (code) {
	default:
	case MEDIA_BUS_FMT_UYVY8_2X8:
		alt->com12	= OV9640_COM12_YUV_AVG;
		alt->com13	= OV9640_COM13_Y_DELAY_EN |
					OV9640_COM13_YUV_DLY(0x01);
		break;
	case MEDIA_BUS_FMT_RGB555_2X8_PADHI_LE:
		alt->com7	= OV9640_COM7_RGB;
		alt->com13	= OV9640_COM13_RGB_AVG;
		alt->com15	= OV9640_COM15_RGB_555;
		break;
	case MEDIA_BUS_FMT_RGB565_2X8_LE:
		alt->com7	= OV9640_COM7_RGB;
		alt->com13	= OV9640_COM13_RGB_AVG;
		alt->com15	= OV9640_COM15_RGB_565;
		break;
	}
}