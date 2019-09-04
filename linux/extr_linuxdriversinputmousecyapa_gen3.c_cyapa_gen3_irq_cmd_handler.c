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
struct cyapa {scalar_t__ gen; scalar_t__ operational; } ;

/* Variables and functions */
 scalar_t__ CYAPA_GEN3 ; 

__attribute__((used)) static bool cyapa_gen3_irq_cmd_handler(struct cyapa *cyapa)
{
	/* Not gen3 irq command response, skip for continue. */
	if (cyapa->gen != CYAPA_GEN3)
		return true;

	if (cyapa->operational)
		return true;

	/*
	 * Driver in detecting or other interface function processing,
	 * so, stop cyapa_gen3_irq_handler to continue process to
	 * avoid unwanted to error detecting and processing.
	 *
	 * And also, avoid the periodically asserted interrupts to be processed
	 * as touch inputs when gen3 failed to launch into application mode,
	 * which will cause gen3 stays in bootloader mode.
	 */
	return false;
}