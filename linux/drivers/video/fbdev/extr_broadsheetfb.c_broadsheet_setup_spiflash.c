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
typedef  int /*<<< orphan*/  u16 ;
struct broadsheetfb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  broadsheet_read_reg (struct broadsheetfb_par*,int) ; 
 int /*<<< orphan*/  broadsheet_write_reg (struct broadsheetfb_par*,int,int) ; 

__attribute__((used)) static int broadsheet_setup_spiflash(struct broadsheetfb_par *par,
						u16 *orig_sfmcd)
{

	*orig_sfmcd = broadsheet_read_reg(par, 0x0204);
	broadsheet_write_reg(par, 0x0208, 0);
	broadsheet_write_reg(par, 0x0204, 0);
	broadsheet_write_reg(par, 0x0204, ((3 << 3) | 1));

	return 0;
}