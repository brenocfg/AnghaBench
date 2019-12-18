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
 int broadsheet_spiflash_op_on_address (struct broadsheetfb_par*,int,int) ; 
 int broadsheet_spiflash_read_byte (struct broadsheetfb_par*,char*) ; 
 int /*<<< orphan*/  broadsheet_write_reg (struct broadsheetfb_par*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int broadsheet_spiflash_read_range(struct broadsheetfb_par *par,
						int addr, int size, char *data)
{
	int err;
	int i;

	err = broadsheet_spiflash_op_on_address(par, 0x03, addr);
	if (err)
		goto failout;

	for (i = 0; i < size; i++) {
		err = broadsheet_spiflash_read_byte(par, &data[i]);
		if (err)
			goto failout;
	}

failout:
	broadsheet_write_reg(par, 0x0208, 0);
	return err;
}