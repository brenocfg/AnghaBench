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
struct intel_engine_execlists {int /*<<< orphan*/  csb_write_reset; int /*<<< orphan*/ * csb_write; int /*<<< orphan*/  csb_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reset_csb_pointers(struct intel_engine_execlists *execlists)
{
	/*
	 * After a reset, the HW starts writing into CSB entry [0]. We
	 * therefore have to set our HEAD pointer back one entry so that
	 * the *first* entry we check is entry 0. To complicate this further,
	 * as we don't wait for the first interrupt after reset, we have to
	 * fake the HW write to point back to the last entry so that our
	 * inline comparison of our cached head position against the last HW
	 * write works even before the first interrupt.
	 */
	execlists->csb_head = execlists->csb_write_reset;
	WRITE_ONCE(*execlists->csb_write, execlists->csb_write_reset);
}