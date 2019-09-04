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
 scalar_t__ STK1135_REG_PLLFD ; 
 scalar_t__ STK1135_REG_SENSO ; 
 scalar_t__ STK1135_REG_SICTL ; 
 scalar_t__ STK1135_REG_TCP1 ; 
 scalar_t__ STK1135_REG_TMGEN ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void stk1135_configure_clock(struct gspca_dev *gspca_dev)
{
	/* configure SCLKOUT */
	reg_w(gspca_dev, STK1135_REG_TMGEN, 0x12);
	/* set 1 clock per pixel */
	/* and positive edge clocked pulse high when pixel counter = 0 */
	reg_w(gspca_dev, STK1135_REG_TCP1 + 0, 0x41);
	reg_w(gspca_dev, STK1135_REG_TCP1 + 1, 0x00);
	reg_w(gspca_dev, STK1135_REG_TCP1 + 2, 0x00);
	reg_w(gspca_dev, STK1135_REG_TCP1 + 3, 0x00);

	/* enable CLKOUT for sensor */
	reg_w(gspca_dev, STK1135_REG_SENSO + 0, 0x10);
	/* disable STOP clock */
	reg_w(gspca_dev, STK1135_REG_SENSO + 1, 0x00);
	/* set lower 8 bits of PLL feedback divider */
	reg_w(gspca_dev, STK1135_REG_SENSO + 3, 0x07);
	/* set other PLL parameters */
	reg_w(gspca_dev, STK1135_REG_PLLFD, 0x06);
	/* enable timing generator */
	reg_w(gspca_dev, STK1135_REG_TMGEN, 0x80);
	/* enable PLL */
	reg_w(gspca_dev, STK1135_REG_SENSO + 2, 0x04);

	/* set serial interface clock divider (30MHz/0x1f*16+2) = 60240 kHz) */
	reg_w(gspca_dev, STK1135_REG_SICTL + 2, 0x1f);

	/* wait a while for sensor to catch up */
	udelay(1000);
}