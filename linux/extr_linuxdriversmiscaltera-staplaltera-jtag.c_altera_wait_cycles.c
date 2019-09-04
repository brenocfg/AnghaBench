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
struct altera_jtag {int jtag_state; } ;
struct altera_state {struct altera_jtag js; } ;
typedef  long s32 ;
typedef  enum altera_jtag_state { ____Placeholder_altera_jtag_state } altera_jtag_state ;

/* Variables and functions */
 int /*<<< orphan*/  IGNORE_TDO ; 
 int RESET ; 
 int /*<<< orphan*/  TDI_LOW ; 
 int TMS_HIGH ; 
 int TMS_LOW ; 
 int /*<<< orphan*/  alt_jtag_io (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int altera_goto_jstate (struct altera_state*,int) ; 

int altera_wait_cycles(struct altera_state *astate,
					s32 cycles,
					enum altera_jtag_state wait_state)
{
	struct altera_jtag *js = &astate->js;
	int tms;
	s32 count;
	int status = 0;

	if (js->jtag_state != wait_state)
		status = altera_goto_jstate(astate, wait_state);

	if (status == 0) {
		/*
		 * Set TMS high to loop in RESET state
		 * Set TMS low to loop in any other stable state
		 */
		tms = (wait_state == RESET) ? TMS_HIGH : TMS_LOW;

		for (count = 0L; count < cycles; count++)
			alt_jtag_io(tms, TDI_LOW, IGNORE_TDO);

	}

	return status;
}