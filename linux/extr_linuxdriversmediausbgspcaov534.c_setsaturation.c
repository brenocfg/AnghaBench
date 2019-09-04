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
typedef  size_t u8 ;
struct sd {scalar_t__ sensor; } ;
struct gspca_dev {int dummy; } ;
typedef  size_t s32 ;

/* Variables and functions */
 int ARRAY_SIZE (size_t*) ; 
 scalar_t__ SENSOR_OV767x ; 
 int /*<<< orphan*/  sccb_reg_write (struct gspca_dev*,int,size_t) ; 

__attribute__((used)) static void setsaturation(struct gspca_dev *gspca_dev, s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (sd->sensor == SENSOR_OV767x) {
		int i;
		static u8 color_tb[][6] = {
			{0x42, 0x42, 0x00, 0x11, 0x30, 0x41},
			{0x52, 0x52, 0x00, 0x16, 0x3c, 0x52},
			{0x66, 0x66, 0x00, 0x1b, 0x4b, 0x66},
			{0x80, 0x80, 0x00, 0x22, 0x5e, 0x80},
			{0x9a, 0x9a, 0x00, 0x29, 0x71, 0x9a},
			{0xb8, 0xb8, 0x00, 0x31, 0x87, 0xb8},
			{0xdd, 0xdd, 0x00, 0x3b, 0xa2, 0xdd},
		};

		for (i = 0; i < ARRAY_SIZE(color_tb[0]); i++)
			sccb_reg_write(gspca_dev, 0x4f + i, color_tb[val][i]);
	} else {
		sccb_reg_write(gspca_dev, 0xa7, val); /* U saturation */
		sccb_reg_write(gspca_dev, 0xa8, val); /* V saturation */
	}
}