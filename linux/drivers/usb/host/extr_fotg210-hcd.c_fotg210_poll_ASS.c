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
struct fotg210_hcd {scalar_t__ rh_state; int command; scalar_t__ async_count; scalar_t__ ASS_poll_count; TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int CMD_ASE ; 
 int /*<<< orphan*/  FOTG210_HRTIMER_DISABLE_ASYNC ; 
 int /*<<< orphan*/  FOTG210_HRTIMER_POLL_ASS ; 
 scalar_t__ FOTG210_RH_RUNNING ; 
 unsigned int STS_ASS ; 
 int /*<<< orphan*/  fotg210_dbg (struct fotg210_hcd*,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  fotg210_enable_event (struct fotg210_hcd*,int /*<<< orphan*/ ,int) ; 
 unsigned int fotg210_readl (struct fotg210_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fotg210_set_command_bit (struct fotg210_hcd*,int) ; 

__attribute__((used)) static void fotg210_poll_ASS(struct fotg210_hcd *fotg210)
{
	unsigned actual, want;

	/* Don't enable anything if the controller isn't running (e.g., died) */
	if (fotg210->rh_state != FOTG210_RH_RUNNING)
		return;

	want = (fotg210->command & CMD_ASE) ? STS_ASS : 0;
	actual = fotg210_readl(fotg210, &fotg210->regs->status) & STS_ASS;

	if (want != actual) {

		/* Poll again later, but give up after about 20 ms */
		if (fotg210->ASS_poll_count++ < 20) {
			fotg210_enable_event(fotg210, FOTG210_HRTIMER_POLL_ASS,
					true);
			return;
		}
		fotg210_dbg(fotg210, "Waited too long for the async schedule status (%x/%x), giving up\n",
				want, actual);
	}
	fotg210->ASS_poll_count = 0;

	/* The status is up-to-date; restart or stop the schedule as needed */
	if (want == 0) {	/* Stopped */
		if (fotg210->async_count > 0)
			fotg210_set_command_bit(fotg210, CMD_ASE);

	} else {		/* Running */
		if (fotg210->async_count == 0) {

			/* Turn off the schedule after a while */
			fotg210_enable_event(fotg210,
					FOTG210_HRTIMER_DISABLE_ASYNC,
					true);
		}
	}
}