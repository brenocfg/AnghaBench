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
struct TYPE_2__ {int /*<<< orphan*/  guaranteed; } ;
struct stm_drvdata {int stmspscr; int stmsper; int traceid; int /*<<< orphan*/  numsp; TYPE_1__ chs; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stm_init_default_data(struct stm_drvdata *drvdata)
{
	/* Don't use port selection */
	drvdata->stmspscr = 0x0;
	/*
	 * Enable all channel regardless of their number.  When port
	 * selection isn't used (see above) STMSPER applies to all
	 * 32 channel group available, hence setting all 32 bits to 1
	 */
	drvdata->stmsper = ~0x0;

	/*
	 * The trace ID value for *ETM* tracers start at CPU_ID * 2 + 0x10 and
	 * anything equal to or higher than 0x70 is reserved.  Since 0x00 is
	 * also reserved the STM trace ID needs to be higher than 0x00 and
	 * lowner than 0x10.
	 */
	drvdata->traceid = 0x1;

	/* Set invariant transaction timing on all channels */
	bitmap_clear(drvdata->chs.guaranteed, 0, drvdata->numsp);
}