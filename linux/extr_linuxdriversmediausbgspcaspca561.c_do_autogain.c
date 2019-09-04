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
struct sd {scalar_t__ ag_cnt; int chip_revision; } ;
struct gspca_dev {int* usb_buf; } ;
typedef  int __u8 ;

/* Variables and functions */
 scalar_t__ AG_CNT_START ; 
#define  Rev072A 128 
 int i2c_read (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  i2c_write (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void do_autogain(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int expotimes;
	int pixelclk;
	int gainG;
	__u8 R, Gr, Gb, B;
	int y;
	__u8 luma_mean = 110;
	__u8 luma_delta = 20;
	__u8 spring = 4;

	if (sd->ag_cnt < 0)
		return;
	if (--sd->ag_cnt >= 0)
		return;
	sd->ag_cnt = AG_CNT_START;

	switch (sd->chip_revision) {
	case Rev072A:
		reg_r(gspca_dev, 0x8621, 1);
		Gr = gspca_dev->usb_buf[0];
		reg_r(gspca_dev, 0x8622, 1);
		R = gspca_dev->usb_buf[0];
		reg_r(gspca_dev, 0x8623, 1);
		B = gspca_dev->usb_buf[0];
		reg_r(gspca_dev, 0x8624, 1);
		Gb = gspca_dev->usb_buf[0];
		y = (77 * R + 75 * (Gr + Gb) + 29 * B) >> 8;
		/* u= (128*B-(43*(Gr+Gb+R))) >> 8; */
		/* v= (128*R-(53*(Gr+Gb))-21*B) >> 8; */

		if (y < luma_mean - luma_delta ||
		    y > luma_mean + luma_delta) {
			expotimes = i2c_read(gspca_dev, 0x09, 0x10);
			pixelclk = 0x0800;
			expotimes = expotimes & 0x07ff;
			gainG = i2c_read(gspca_dev, 0x35, 0x10);

			expotimes += (luma_mean - y) >> spring;
			gainG += (luma_mean - y) / 50;

			if (gainG > 0x3f)
				gainG = 0x3f;
			else if (gainG < 3)
				gainG = 3;
			i2c_write(gspca_dev, gainG, 0x35);

			if (expotimes > 0x0256)
				expotimes = 0x0256;
			else if (expotimes < 3)
				expotimes = 3;
			i2c_write(gspca_dev, expotimes | pixelclk, 0x09);
		}
		break;
	}
}