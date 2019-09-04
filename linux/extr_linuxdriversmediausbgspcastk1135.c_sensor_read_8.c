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
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ STK1135_REG_SBUSR ; 
 scalar_t__ STK1135_REG_SICTL ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int reg_r (struct gspca_dev*,scalar_t__) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,scalar_t__,int) ; 
 scalar_t__ stk1135_serial_wait_ready (struct gspca_dev*) ; 

__attribute__((used)) static u8 sensor_read_8(struct gspca_dev *gspca_dev, u8 addr)
{
	reg_w(gspca_dev, STK1135_REG_SBUSR, addr);
	/* begin read */
	reg_w(gspca_dev, STK1135_REG_SICTL, 0x20);
	/* wait until finished */
	if (stk1135_serial_wait_ready(gspca_dev)) {
		pr_err("Sensor read failed\n");
		return 0;
	}

	return reg_r(gspca_dev, STK1135_REG_SBUSR + 1);
}