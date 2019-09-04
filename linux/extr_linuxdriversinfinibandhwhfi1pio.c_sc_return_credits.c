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
struct send_context {int /*<<< orphan*/  hw_context; int /*<<< orphan*/  dd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CREDIT_FORCE ; 
 int /*<<< orphan*/  CREDIT_FORCE_FORCE_RETURN_SMASK ; 
 int /*<<< orphan*/  SC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_kctxt_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_kctxt_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sc_return_credits(struct send_context *sc)
{
	if (!sc)
		return;

	/* a 0->1 transition schedules a credit return */
	write_kctxt_csr(sc->dd, sc->hw_context, SC(CREDIT_FORCE),
			SC(CREDIT_FORCE_FORCE_RETURN_SMASK));
	/*
	 * Ensure that the write is flushed and the credit return is
	 * scheduled. We care more about the 0 -> 1 transition.
	 */
	read_kctxt_csr(sc->dd, sc->hw_context, SC(CREDIT_FORCE));
	/* set back to 0 for next time */
	write_kctxt_csr(sc->dd, sc->hw_context, SC(CREDIT_FORCE), 0);
}