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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  (* reset ) (struct fbtft_par*) ;} ;
struct fbtft_par {TYPE_1__ fbtftops; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct fbtft_par*) ; 
 int /*<<< orphan*/  write_reg (struct fbtft_par*,int,int) ; 

__attribute__((used)) static int init_display(struct fbtft_par *par)
{
	u8 i;

	par->fbtftops.reset(par);

	for (i = 0; i < 2; ++i) {
		write_reg(par, i, 0x3f); /* display on */
		write_reg(par, i, 0x40); /* set x to 0 */
		write_reg(par, i, 0xb0); /* set page to 0 */
		write_reg(par, i, 0xc0); /* set start line to 0 */
	}

	return 0;
}