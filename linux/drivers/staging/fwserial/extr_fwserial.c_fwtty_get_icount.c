#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {struct fwtty_port* driver_data; } ;
struct stats {scalar_t__ xchars; } ;
struct serial_icounter_struct {int /*<<< orphan*/  buf_overrun; int /*<<< orphan*/  brk; int /*<<< orphan*/  parity; int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; scalar_t__ tx; int /*<<< orphan*/  rx; int /*<<< orphan*/  dcd; int /*<<< orphan*/  rng; int /*<<< orphan*/  dsr; int /*<<< orphan*/  cts; } ;
struct TYPE_6__ {int /*<<< orphan*/  overrun; int /*<<< orphan*/  brk; int /*<<< orphan*/  parity; int /*<<< orphan*/  frame; scalar_t__ tx; int /*<<< orphan*/  rx; int /*<<< orphan*/  dcd; int /*<<< orphan*/  rng; int /*<<< orphan*/  dsr; int /*<<< orphan*/  cts; } ;
struct TYPE_4__ {scalar_t__ console; } ;
struct fwtty_port {TYPE_3__ icount; int /*<<< orphan*/  con_data; TYPE_2__* fwcon_ops; TYPE_1__ port; int /*<<< orphan*/  stats; } ;
typedef  int /*<<< orphan*/  stats ;
struct TYPE_5__ {int /*<<< orphan*/  (* stats ) (struct stats*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct stats*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (struct stats*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fwtty_get_icount(struct tty_struct *tty,
			    struct serial_icounter_struct *icount)
{
	struct fwtty_port *port = tty->driver_data;
	struct stats stats;

	memcpy(&stats, &port->stats, sizeof(stats));
	if (port->port.console)
		(*port->fwcon_ops->stats)(&stats, port->con_data);

	icount->cts = port->icount.cts;
	icount->dsr = port->icount.dsr;
	icount->rng = port->icount.rng;
	icount->dcd = port->icount.dcd;
	icount->rx  = port->icount.rx;
	icount->tx  = port->icount.tx + stats.xchars;
	icount->frame   = port->icount.frame;
	icount->overrun = port->icount.overrun;
	icount->parity  = port->icount.parity;
	icount->brk     = port->icount.brk;
	icount->buf_overrun = port->icount.overrun;
	return 0;
}