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
struct sd {int hstart; int vstart; } ;
struct gspca_dev {scalar_t__ usb_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_w1 (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  i2c_w1_buf (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  ov9655_init ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void ov9655_init_sensor(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	i2c_w1(gspca_dev, 0x12, 0x80);		/* sensor reset */
	msleep(200);
	i2c_w1_buf(gspca_dev, ov9655_init, ARRAY_SIZE(ov9655_init));
	if (gspca_dev->usb_err < 0)
		pr_err("OV9655 sensor initialization failed\n");

	sd->hstart = 1;
	sd->vstart = 2;
}