#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct initio_host {int jsstatus0; int jsint; int phase; int flags; scalar_t__ addr; int /*<<< orphan*/ * active_tc; TYPE_1__* active; void* jsstatus1; } ;
struct TYPE_3__ {scalar_t__ hastat; } ;

/* Variables and functions */
 int HCF_EXPECT_DISC ; 
 int HCF_EXPECT_DONE_DISC ; 
 int /*<<< orphan*/  TSC_FLUSH_FIFO ; 
 int /*<<< orphan*/  TSC_HW_RESELECT ; 
 int /*<<< orphan*/  TSC_INITDEFAULT ; 
 int TSS_BUS_SERV ; 
 int TSS_DISC_INT ; 
 int TSS_FUNC_COMP ; 
 int TSS_INT_PENDING ; 
 int TSS_PH_MASK ; 
 int TSS_RESEL_INT ; 
 int TSS_SCSIRST_INT ; 
 int TSS_SEL_TIMEOUT ; 
 scalar_t__ TUL_SConfig ; 
 scalar_t__ TUL_SCtrl0 ; 
 scalar_t__ TUL_SCtrl1 ; 
 scalar_t__ TUL_SInt ; 
 scalar_t__ TUL_SStatus0 ; 
 scalar_t__ TUL_SStatus1 ; 
 int /*<<< orphan*/  cpu_relax () ; 
 void* inb (scalar_t__) ; 
 int /*<<< orphan*/  initio_append_done_scb (struct initio_host*,TYPE_1__*) ; 
 int /*<<< orphan*/  initio_unlink_busy_scb (struct initio_host*,TYPE_1__*) ; 
 int int_initio_busfree (struct initio_host*) ; 
 int int_initio_resel (struct initio_host*) ; 
 int int_initio_scsi_rst (struct initio_host*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int wait_tulip(struct initio_host * host)
{

	while (!((host->jsstatus0 = inb(host->addr + TUL_SStatus0))
		 & TSS_INT_PENDING))
			cpu_relax();

	host->jsint = inb(host->addr + TUL_SInt);
	host->phase = host->jsstatus0 & TSS_PH_MASK;
	host->jsstatus1 = inb(host->addr + TUL_SStatus1);

	if (host->jsint & TSS_RESEL_INT)	/* if SCSI bus reset detected */
		return int_initio_resel(host);
	if (host->jsint & TSS_SEL_TIMEOUT)	/* if selected/reselected timeout interrupt */
		return int_initio_busfree(host);
	if (host->jsint & TSS_SCSIRST_INT)	/* if SCSI bus reset detected   */
		return int_initio_scsi_rst(host);

	if (host->jsint & TSS_DISC_INT) {	/* BUS disconnection            */
		if (host->flags & HCF_EXPECT_DONE_DISC) {
			outb(TSC_FLUSH_FIFO, host->addr + TUL_SCtrl0); /* Flush SCSI FIFO */
			initio_unlink_busy_scb(host, host->active);
			host->active->hastat = 0;
			initio_append_done_scb(host, host->active);
			host->active = NULL;
			host->active_tc = NULL;
			host->flags &= ~HCF_EXPECT_DONE_DISC;
			outb(TSC_INITDEFAULT, host->addr + TUL_SConfig);
			outb(TSC_HW_RESELECT, host->addr + TUL_SCtrl1);	/* Enable HW reselect */
			return -1;
		}
		if (host->flags & HCF_EXPECT_DISC) {
			outb(TSC_FLUSH_FIFO, host->addr + TUL_SCtrl0); /* Flush SCSI FIFO */
			host->active = NULL;
			host->active_tc = NULL;
			host->flags &= ~HCF_EXPECT_DISC;
			outb(TSC_INITDEFAULT, host->addr + TUL_SConfig);
			outb(TSC_HW_RESELECT, host->addr + TUL_SCtrl1);	/* Enable HW reselect */
			return -1;
		}
		return int_initio_busfree(host);
	}
	/* The old code really does the below. Can probably be removed */
	if (host->jsint & (TSS_FUNC_COMP | TSS_BUS_SERV))
		return host->phase;
	return host->phase;
}