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
struct sd {scalar_t__ sensor; } ;
struct gspca_dev {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 scalar_t__ SENSOR_OV767x ; 
#define  V4L2_EXPOSURE_AUTO 129 
#define  V4L2_EXPOSURE_MANUAL 128 
 int sccb_reg_read (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  sccb_reg_write (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void setaec(struct gspca_dev *gspca_dev, s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 data;

	data = sd->sensor == SENSOR_OV767x ?
			0x05 :		/* agc + aec */
			0x01;		/* agc */
	switch (val) {
	case V4L2_EXPOSURE_AUTO:
		sccb_reg_write(gspca_dev, 0x13,
				sccb_reg_read(gspca_dev, 0x13) | data);
		break;
	case V4L2_EXPOSURE_MANUAL:
		sccb_reg_write(gspca_dev, 0x13,
				sccb_reg_read(gspca_dev, 0x13) & ~data);
		break;
	}
}