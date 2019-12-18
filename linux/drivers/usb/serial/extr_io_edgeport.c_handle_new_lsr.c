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
struct edgeport_port {int shadowLSR; TYPE_1__* port; } ;
struct async_icount {int /*<<< orphan*/  frame; int /*<<< orphan*/  parity; int /*<<< orphan*/  overrun; int /*<<< orphan*/  brk; } ;
typedef  int __u8 ;
struct TYPE_2__ {struct async_icount icount; } ;

/* Variables and functions */
 int LSR_BREAK ; 
 int LSR_FRM_ERR ; 
 int LSR_OVER_ERR ; 
 int LSR_PAR_ERR ; 
 int /*<<< orphan*/  edge_tty_recv (TYPE_1__*,int*,int) ; 

__attribute__((used)) static void handle_new_lsr(struct edgeport_port *edge_port, __u8 lsrData,
							__u8 lsr, __u8 data)
{
	__u8 newLsr = (__u8) (lsr & (__u8)
		(LSR_OVER_ERR | LSR_PAR_ERR | LSR_FRM_ERR | LSR_BREAK));
	struct async_icount *icount;

	edge_port->shadowLSR = lsr;

	if (newLsr & LSR_BREAK) {
		/*
		 * Parity and Framing errors only count if they
		 * occur exclusive of a break being
		 * received.
		 */
		newLsr &= (__u8)(LSR_OVER_ERR | LSR_BREAK);
	}

	/* Place LSR data byte into Rx buffer */
	if (lsrData)
		edge_tty_recv(edge_port->port, &data, 1);

	/* update input line counters */
	icount = &edge_port->port->icount;
	if (newLsr & LSR_BREAK)
		icount->brk++;
	if (newLsr & LSR_OVER_ERR)
		icount->overrun++;
	if (newLsr & LSR_PAR_ERR)
		icount->parity++;
	if (newLsr & LSR_FRM_ERR)
		icount->frame++;
}