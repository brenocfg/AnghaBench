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
struct altera_jtag {scalar_t__ jtag_state; } ;
struct altera_state {struct altera_jtag js; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  enum altera_jtag_state { ____Placeholder_altera_jtag_state } altera_jtag_state ;

/* Variables and functions */
 scalar_t__ ILLEGAL_JTAG_STATE ; 
 int altera_goto_jstate (struct altera_state*,int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

int altera_wait_msecs(struct altera_state *astate,
			s32 microseconds, enum altera_jtag_state wait_state)
/*
 * Causes JTAG hardware to sit in the specified stable
 * state for the specified duration of real time.  If
 * no JTAG operations have been performed yet, then only
 * a delay is performed.  This permits the WAIT USECS
 * statement to be used in VECTOR programs without causing
 * any JTAG operations.
 * Returns 0 for success, else appropriate error code.
 */
{
	struct altera_jtag *js = &astate->js;
	int status = 0;

	if ((js->jtag_state != ILLEGAL_JTAG_STATE) &&
	    (js->jtag_state != wait_state))
		status = altera_goto_jstate(astate, wait_state);

	if (status == 0)
		/* Wait for specified time interval */
		udelay(microseconds);

	return status;
}