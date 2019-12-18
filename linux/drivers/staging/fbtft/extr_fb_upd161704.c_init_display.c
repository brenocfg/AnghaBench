#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ cs; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* reset ) (struct fbtft_par*) ;} ;
struct fbtft_par {TYPE_2__ gpio; TYPE_1__ fbtftops; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct fbtft_par*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_reg (struct fbtft_par*,int,int) ; 

__attribute__((used)) static int init_display(struct fbtft_par *par)
{
	par->fbtftops.reset(par);

	if (par->gpio.cs)
		gpiod_set_value(par->gpio.cs, 0);  /* Activate chip */

	/* Initialization sequence from Lib_UTFT */

	/* register reset */
	write_reg(par, 0x0003, 0x0001);	/* Soft reset */

	/* oscillator start */
	write_reg(par, 0x003A, 0x0001);	/*Oscillator 0: stop, 1: operation */
	udelay(100);

	/* y-setting */
	write_reg(par, 0x0024, 0x007B);	/* amplitude setting */
	udelay(10);
	write_reg(par, 0x0025, 0x003B);	/* amplitude setting */
	write_reg(par, 0x0026, 0x0034);	/* amplitude setting */
	udelay(10);
	write_reg(par, 0x0027, 0x0004);	/* amplitude setting */
	write_reg(par, 0x0052, 0x0025);	/* circuit setting 1 */
	udelay(10);
	write_reg(par, 0x0053, 0x0033);	/* circuit setting 2 */
	write_reg(par, 0x0061, 0x001C);	/* adjustment V10 positive polarity */
	udelay(10);
	write_reg(par, 0x0062, 0x002C);	/* adjustment V9 negative polarity */
	write_reg(par, 0x0063, 0x0022);	/* adjustment V34 positive polarity */
	udelay(10);
	write_reg(par, 0x0064, 0x0027);	/* adjustment V31 negative polarity */
	udelay(10);
	write_reg(par, 0x0065, 0x0014);	/* adjustment V61 negative polarity */
	udelay(10);
	write_reg(par, 0x0066, 0x0010);	/* adjustment V61 negative polarity */

	/* Basical clock for 1 line (BASECOUNT[7:0]) number specified */
	write_reg(par, 0x002E, 0x002D);

	/* Power supply setting */
	write_reg(par, 0x0019, 0x0000);	/* DC/DC output setting */
	udelay(200);
	write_reg(par, 0x001A, 0x1000);	/* DC/DC frequency setting */
	write_reg(par, 0x001B, 0x0023);	/* DC/DC rising setting */
	write_reg(par, 0x001C, 0x0C01);	/* Regulator voltage setting */
	write_reg(par, 0x001D, 0x0000);	/* Regulator current setting */
	write_reg(par, 0x001E, 0x0009);	/* VCOM output setting */
	write_reg(par, 0x001F, 0x0035);	/* VCOM amplitude setting */
	write_reg(par, 0x0020, 0x0015);	/* VCOMM cencter setting */
	write_reg(par, 0x0018, 0x1E7B);	/* DC/DC operation setting */

	/* windows setting */
	write_reg(par, 0x0008, 0x0000);	/* Minimum X address */
	write_reg(par, 0x0009, 0x00EF);	/* Maximum X address */
	write_reg(par, 0x000a, 0x0000);	/* Minimum Y address */
	write_reg(par, 0x000b, 0x013F);	/* Maximum Y address */

	/* LCD display area setting */
	write_reg(par, 0x0029, 0x0000);	/* [LCDSIZE]  X MIN. size set */
	write_reg(par, 0x002A, 0x0000);	/* [LCDSIZE]  Y MIN. size set */
	write_reg(par, 0x002B, 0x00EF);	/* [LCDSIZE]  X MAX. size set */
	write_reg(par, 0x002C, 0x013F);	/* [LCDSIZE]  Y MAX. size set */

	/* Gate scan setting */
	write_reg(par, 0x0032, 0x0002);

	/* n line inversion line number */
	write_reg(par, 0x0033, 0x0000);

	/* Line inversion/frame inversion/interlace setting */
	write_reg(par, 0x0037, 0x0000);

	/* Gate scan operation setting register */
	write_reg(par, 0x003B, 0x0001);

	/* Color mode */
	/*GS = 0: 260-k color (64 gray scale), GS = 1: 8 color (2 gray scale) */
	write_reg(par, 0x0004, 0x0000);

	/* RAM control register */
	write_reg(par, 0x0005, 0x0000);	/*Window access 00:Normal, 10:Window */

	/* Display setting register 2 */
	write_reg(par, 0x0001, 0x0000);

	/* display setting */
	write_reg(par, 0x0000, 0x0000);	/* display on */

	return 0;
}