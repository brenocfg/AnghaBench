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
struct intel_engine_execlists {int csb_size; unsigned int csb_head; int /*<<< orphan*/ * csb_status; int /*<<< orphan*/ * csb_write; } ;
struct intel_engine_cs {struct intel_engine_execlists execlists; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,unsigned int const) ; 
 int /*<<< orphan*/  invalidate_csb_entries (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ring_set_paused (struct intel_engine_cs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void reset_csb_pointers(struct intel_engine_cs *engine)
{
	struct intel_engine_execlists * const execlists = &engine->execlists;
	const unsigned int reset_value = execlists->csb_size - 1;

	ring_set_paused(engine, 0);

	/*
	 * After a reset, the HW starts writing into CSB entry [0]. We
	 * therefore have to set our HEAD pointer back one entry so that
	 * the *first* entry we check is entry 0. To complicate this further,
	 * as we don't wait for the first interrupt after reset, we have to
	 * fake the HW write to point back to the last entry so that our
	 * inline comparison of our cached head position against the last HW
	 * write works even before the first interrupt.
	 */
	execlists->csb_head = reset_value;
	WRITE_ONCE(*execlists->csb_write, reset_value);
	wmb(); /* Make sure this is visible to HW (paranoia?) */

	invalidate_csb_entries(&execlists->csb_status[0],
			       &execlists->csb_status[reset_value]);
}