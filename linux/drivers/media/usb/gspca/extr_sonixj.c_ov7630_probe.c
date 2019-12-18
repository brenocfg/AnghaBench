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
typedef  int u16 ;
struct sd {int i2c_addr; int /*<<< orphan*/  sensor; } ;
struct TYPE_2__ {int input_flags; } ;
struct gspca_dev {int* usb_buf; scalar_t__ usb_err; TYPE_1__ cam; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_PROBE ; 
 int /*<<< orphan*/  SENSOR_SOI768 ; 
 int V4L2_IN_ST_HFLIP ; 
 int V4L2_IN_ST_VFLIP ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  i2c_r (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  reg_w1 (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void ov7630_probe(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u16 val;

	/* check ov76xx */
	reg_w1(gspca_dev, 0x17, 0x62);
	reg_w1(gspca_dev, 0x01, 0x08);
	sd->i2c_addr = 0x21;
	i2c_r(gspca_dev, 0x0a, 2);
	val = (gspca_dev->usb_buf[3] << 8) | gspca_dev->usb_buf[4];
	reg_w1(gspca_dev, 0x01, 0x29);
	reg_w1(gspca_dev, 0x17, 0x42);
	if (gspca_dev->usb_err < 0)
		return;
	if (val == 0x7628) {			/* soi768 */
		sd->sensor = SENSOR_SOI768;
/*fixme: only valid for 0c45:613e?*/
		gspca_dev->cam.input_flags =
				V4L2_IN_ST_VFLIP | V4L2_IN_ST_HFLIP;
		gspca_dbg(gspca_dev, D_PROBE, "Sensor soi768\n");
		return;
	}
	gspca_dbg(gspca_dev, D_PROBE, "Sensor ov%04x\n", val);
}