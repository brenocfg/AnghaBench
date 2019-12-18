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
struct uart_pmac_port {int /*<<< orphan*/  curregs; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMACZILOG_FLAG_REGS_HELD ; 
 int /*<<< orphan*/  ZS_REGS_HELD (struct uart_pmac_port*) ; 
 scalar_t__ ZS_TX_ACTIVE (struct uart_pmac_port*) ; 
 int /*<<< orphan*/  pmz_debug (char*) ; 
 int /*<<< orphan*/  pmz_load_zsregs (struct uart_pmac_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pmz_maybe_update_regs(struct uart_pmac_port *uap)
{
	if (!ZS_REGS_HELD(uap)) {
		if (ZS_TX_ACTIVE(uap)) {
			uap->flags |= PMACZILOG_FLAG_REGS_HELD;
		} else {
			pmz_debug("pmz: maybe_update_regs: updating\n");
			pmz_load_zsregs(uap, uap->curregs);
		}
	}
}