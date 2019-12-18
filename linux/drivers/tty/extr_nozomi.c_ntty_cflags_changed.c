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
struct async_icount {scalar_t__ rng; scalar_t__ dsr; scalar_t__ dcd; scalar_t__ cts; } ;
struct port {struct async_icount tty_icount; } ;

/* Variables and functions */
 unsigned long TIOCM_CD ; 
 unsigned long TIOCM_CTS ; 
 unsigned long TIOCM_DSR ; 
 unsigned long TIOCM_RNG ; 

__attribute__((used)) static int ntty_cflags_changed(struct port *port, unsigned long flags,
		struct async_icount *cprev)
{
	const struct async_icount cnow = port->tty_icount;
	int ret;

	ret = ((flags & TIOCM_RNG) && (cnow.rng != cprev->rng))
		|| ((flags & TIOCM_DSR) && (cnow.dsr != cprev->dsr))
		|| ((flags & TIOCM_CD)  && (cnow.dcd != cprev->dcd))
		|| ((flags & TIOCM_CTS) && (cnow.cts != cprev->cts));

	*cprev = cnow;

	return ret;
}