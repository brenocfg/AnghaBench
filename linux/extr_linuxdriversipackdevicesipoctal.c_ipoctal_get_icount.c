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
struct tty_struct {struct ipoctal_channel* driver_data; } ;
struct serial_icounter_struct {int /*<<< orphan*/  brk; int /*<<< orphan*/  parity; int /*<<< orphan*/  frame; int /*<<< orphan*/  tx; int /*<<< orphan*/  rx; scalar_t__ dcd; scalar_t__ rng; scalar_t__ dsr; scalar_t__ cts; } ;
struct TYPE_2__ {int /*<<< orphan*/  rcv_break; int /*<<< orphan*/  parity_err; int /*<<< orphan*/  framing_err; int /*<<< orphan*/  tx; int /*<<< orphan*/  rx; } ;
struct ipoctal_channel {TYPE_1__ stats; } ;

/* Variables and functions */

__attribute__((used)) static int ipoctal_get_icount(struct tty_struct *tty,
			      struct serial_icounter_struct *icount)
{
	struct ipoctal_channel *channel = tty->driver_data;

	icount->cts = 0;
	icount->dsr = 0;
	icount->rng = 0;
	icount->dcd = 0;
	icount->rx = channel->stats.rx;
	icount->tx = channel->stats.tx;
	icount->frame = channel->stats.framing_err;
	icount->parity = channel->stats.parity_err;
	icount->brk = channel->stats.rcv_break;
	return 0;
}