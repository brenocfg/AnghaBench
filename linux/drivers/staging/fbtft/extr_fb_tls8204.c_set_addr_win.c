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
 int /*<<< orphan*/  write_reg (struct fbtft_par*,int) ; 

__attribute__((used)) static void set_addr_win(struct fbtft_par *par, int xs, int ys, int xe, int ye)
{
	/* H=0 Set X address of RAM */
	write_reg(par, 0x80);	/* 7:1  1
				 * 6-0: X[6:0] - 0x00
				 */

	/* H=0 Set Y address of RAM */
	write_reg(par, 0x40);	/* 7:0  0
				 * 6:1  1
				 * 2-0: Y[2:0] - 0x0
				 */
}