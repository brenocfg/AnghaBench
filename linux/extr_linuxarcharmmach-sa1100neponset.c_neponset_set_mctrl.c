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
typedef  int u_int ;
struct uart_port {scalar_t__ mapbase; } ;
struct neponset_drvdata {TYPE_1__** gpio; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_multiple ) (TYPE_1__*,unsigned long*,unsigned long*) ;} ;

/* Variables and functions */
 unsigned long MDM_CTL0_DTR1 ; 
 unsigned long MDM_CTL0_DTR2 ; 
 unsigned long MDM_CTL0_RTS1 ; 
 unsigned long MDM_CTL0_RTS2 ; 
 int TIOCM_DTR ; 
 int TIOCM_RTS ; 
 scalar_t__ _Ser1UTCR0 ; 
 scalar_t__ _Ser3UTCR0 ; 
 struct neponset_drvdata* nep ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,unsigned long*,unsigned long*) ; 

__attribute__((used)) static void neponset_set_mctrl(struct uart_port *port, u_int mctrl)
{
	struct neponset_drvdata *n = nep;
	unsigned long mask, val = 0;

	if (!n)
		return;

	if (port->mapbase == _Ser1UTCR0) {
		mask = MDM_CTL0_RTS2 | MDM_CTL0_DTR2;

		if (!(mctrl & TIOCM_RTS))
			val |= MDM_CTL0_RTS2;

		if (!(mctrl & TIOCM_DTR))
			val |= MDM_CTL0_DTR2;
	} else if (port->mapbase == _Ser3UTCR0) {
		mask = MDM_CTL0_RTS1 | MDM_CTL0_DTR1;

		if (!(mctrl & TIOCM_RTS))
			val |= MDM_CTL0_RTS1;

		if (!(mctrl & TIOCM_DTR))
			val |= MDM_CTL0_DTR1;
	}

	n->gpio[1]->set_multiple(n->gpio[1], &mask, &val);
}