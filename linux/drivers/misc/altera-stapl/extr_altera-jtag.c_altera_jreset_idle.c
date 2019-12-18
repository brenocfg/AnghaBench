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
struct altera_jtag {int /*<<< orphan*/  jtag_state; } ;
struct altera_state {struct altera_jtag js; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDLE ; 
 int /*<<< orphan*/  IGNORE_TDO ; 
 int /*<<< orphan*/  TDI_LOW ; 
 int /*<<< orphan*/  TMS_HIGH ; 
 int /*<<< orphan*/  TMS_LOW ; 
 int /*<<< orphan*/  alt_jtag_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void altera_jreset_idle(struct altera_state *astate)
{
	struct altera_jtag *js = &astate->js;
	int i;
	/* Go to Test Logic Reset (no matter what the starting state may be) */
	for (i = 0; i < 5; ++i)
		alt_jtag_io(TMS_HIGH, TDI_LOW, IGNORE_TDO);

	/* Now step to Run Test / Idle */
	alt_jtag_io(TMS_LOW, TDI_LOW, IGNORE_TDO);
	js->jtag_state = IDLE;
}