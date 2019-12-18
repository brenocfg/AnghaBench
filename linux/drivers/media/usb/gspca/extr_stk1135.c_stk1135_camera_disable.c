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
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ STK1135_REG_CIEPO ; 
 scalar_t__ STK1135_REG_GCTRL ; 
 scalar_t__ STK1135_REG_SCTRL ; 
 scalar_t__ STK1135_REG_SENSO ; 
 scalar_t__ STK1135_REG_TMGEN ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  reg_w_mask (struct gspca_dev*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  sensor_write_mask (struct gspca_dev*,int,int,int) ; 

__attribute__((used)) static void stk1135_camera_disable(struct gspca_dev *gspca_dev)
{
	/* set capture end Y position to 0 */
	reg_w(gspca_dev, STK1135_REG_CIEPO + 2, 0x00);
	reg_w(gspca_dev, STK1135_REG_CIEPO + 3, 0x00);
	/* disable capture */
	reg_w_mask(gspca_dev, STK1135_REG_SCTRL, 0x00, 0x80);

	/* enable sensor standby and diasble chip enable */
	sensor_write_mask(gspca_dev, 0x00d, 0x0004, 0x000c);

	/* disable PLL */
	reg_w_mask(gspca_dev, STK1135_REG_SENSO + 2, 0x00, 0x01);
	/* disable timing generator */
	reg_w(gspca_dev, STK1135_REG_TMGEN, 0x00);
	/* enable STOP clock */
	reg_w(gspca_dev, STK1135_REG_SENSO + 1, 0x20);
	/* disable CLKOUT for sensor */
	reg_w(gspca_dev, STK1135_REG_SENSO, 0x00);

	/* disable sensor (GPIO5) and enable GPIO0,3,6 (?) - sensor standby? */
	reg_w(gspca_dev, STK1135_REG_GCTRL, 0x49);
}