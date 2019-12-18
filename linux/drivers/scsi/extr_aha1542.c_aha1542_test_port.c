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
typedef  int u8 ;
struct Scsi_Host {int /*<<< orphan*/  io_port; } ;

/* Variables and functions */
 int CDF ; 
 int /*<<< orphan*/  CMD_INQUIRY ; 
 int /*<<< orphan*/  CONTROL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DATA (int /*<<< orphan*/ ) ; 
 int DF ; 
 int DIAGF ; 
 int HACC ; 
 int IDLE ; 
 int INIT ; 
 int /*<<< orphan*/  INTRFLAGS (int /*<<< orphan*/ ) ; 
 int INTRMASK ; 
 int INVDCMD ; 
 int IRST ; 
 int SRST ; 
 int STATMASK ; 
 int /*<<< orphan*/  STATUS (int /*<<< orphan*/ ) ; 
 int STST ; 
 int /*<<< orphan*/  aha1542_intr_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aha1542_outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_mask (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aha1542_test_port(struct Scsi_Host *sh)
{
	u8 inquiry_result[4];
	int i;

	/* Quick and dirty test for presence of the card. */
	if (inb(STATUS(sh->io_port)) == 0xff)
		return 0;

	/* Reset the adapter. I ought to make a hard reset, but it's not really necessary */

	/* In case some other card was probing here, reset interrupts */
	aha1542_intr_reset(sh->io_port);	/* reset interrupts, so they don't block */

	outb(SRST | IRST /*|SCRST */ , CONTROL(sh->io_port));

	mdelay(20);		/* Wait a little bit for things to settle down. */

	/* Expect INIT and IDLE, any of the others are bad */
	if (!wait_mask(STATUS(sh->io_port), STATMASK, INIT | IDLE, STST | DIAGF | INVDCMD | DF | CDF, 0))
		return 0;

	/* Shouldn't have generated any interrupts during reset */
	if (inb(INTRFLAGS(sh->io_port)) & INTRMASK)
		return 0;

	/* Perform a host adapter inquiry instead so we do not need to set
	   up the mailboxes ahead of time */

	aha1542_outb(sh->io_port, CMD_INQUIRY);

	for (i = 0; i < 4; i++) {
		if (!wait_mask(STATUS(sh->io_port), DF, DF, 0, 0))
			return 0;
		inquiry_result[i] = inb(DATA(sh->io_port));
	}

	/* Reading port should reset DF */
	if (inb(STATUS(sh->io_port)) & DF)
		return 0;

	/* When HACC, command is completed, and we're though testing */
	if (!wait_mask(INTRFLAGS(sh->io_port), HACC, HACC, 0, 0))
		return 0;

	/* Clear interrupts */
	outb(IRST, CONTROL(sh->io_port));

	return 1;
}