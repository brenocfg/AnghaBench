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
struct gspca_dev {int* usb_buf; } ;

/* Variables and functions */
 int SENSOR_CX0342 ; 
 int SENSOR_SOI763A ; 
 int /*<<< orphan*/  TP6800_R10_SIF_TYPE ; 
 int /*<<< orphan*/  TP6800_R12_SIF_ADDR_S ; 
 int /*<<< orphan*/  TP6800_R18_GPIO_DATA ; 
 int /*<<< orphan*/  TP6800_R1A_SIF_TX_DATA2 ; 
 int i2c_r (struct gspca_dev*,int,int) ; 
 scalar_t__ i2c_w (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int probe_6810(struct gspca_dev *gspca_dev)
{
	u8 gpio;
	int ret;

	reg_r(gspca_dev, TP6800_R18_GPIO_DATA);
	gpio = gspca_dev->usb_buf[0];
	reg_w(gspca_dev, TP6800_R18_GPIO_DATA, gpio);
	reg_w(gspca_dev, TP6800_R18_GPIO_DATA, gpio | 0x20);
	reg_w(gspca_dev, TP6800_R18_GPIO_DATA, gpio);
	reg_w(gspca_dev, TP6800_R10_SIF_TYPE, 0x04);	/* i2c 16 bits */
	reg_w(gspca_dev, TP6800_R12_SIF_ADDR_S, 0x21);	/* ov??? */
	reg_w(gspca_dev, TP6800_R1A_SIF_TX_DATA2, 0x00);
	if (i2c_w(gspca_dev, 0x00, 0x00) >= 0)
		return SENSOR_SOI763A;

	reg_w(gspca_dev, TP6800_R18_GPIO_DATA, gpio | 0x20);
	reg_w(gspca_dev, TP6800_R10_SIF_TYPE, 0x00);	/* i2c 8 bits */
	reg_w(gspca_dev, TP6800_R12_SIF_ADDR_S, 0x7f);	/* (unknown i2c) */
	if (i2c_w(gspca_dev, 0x00, 0x00) >= 0)
		return -2;

	reg_w(gspca_dev, TP6800_R18_GPIO_DATA, gpio | 0x20);
	reg_w(gspca_dev, TP6800_R18_GPIO_DATA, gpio);
	reg_w(gspca_dev, TP6800_R18_GPIO_DATA, gpio | 0x20);
	reg_w(gspca_dev, TP6800_R10_SIF_TYPE, 0x00);	/* i2c 8 bits */
	reg_w(gspca_dev, TP6800_R12_SIF_ADDR_S, 0x11);	/* tas??? / hv??? */
	ret = i2c_r(gspca_dev, 0x00, 1);
	if (ret > 0)
		return -3;

	reg_w(gspca_dev, TP6800_R18_GPIO_DATA, gpio | 0x20);
	reg_w(gspca_dev, TP6800_R18_GPIO_DATA, gpio);
	reg_w(gspca_dev, TP6800_R18_GPIO_DATA, gpio | 0x20);
	reg_w(gspca_dev, TP6800_R12_SIF_ADDR_S, 0x6e);	/* po??? */
	ret = i2c_r(gspca_dev, 0x00, 1);
	if (ret > 0)
		return -4;

	ret = i2c_r(gspca_dev, 0x01, 1);
	if (ret > 0)
		return -5;

	reg_w(gspca_dev, TP6800_R18_GPIO_DATA, gpio | 0x20);
	reg_w(gspca_dev, TP6800_R18_GPIO_DATA, gpio);
	reg_w(gspca_dev, TP6800_R18_GPIO_DATA, gpio | 0x20);
	reg_w(gspca_dev, TP6800_R10_SIF_TYPE, 0x04);	/* i2c 16 bits */
	reg_w(gspca_dev, TP6800_R12_SIF_ADDR_S, 0x5d);	/* mi/mt??? */
	ret = i2c_r(gspca_dev, 0x00, 2);
	if (ret > 0)
		return -6;

	reg_w(gspca_dev, TP6800_R18_GPIO_DATA, gpio | 0x20);
	reg_w(gspca_dev, TP6800_R18_GPIO_DATA, gpio);
	reg_w(gspca_dev, TP6800_R18_GPIO_DATA, gpio | 0x20);
	reg_w(gspca_dev, TP6800_R12_SIF_ADDR_S, 0x5c);	/* mi/mt??? */
	ret = i2c_r(gspca_dev, 0x36, 2);
	if (ret > 0)
		return -7;

	reg_w(gspca_dev, TP6800_R18_GPIO_DATA, gpio);
	reg_w(gspca_dev, TP6800_R18_GPIO_DATA, gpio | 0x20);
	reg_w(gspca_dev, TP6800_R18_GPIO_DATA, gpio);
	reg_w(gspca_dev, TP6800_R12_SIF_ADDR_S, 0x61);	/* (unknown i2c) */
	reg_w(gspca_dev, TP6800_R1A_SIF_TX_DATA2, 0x10);
	if (i2c_w(gspca_dev, 0xff, 0x00) >= 0)
		return -8;

	reg_w(gspca_dev, TP6800_R18_GPIO_DATA, gpio | 0x20);
	reg_w(gspca_dev, TP6800_R18_GPIO_DATA, gpio);
	reg_w(gspca_dev, TP6800_R18_GPIO_DATA, gpio | 0x20);
	reg_w(gspca_dev, TP6800_R10_SIF_TYPE, 0x00);	/* i2c 8 bits */
	reg_w(gspca_dev, TP6800_R12_SIF_ADDR_S, 0x20);	/* cx0342 */
	ret = i2c_r(gspca_dev, 0x00, 1);
	if (ret > 0)
		return SENSOR_CX0342;
	return -9;
}