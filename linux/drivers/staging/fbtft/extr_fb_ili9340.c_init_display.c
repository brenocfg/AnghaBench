#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* reset ) (struct fbtft_par*) ;} ;
struct fbtft_par {TYPE_1__ fbtftops; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPI_DCS_EXIT_SLEEP_MODE ; 
 int /*<<< orphan*/  MIPI_DCS_SET_DISPLAY_ON ; 
 int /*<<< orphan*/  MIPI_DCS_SET_GAMMA_CURVE ; 
 int /*<<< orphan*/  MIPI_DCS_SET_PIXEL_FORMAT ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  stub1 (struct fbtft_par*) ; 
 int /*<<< orphan*/  write_reg (struct fbtft_par*,int,...) ; 

__attribute__((used)) static int init_display(struct fbtft_par *par)
{
	par->fbtftops.reset(par);

	write_reg(par, 0xEF, 0x03, 0x80, 0x02);
	write_reg(par, 0xCF, 0x00, 0XC1, 0X30);
	write_reg(par, 0xED, 0x64, 0x03, 0X12, 0X81);
	write_reg(par, 0xE8, 0x85, 0x00, 0x78);
	write_reg(par, 0xCB, 0x39, 0x2C, 0x00, 0x34, 0x02);
	write_reg(par, 0xF7, 0x20);
	write_reg(par, 0xEA, 0x00, 0x00);

	/* Power Control 1 */
	write_reg(par, 0xC0, 0x23);

	/* Power Control 2 */
	write_reg(par, 0xC1, 0x10);

	/* VCOM Control 1 */
	write_reg(par, 0xC5, 0x3e, 0x28);

	/* VCOM Control 2 */
	write_reg(par, 0xC7, 0x86);

	/* COLMOD: Pixel Format Set */
	/* 16 bits/pixel */
	write_reg(par, MIPI_DCS_SET_PIXEL_FORMAT, 0x55);

	/* Frame Rate Control */
	/* Division ratio = fosc, Frame Rate = 79Hz */
	write_reg(par, 0xB1, 0x00, 0x18);

	/* Display Function Control */
	write_reg(par, 0xB6, 0x08, 0x82, 0x27);

	/* Gamma Function Disable */
	write_reg(par, 0xF2, 0x00);

	/* Gamma curve selection */
	write_reg(par, MIPI_DCS_SET_GAMMA_CURVE, 0x01);

	/* Positive Gamma Correction */
	write_reg(par, 0xE0,
		  0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08, 0x4E, 0xF1,
		  0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00);

	/* Negative Gamma Correction */
	write_reg(par, 0xE1,
		  0x00, 0x0E, 0x14, 0x03, 0x11, 0x07, 0x31, 0xC1,
		  0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F);

	write_reg(par, MIPI_DCS_EXIT_SLEEP_MODE);

	mdelay(120);

	write_reg(par, MIPI_DCS_SET_DISPLAY_ON);

	return 0;
}