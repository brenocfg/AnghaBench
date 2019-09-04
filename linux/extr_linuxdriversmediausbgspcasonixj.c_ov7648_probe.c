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
typedef  int u16 ;
struct sd {int i2c_addr; int /*<<< orphan*/  sensor; } ;
struct gspca_dev {int* usb_buf; scalar_t__ usb_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_PROBE ; 
 int /*<<< orphan*/  SENSOR_PO1030 ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  i2c_r (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  reg_w1 (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void ov7648_probe(struct gspca_dev *gspca_dev)
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
	if ((val & 0xff00) == 0x7600) {		/* ov76xx */
		gspca_dbg(gspca_dev, D_PROBE, "Sensor ov%04x\n", val);
		return;
	}

	/* check po1030 */
	reg_w1(gspca_dev, 0x17, 0x62);
	reg_w1(gspca_dev, 0x01, 0x08);
	sd->i2c_addr = 0x6e;
	i2c_r(gspca_dev, 0x00, 2);
	val = (gspca_dev->usb_buf[3] << 8) | gspca_dev->usb_buf[4];
	reg_w1(gspca_dev, 0x01, 0x29);
	reg_w1(gspca_dev, 0x17, 0x42);
	if (gspca_dev->usb_err < 0)
		return;
	if (val == 0x1030) {			/* po1030 */
		gspca_dbg(gspca_dev, D_PROBE, "Sensor po1030\n");
		sd->sensor = SENSOR_PO1030;
		return;
	}
	pr_err("Unknown sensor %04x\n", val);
}