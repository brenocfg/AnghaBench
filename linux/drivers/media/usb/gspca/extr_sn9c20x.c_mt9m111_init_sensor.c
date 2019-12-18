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
struct sd {int vstart; scalar_t__ hstart; } ;
struct gspca_dev {scalar_t__ usb_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_w2_buf (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt9m111_init ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void mt9m111_init_sensor(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	i2c_w2_buf(gspca_dev, mt9m111_init, ARRAY_SIZE(mt9m111_init));
	if (gspca_dev->usb_err < 0)
		pr_err("MT9M111 sensor initialization failed\n");

	sd->hstart = 0;
	sd->vstart = 2;
}