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
 int /*<<< orphan*/  write_reg (struct fbtft_par*,int,...) ; 

__attribute__((used)) static int init_display(struct fbtft_par *par)
{
	par->fbtftops.reset(par);

	if (par->gpio.cs)
		gpiod_set_value(par->gpio.cs, 0);  /* Activate chip */

	/* Initialization sequence from Lib_UTFT */

	write_reg(par, 0x0011, 0x2004);
	write_reg(par, 0x0013, 0xCC00);
	write_reg(par, 0x0015, 0x2600);
	write_reg(par, 0x0014, 0x252A);
	write_reg(par, 0x0012, 0x0033);
	write_reg(par, 0x0013, 0xCC04);
	write_reg(par, 0x0013, 0xCC06);
	write_reg(par, 0x0013, 0xCC4F);
	write_reg(par, 0x0013, 0x674F);
	write_reg(par, 0x0011, 0x2003);
	write_reg(par, 0x0016, 0x0007);
	write_reg(par, 0x0002, 0x0013);
	write_reg(par, 0x0003, 0x0003);
	write_reg(par, 0x0001, 0x0127);
	write_reg(par, 0x0008, 0x0303);
	write_reg(par, 0x000A, 0x000B);
	write_reg(par, 0x000B, 0x0003);
	write_reg(par, 0x000C, 0x0000);
	write_reg(par, 0x0041, 0x0000);
	write_reg(par, 0x0050, 0x0000);
	write_reg(par, 0x0060, 0x0005);
	write_reg(par, 0x0070, 0x000B);
	write_reg(par, 0x0071, 0x0000);
	write_reg(par, 0x0078, 0x0000);
	write_reg(par, 0x007A, 0x0000);
	write_reg(par, 0x0079, 0x0007);
	write_reg(par, 0x0007, 0x0051);
	write_reg(par, 0x0007, 0x0053);
	write_reg(par, 0x0079, 0x0000);

	write_reg(par, 0x0022); /* Write Data to GRAM */

	return 0;
}