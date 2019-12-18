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
struct fbtft_par {int bgr; TYPE_1__ fbtftops; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  stub1 (struct fbtft_par*) ; 
 int /*<<< orphan*/  write_reg (struct fbtft_par*,int,int) ; 

__attribute__((used)) static int init_display(struct fbtft_par *par)
{
	par->fbtftops.reset(par);

	/* driving ability */
	write_reg(par, 0xEA, 0x00);
	write_reg(par, 0xEB, 0x20);
	write_reg(par, 0xEC, 0x0C);
	write_reg(par, 0xED, 0xC4);
	write_reg(par, 0xE8, 0x40);
	write_reg(par, 0xE9, 0x38);
	write_reg(par, 0xF1, 0x01);
	write_reg(par, 0xF2, 0x10);
	write_reg(par, 0x27, 0xA3);

	/* power voltage */
	write_reg(par, 0x1B, 0x1B);
	write_reg(par, 0x1A, 0x01);
	write_reg(par, 0x24, 0x2F);
	write_reg(par, 0x25, 0x57);

	/* VCOM offset */
	write_reg(par, 0x23, 0x8D); /* for flicker adjust */

	/* power on */
	write_reg(par, 0x18, 0x36);
	write_reg(par, 0x19, 0x01); /* start osc */
	write_reg(par, 0x01, 0x00); /* wakeup */
	write_reg(par, 0x1F, 0x88);
	mdelay(5);
	write_reg(par, 0x1F, 0x80);
	mdelay(5);
	write_reg(par, 0x1F, 0x90);
	mdelay(5);
	write_reg(par, 0x1F, 0xD0);
	mdelay(5);

	/* color selection */
	write_reg(par, 0x17, 0x05); /* 65k */

	/*panel characteristic */
	write_reg(par, 0x36, 0x00);

	/*display on */
	write_reg(par, 0x28, 0x38);
	mdelay(40);
	write_reg(par, 0x28, 0x3C);

	/* orientation */
	write_reg(par, 0x16, 0x60 | (par->bgr << 3));

	return 0;
}