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
struct broadsheetfb_par {int dummy; } ;

/* Variables and functions */
 int broadsheet_spiflash_write_byte (struct broadsheetfb_par*,int) ; 
 int /*<<< orphan*/  broadsheet_write_reg (struct broadsheetfb_par*,int,int) ; 

__attribute__((used)) static int broadsheet_spiflash_write_control(struct broadsheetfb_par *par,
						int mode)
{
	int err;

	broadsheet_write_reg(par, 0x0208, 1);
	if (mode)
		err = broadsheet_spiflash_write_byte(par, 0x06);
	else
		err = broadsheet_spiflash_write_byte(par, 0x04);

	broadsheet_write_reg(par, 0x0208, 0);
	return err;
}