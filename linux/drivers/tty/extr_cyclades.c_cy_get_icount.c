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
struct tty_struct {struct cyclades_port* driver_data; } ;
struct serial_icounter_struct {int /*<<< orphan*/  buf_overrun; int /*<<< orphan*/  brk; int /*<<< orphan*/  parity; int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  tx; int /*<<< orphan*/  rx; int /*<<< orphan*/  dcd; int /*<<< orphan*/  rng; int /*<<< orphan*/  dsr; int /*<<< orphan*/  cts; } ;
struct cyclades_icount {int /*<<< orphan*/  buf_overrun; int /*<<< orphan*/  brk; int /*<<< orphan*/  parity; int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  tx; int /*<<< orphan*/  rx; int /*<<< orphan*/  dcd; int /*<<< orphan*/  rng; int /*<<< orphan*/  dsr; int /*<<< orphan*/  cts; } ;
struct cyclades_port {TYPE_1__* card; struct cyclades_icount icount; } ;
struct TYPE_2__ {int /*<<< orphan*/  card_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int cy_get_icount(struct tty_struct *tty,
				struct serial_icounter_struct *sic)
{
	struct cyclades_port *info = tty->driver_data;
	struct cyclades_icount cnow;	/* Used to snapshot */
	unsigned long flags;

	spin_lock_irqsave(&info->card->card_lock, flags);
	cnow = info->icount;
	spin_unlock_irqrestore(&info->card->card_lock, flags);

	sic->cts = cnow.cts;
	sic->dsr = cnow.dsr;
	sic->rng = cnow.rng;
	sic->dcd = cnow.dcd;
	sic->rx = cnow.rx;
	sic->tx = cnow.tx;
	sic->frame = cnow.frame;
	sic->overrun = cnow.overrun;
	sic->parity = cnow.parity;
	sic->brk = cnow.brk;
	sic->buf_overrun = cnow.buf_overrun;
	return 0;
}