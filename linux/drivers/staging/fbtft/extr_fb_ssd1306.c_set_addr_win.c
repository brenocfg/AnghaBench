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
struct fbtft_par {TYPE_2__* info; } ;
struct TYPE_3__ {int xres; int yres; } ;
struct TYPE_4__ {TYPE_1__ var; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_addr_win_64x48 (struct fbtft_par*) ; 
 int /*<<< orphan*/  write_reg (struct fbtft_par*,int) ; 

__attribute__((used)) static void set_addr_win(struct fbtft_par *par, int xs, int ys, int xe, int ye)
{
	/* Set Lower Column Start Address for Page Addressing Mode */
	write_reg(par, 0x00 | 0x0);
	/* Set Higher Column Start Address for Page Addressing Mode */
	write_reg(par, 0x10 | 0x0);
	/* Set Display Start Line */
	write_reg(par, 0x40 | 0x0);

	if (par->info->var.xres == 64 && par->info->var.yres == 48)
		set_addr_win_64x48(par);
}