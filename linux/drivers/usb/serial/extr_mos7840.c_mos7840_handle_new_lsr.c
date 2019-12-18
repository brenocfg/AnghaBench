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
struct moschip_port {TYPE_1__* port; } ;
struct async_icount {int /*<<< orphan*/  frame; int /*<<< orphan*/  parity; int /*<<< orphan*/  overrun; int /*<<< orphan*/  brk; } ;
typedef  int __u8 ;
struct TYPE_2__ {struct async_icount icount; } ;

/* Variables and functions */
 int SERIAL_LSR_BI ; 
 int SERIAL_LSR_FE ; 
 int SERIAL_LSR_OE ; 
 int SERIAL_LSR_PE ; 

__attribute__((used)) static void mos7840_handle_new_lsr(struct moschip_port *port, __u8 new_lsr)
{
	struct async_icount *icount;

	if (new_lsr & SERIAL_LSR_BI) {
		/*
		 * Parity and Framing errors only count if they
		 * occur exclusive of a break being
		 * received.
		 */
		new_lsr &= (__u8) (SERIAL_LSR_OE | SERIAL_LSR_BI);
	}

	/* update input line counters */
	icount = &port->port->icount;
	if (new_lsr & SERIAL_LSR_BI)
		icount->brk++;
	if (new_lsr & SERIAL_LSR_OE)
		icount->overrun++;
	if (new_lsr & SERIAL_LSR_PE)
		icount->parity++;
	if (new_lsr & SERIAL_LSR_FE)
		icount->frame++;
}