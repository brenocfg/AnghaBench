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
 int bs ; 
 int /*<<< orphan*/  stub1 (struct fbtft_par*) ; 
 int tc ; 
 int /*<<< orphan*/  write_reg (struct fbtft_par*,int) ; 

__attribute__((used)) static int init_display(struct fbtft_par *par)
{
	par->fbtftops.reset(par);

	/* Function set
	 *
	 * 5:1  1
	 * 2:0  PD - Powerdown control: chip is active
	 * 1:0  V  - Entry mode: horizontal addressing
	 * 0:1  H  - Extended instruction set control: extended
	 */
	write_reg(par, 0x21);

	/* H=1 Temperature control
	 *
	 * 2:1  1
	 * 1:x  TC1 - Temperature Coefficient: 0x10
	 * 0:x  TC0
	 */
	write_reg(par, 0x04 | (tc & 0x3));

	/* H=1 Bias system
	 *
	 * 4:1  1
	 * 3:0  0
	 * 2:x  BS2 - Bias System
	 * 1:x  BS1
	 * 0:x  BS0
	 */
	write_reg(par, 0x10 | (bs & 0x7));

	/* Function set
	 *
	 * 5:1  1
	 * 2:0  PD - Powerdown control: chip is active
	 * 1:1  V  - Entry mode: vertical addressing
	 * 0:0  H  - Extended instruction set control: basic
	 */
	write_reg(par, 0x22);

	/* H=0 Display control
	 *
	 * 3:1  1
	 * 2:1  D  - DE: 10=normal mode
	 * 1:0  0
	 * 0:0  E
	 */
	write_reg(par, 0x08 | 4);

	return 0;
}