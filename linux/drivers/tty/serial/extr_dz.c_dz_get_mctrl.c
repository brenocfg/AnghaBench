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
struct uart_port {int dummy; } ;
struct TYPE_2__ {scalar_t__ line; } ;
struct dz_port {TYPE_1__ port; } ;

/* Variables and functions */
 scalar_t__ DZ_MODEM ; 
 int DZ_MODEM_DSR ; 
 int /*<<< orphan*/  DZ_MSR ; 
 unsigned int TIOCM_CAR ; 
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_DSR ; 
 int dz_in (struct dz_port*,int /*<<< orphan*/ ) ; 
 struct dz_port* to_dport (struct uart_port*) ; 

__attribute__((used)) static unsigned int dz_get_mctrl(struct uart_port *uport)
{
	/*
	 * FIXME: Handle the 3100/5000 as appropriate. --macro
	 */
	struct dz_port *dport = to_dport(uport);
	unsigned int mctrl = TIOCM_CAR | TIOCM_DSR | TIOCM_CTS;

	if (dport->port.line == DZ_MODEM) {
		if (dz_in(dport, DZ_MSR) & DZ_MODEM_DSR)
			mctrl &= ~TIOCM_DSR;
	}

	return mctrl;
}