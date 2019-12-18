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
 int /*<<< orphan*/  SENSOR_GC0307 ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  i2c_r (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  reg_w1 (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void po2030n_probe(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u16 val;

	/* check gc0307 */
	reg_w1(gspca_dev, 0x17, 0x62);
	reg_w1(gspca_dev, 0x01, 0x08);
	reg_w1(gspca_dev, 0x02, 0x22);
	sd->i2c_addr = 0x21;
	i2c_r(gspca_dev, 0x00, 1);
	val = gspca_dev->usb_buf[4];
	reg_w1(gspca_dev, 0x01, 0x29);		/* reset */
	reg_w1(gspca_dev, 0x17, 0x42);
	if (val == 0x99) {			/* gc0307 (?) */
		gspca_dbg(gspca_dev, D_PROBE, "Sensor gc0307\n");
		sd->sensor = SENSOR_GC0307;
		return;
	}

	/* check po2030n */
	reg_w1(gspca_dev, 0x17, 0x62);
	reg_w1(gspca_dev, 0x01, 0x0a);
	sd->i2c_addr = 0x6e;
	i2c_r(gspca_dev, 0x00, 2);
	val = (gspca_dev->usb_buf[3] << 8) | gspca_dev->usb_buf[4];
	reg_w1(gspca_dev, 0x01, 0x29);
	reg_w1(gspca_dev, 0x17, 0x42);
	if (gspca_dev->usb_err < 0)
		return;
	if (val == 0x2030) {
		gspca_dbg(gspca_dev, D_PROBE, "Sensor po2030n\n");
/*		sd->sensor = SENSOR_PO2030N; */
	} else {
		pr_err("Unknown sensor ID %04x\n", val);
	}
}