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
struct serial_console_data {int /*<<< orphan*/  tstc; int /*<<< orphan*/  getc; int /*<<< orphan*/  putc; int /*<<< orphan*/  open; } ;

/* Variables and functions */
 int dt_get_virtual_reg (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  psc ; 
 int /*<<< orphan*/  psc_getc ; 
 int /*<<< orphan*/  psc_open ; 
 int /*<<< orphan*/  psc_putc ; 
 int /*<<< orphan*/  psc_tstc ; 

int mpc5200_psc_console_init(void *devp, struct serial_console_data *scdp)
{
	/* Get the base address of the psc registers */
	if (dt_get_virtual_reg(devp, &psc, 1) < 1)
		return -1;

	scdp->open = psc_open;
	scdp->putc = psc_putc;
	scdp->getc = psc_getc;
	scdp->tstc = psc_tstc;

	return 0;
}