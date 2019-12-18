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
struct initio_host {int jsstatus0; int jsint; int /*<<< orphan*/ * active; scalar_t__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSC_FLUSH_FIFO ; 
 int /*<<< orphan*/  TSC_HW_RESELECT ; 
 int /*<<< orphan*/  TSC_INITDEFAULT ; 
 int TSS_DISC_INT ; 
 int TSS_INT_PENDING ; 
 int TSS_SCSIRST_INT ; 
 scalar_t__ TUL_SConfig ; 
 scalar_t__ TUL_SCtrl0 ; 
 scalar_t__ TUL_SCtrl1 ; 
 scalar_t__ TUL_SInt ; 
 scalar_t__ TUL_SStatus0 ; 
 int /*<<< orphan*/  cpu_relax () ; 
 void* inb (scalar_t__) ; 
 int initio_bad_seq (struct initio_host*) ; 
 int int_initio_scsi_rst (struct initio_host*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int initio_wait_disc(struct initio_host * host)
{
	while (!((host->jsstatus0 = inb(host->addr + TUL_SStatus0)) & TSS_INT_PENDING))
		cpu_relax();

	host->jsint = inb(host->addr + TUL_SInt);

	if (host->jsint & TSS_SCSIRST_INT)	/* if SCSI bus reset detected */
		return int_initio_scsi_rst(host);
	if (host->jsint & TSS_DISC_INT) {	/* BUS disconnection */
		outb(TSC_FLUSH_FIFO, host->addr + TUL_SCtrl0); /* Flush SCSI FIFO */
		outb(TSC_INITDEFAULT, host->addr + TUL_SConfig);
		outb(TSC_HW_RESELECT, host->addr + TUL_SCtrl1);	/* Enable HW reselect */
		host->active = NULL;
		return -1;
	}
	return initio_bad_seq(host);
}