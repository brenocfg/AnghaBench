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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct scx200_acb_iface {size_t state; int needs_reset; int /*<<< orphan*/  result; TYPE_1__ adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACBST ; 
 int ACBST_BER ; 
 int ACBST_NEGACK ; 
 int ACBST_SDAST ; 
 int /*<<< orphan*/  EIO ; 
 unsigned long POLL_TIMEOUT ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int inb (int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scx200_acb_machine (struct scx200_acb_iface*,int) ; 
 int /*<<< orphan*/ * scx200_acb_state_name ; 
 size_t state_idle ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static void scx200_acb_poll(struct scx200_acb_iface *iface)
{
	u8 status;
	unsigned long timeout;

	timeout = jiffies + POLL_TIMEOUT;
	while (1) {
		status = inb(ACBST);

		/* Reset the status register to avoid the hang */
		outb(0, ACBST);

		if ((status & (ACBST_SDAST|ACBST_BER|ACBST_NEGACK)) != 0) {
			scx200_acb_machine(iface, status);
			return;
		}
		if (time_after(jiffies, timeout))
			break;
		cpu_relax();
		cond_resched();
	}

	dev_err(&iface->adapter.dev, "timeout in state %s\n",
		scx200_acb_state_name[iface->state]);

	iface->state = state_idle;
	iface->result = -EIO;
	iface->needs_reset = 1;
}