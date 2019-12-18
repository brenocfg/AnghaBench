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
struct fbtft_par {int bgr; TYPE_2__ gpio; TYPE_1__ fbtftops; } ;

/* Variables and functions */
 int BIT (int) ; 
 int HEIGHT ; 
 int /*<<< orphan*/  gpiod_set_value (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct fbtft_par*) ; 
 int /*<<< orphan*/  write_reg (struct fbtft_par*,int,...) ; 

__attribute__((used)) static int init_display(struct fbtft_par *par)
{
	par->fbtftops.reset(par);

	if (par->gpio.cs)
		gpiod_set_value(par->gpio.cs, 0);  /* Activate chip */

	write_reg(par, 0x00, 0x0001);
	write_reg(par, 0x03, 0xA8A4);
	write_reg(par, 0x0C, 0x0000);
	write_reg(par, 0x0D, 0x080C);
	write_reg(par, 0x0E, 0x2B00);
	write_reg(par, 0x1E, 0x00B7);
	write_reg(par, 0x01,
		  BIT(13) | (par->bgr << 11) | BIT(9) | (HEIGHT - 1));
	write_reg(par, 0x02, 0x0600);
	write_reg(par, 0x10, 0x0000);
	write_reg(par, 0x05, 0x0000);
	write_reg(par, 0x06, 0x0000);
	write_reg(par, 0x16, 0xEF1C);
	write_reg(par, 0x17, 0x0003);
	write_reg(par, 0x07, 0x0233);
	write_reg(par, 0x0B, 0x0000);
	write_reg(par, 0x0F, 0x0000);
	write_reg(par, 0x41, 0x0000);
	write_reg(par, 0x42, 0x0000);
	write_reg(par, 0x48, 0x0000);
	write_reg(par, 0x49, 0x013F);
	write_reg(par, 0x4A, 0x0000);
	write_reg(par, 0x4B, 0x0000);
	write_reg(par, 0x44, 0xEF00);
	write_reg(par, 0x45, 0x0000);
	write_reg(par, 0x46, 0x013F);
	write_reg(par, 0x23, 0x0000);
	write_reg(par, 0x24, 0x0000);
	write_reg(par, 0x25, 0x8000);
	write_reg(par, 0x4f, 0x0000);
	write_reg(par, 0x4e, 0x0000);
	write_reg(par, 0x22);
	return 0;
}