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
typedef  int u8 ;
typedef  int u16 ;
struct jsm_channel {int ch_r_head; int ch_r_tail; int ch_cached_lsr; int ch_c_iflag; int* ch_equeue; int ch_e_head; int /*<<< orphan*/  ch_lock; int /*<<< orphan*/  ch_rxcount; int /*<<< orphan*/  ch_err_frame; int /*<<< orphan*/  ch_err_break; int /*<<< orphan*/  ch_err_parity; TYPE_1__* ch_cls_uart; void** ch_rqueue; int /*<<< orphan*/  ch_err_overrun; } ;
struct TYPE_2__ {int /*<<< orphan*/  txrx; int /*<<< orphan*/  lsr; } ;

/* Variables and functions */
 int EQUEUEMASK ; 
 int IGNBRK ; 
 int RQUEUEMASK ; 
 int UART_LSR_BI ; 
 int UART_LSR_DR ; 
 int UART_LSR_FE ; 
 int UART_LSR_PE ; 
 void* readb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void cls_copy_data_from_uart_to_queue(struct jsm_channel *ch)
{
	int qleft = 0;
	u8 linestatus = 0;
	u8 error_mask = 0;
	u16 head;
	u16 tail;
	unsigned long flags;

	if (!ch)
		return;

	spin_lock_irqsave(&ch->ch_lock, flags);

	/* cache head and tail of queue */
	head = ch->ch_r_head & RQUEUEMASK;
	tail = ch->ch_r_tail & RQUEUEMASK;

	/* Get our cached LSR */
	linestatus = ch->ch_cached_lsr;
	ch->ch_cached_lsr = 0;

	/* Store how much space we have left in the queue */
	qleft = tail - head - 1;
	if (qleft < 0)
		qleft += RQUEUEMASK + 1;

	/*
	 * Create a mask to determine whether we should
	 * insert the character (if any) into our queue.
	 */
	if (ch->ch_c_iflag & IGNBRK)
		error_mask |= UART_LSR_BI;

	while (1) {
		/*
		 * Grab the linestatus register, we need to
		 * check to see if there is any data to read
		 */
		linestatus = readb(&ch->ch_cls_uart->lsr);

		/* Break out if there is no data to fetch */
		if (!(linestatus & UART_LSR_DR))
			break;

		/*
		 * Discard character if we are ignoring the error mask
		 * which in this case is the break signal.
		 */
		if (linestatus & error_mask)  {
			u8 discard;

			linestatus = 0;
			discard = readb(&ch->ch_cls_uart->txrx);
			continue;
		}

		/*
		 * If our queue is full, we have no choice but to drop some
		 * data. The assumption is that HWFLOW or SWFLOW should have
		 * stopped things way way before we got to this point.
		 *
		 * I decided that I wanted to ditch the oldest data first,
		 * I hope thats okay with everyone? Yes? Good.
		 */
		while (qleft < 1) {
			tail = (tail + 1) & RQUEUEMASK;
			ch->ch_r_tail = tail;
			ch->ch_err_overrun++;
			qleft++;
		}

		ch->ch_equeue[head] = linestatus & (UART_LSR_BI | UART_LSR_PE
								 | UART_LSR_FE);
		ch->ch_rqueue[head] = readb(&ch->ch_cls_uart->txrx);

		qleft--;

		if (ch->ch_equeue[head] & UART_LSR_PE)
			ch->ch_err_parity++;
		if (ch->ch_equeue[head] & UART_LSR_BI)
			ch->ch_err_break++;
		if (ch->ch_equeue[head] & UART_LSR_FE)
			ch->ch_err_frame++;

		/* Add to, and flip head if needed */
		head = (head + 1) & RQUEUEMASK;
		ch->ch_rxcount++;
	}

	/*
	 * Write new final heads to channel structure.
	 */
	ch->ch_r_head = head & RQUEUEMASK;
	ch->ch_e_head = head & EQUEUEMASK;

	spin_unlock_irqrestore(&ch->ch_lock, flags);
}