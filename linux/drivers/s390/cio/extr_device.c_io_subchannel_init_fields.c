#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int pam; int /*<<< orphan*/  pom; int /*<<< orphan*/  pim; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {TYPE_1__ pmcw; } ;
struct TYPE_6__ {int /*<<< orphan*/  sch_no; int /*<<< orphan*/  ssid; } ;
struct subchannel {int opm; int lpm; TYPE_2__ schib; TYPE_3__ schid; int /*<<< orphan*/  isc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_MSG_EVENT (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONSOLE_ISC ; 
 int /*<<< orphan*/  IO_SCH_ISC ; 
 int chp_get_sch_opm (struct subchannel*) ; 
 scalar_t__ cio_is_console (TYPE_3__) ; 
 int /*<<< orphan*/  io_subchannel_init_config (struct subchannel*) ; 

__attribute__((used)) static void io_subchannel_init_fields(struct subchannel *sch)
{
	if (cio_is_console(sch->schid))
		sch->opm = 0xff;
	else
		sch->opm = chp_get_sch_opm(sch);
	sch->lpm = sch->schib.pmcw.pam & sch->opm;
	sch->isc = cio_is_console(sch->schid) ? CONSOLE_ISC : IO_SCH_ISC;

	CIO_MSG_EVENT(6, "Detected device %04x on subchannel 0.%x.%04X"
		      " - PIM = %02X, PAM = %02X, POM = %02X\n",
		      sch->schib.pmcw.dev, sch->schid.ssid,
		      sch->schid.sch_no, sch->schib.pmcw.pim,
		      sch->schib.pmcw.pam, sch->schib.pmcw.pom);

	io_subchannel_init_config(sch);
}