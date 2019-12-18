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
struct fbtft_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  write_reg (struct fbtft_par*,int,...) ; 

__attribute__((used)) static void set_addr_win(struct fbtft_par *par, int xs, int ys, int xe, int ye)
{
	/* Set_Active_Window */
	write_reg(par, 0x30, xs & 0x00FF);
	write_reg(par, 0x31, (xs & 0xFF00) >> 8);
	write_reg(par, 0x32, ys & 0x00FF);
	write_reg(par, 0x33, (ys & 0xFF00) >> 8);
	write_reg(par, 0x34, (xs + xe) & 0x00FF);
	write_reg(par, 0x35, ((xs + xe) & 0xFF00) >> 8);
	write_reg(par, 0x36, (ys + ye) & 0x00FF);
	write_reg(par, 0x37, ((ys + ye) & 0xFF00) >> 8);

	/* Set_Memory_Write_Cursor */
	write_reg(par, 0x46,  xs & 0xff);
	write_reg(par, 0x47, (xs >> 8) & 0x03);
	write_reg(par, 0x48,  ys & 0xff);
	write_reg(par, 0x49, (ys >> 8) & 0x01);

	write_reg(par, 0x02);
}