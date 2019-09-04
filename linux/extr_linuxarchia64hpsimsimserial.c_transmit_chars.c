#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {scalar_t__ stopped; } ;
struct TYPE_6__ {int head; int tail; char* buf; } ;
struct serial_state {char x_char; TYPE_1__ xmit; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* write ) (TYPE_2__*,char*,int) ;} ;

/* Variables and functions */
 int CIRC_CNT (int,int,int) ; 
 int SERIAL_XMIT_SIZE ; 
 TYPE_2__* console ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,char*,int) ; 

__attribute__((used)) static void transmit_chars(struct tty_struct *tty, struct serial_state *info,
		int *intr_done)
{
	int count;
	unsigned long flags;

	local_irq_save(flags);

	if (info->x_char) {
		char c = info->x_char;

		console->write(console, &c, 1);

		info->x_char = 0;

		goto out;
	}

	if (info->xmit.head == info->xmit.tail || tty->stopped) {
#ifdef SIMSERIAL_DEBUG
		printk("transmit_chars: head=%d, tail=%d, stopped=%d\n",
		       info->xmit.head, info->xmit.tail, tty->stopped);
#endif
		goto out;
	}
	/*
	 * We removed the loop and try to do it in to chunks. We need
	 * 2 operations maximum because it's a ring buffer.
	 *
	 * First from current to tail if possible.
	 * Then from the beginning of the buffer until necessary
	 */

	count = min(CIRC_CNT(info->xmit.head, info->xmit.tail, SERIAL_XMIT_SIZE),
		    SERIAL_XMIT_SIZE - info->xmit.tail);
	console->write(console, info->xmit.buf+info->xmit.tail, count);

	info->xmit.tail = (info->xmit.tail+count) & (SERIAL_XMIT_SIZE-1);

	/*
	 * We have more at the beginning of the buffer
	 */
	count = CIRC_CNT(info->xmit.head, info->xmit.tail, SERIAL_XMIT_SIZE);
	if (count) {
		console->write(console, info->xmit.buf, count);
		info->xmit.tail += count;
	}
out:
	local_irq_restore(flags);
}