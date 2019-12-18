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
struct sd {scalar_t__ bridge; } ;
struct gspca_dev {scalar_t__* usb_buf; } ;

/* Variables and functions */
 scalar_t__ BRIDGE_TP6800 ; 
 int /*<<< orphan*/  TP6800_R11_SIF_CONTROL ; 
 int /*<<< orphan*/  TP6800_R13_SIF_TX_DATA ; 
 int /*<<< orphan*/  TP6800_R19_SIF_ADDR_S2 ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int i2c_w(struct gspca_dev *gspca_dev, u8 index, u8 value)
{
	struct sd *sd = (struct sd *) gspca_dev;

	reg_w(gspca_dev, TP6800_R11_SIF_CONTROL, 0x00);
	reg_w(gspca_dev, TP6800_R19_SIF_ADDR_S2, index);
	reg_w(gspca_dev, TP6800_R13_SIF_TX_DATA, value);
	reg_w(gspca_dev, TP6800_R11_SIF_CONTROL, 0x01);
	if (sd->bridge == BRIDGE_TP6800)
		return 0;
	msleep(5);
	reg_r(gspca_dev, TP6800_R11_SIF_CONTROL);
	if (gspca_dev->usb_buf[0] == 0)
		return 0;
	reg_w(gspca_dev, TP6800_R11_SIF_CONTROL, 0x00);
	return -1;				/* error */
}