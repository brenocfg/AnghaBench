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
struct sd {scalar_t__ sensor; } ;
struct gspca_dev {int* usb_buf; } ;
typedef  int __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  D_CONF ; 
 int /*<<< orphan*/  PAS106_REG0e ; 
 scalar_t__ SENSOR_PAS106 ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  i2c_r (struct gspca_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __u8 Et_getgainG(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (sd->sensor == SENSOR_PAS106) {
		i2c_r(gspca_dev, PAS106_REG0e);
		gspca_dbg(gspca_dev, D_CONF, "Etoms gain G %d\n",
			  gspca_dev->usb_buf[0]);
		return gspca_dev->usb_buf[0];
	}
	return 0x1f;
}