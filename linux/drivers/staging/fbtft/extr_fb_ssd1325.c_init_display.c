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
struct TYPE_4__ {int /*<<< orphan*/  cs; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* reset ) (struct fbtft_par*) ;} ;
struct fbtft_par {TYPE_2__ gpio; TYPE_1__ fbtftops; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct fbtft_par*) ; 
 int /*<<< orphan*/  write_reg (struct fbtft_par*,int) ; 

__attribute__((used)) static int init_display(struct fbtft_par *par)
{
	par->fbtftops.reset(par);

	gpiod_set_value(par->gpio.cs, 0);

	write_reg(par, 0xb3);
	write_reg(par, 0xf0);
	write_reg(par, 0xae);
	write_reg(par, 0xa1);
	write_reg(par, 0x00);
	write_reg(par, 0xa8);
	write_reg(par, 0x3f);
	write_reg(par, 0xa0);
	write_reg(par, 0x45);
	write_reg(par, 0xa2);
	write_reg(par, 0x40);
	write_reg(par, 0x75);
	write_reg(par, 0x00);
	write_reg(par, 0x3f);
	write_reg(par, 0x15);
	write_reg(par, 0x00);
	write_reg(par, 0x7f);
	write_reg(par, 0xa4);
	write_reg(par, 0xaf);

	return 0;
}