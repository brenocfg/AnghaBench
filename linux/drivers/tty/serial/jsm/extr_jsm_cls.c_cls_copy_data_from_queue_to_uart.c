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
typedef  scalar_t__ u32 ;
typedef  size_t u16 ;
struct TYPE_6__ {TYPE_1__* state; } ;
struct jsm_channel {int ch_flags; scalar_t__ ch_t_tlevel; TYPE_3__ uart_port; int /*<<< orphan*/  ch_txcount; TYPE_2__* ch_cls_uart; } ;
struct circ_buf {int tail; int /*<<< orphan*/ * buf; } ;
struct TYPE_5__ {int /*<<< orphan*/  txrx; } ;
struct TYPE_4__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int CH_BREAK_SENDING ; 
 int CH_STOP ; 
 int CH_TX_FIFO_EMPTY ; 
 int CH_TX_FIFO_LWM ; 
 int UART_XMIT_SIZE ; 
 int min (int,int) ; 
 int uart_circ_chars_pending (struct circ_buf*) ; 
 scalar_t__ uart_circ_empty (struct circ_buf*) ; 
 int /*<<< orphan*/  uart_write_wakeup (TYPE_3__*) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cls_copy_data_from_queue_to_uart(struct jsm_channel *ch)
{
	u16 tail;
	int n;
	int qlen;
	u32 len_written = 0;
	struct circ_buf *circ;

	if (!ch)
		return;

	circ = &ch->uart_port.state->xmit;

	/* No data to write to the UART */
	if (uart_circ_empty(circ))
		return;

	/* If port is "stopped", don't send any data to the UART */
	if ((ch->ch_flags & CH_STOP) || (ch->ch_flags & CH_BREAK_SENDING))
		return;

	/* We have to do it this way, because of the EXAR TXFIFO count bug. */
	if (!(ch->ch_flags & (CH_TX_FIFO_EMPTY | CH_TX_FIFO_LWM)))
		return;

	n = 32;

	/* cache tail of queue */
	tail = circ->tail & (UART_XMIT_SIZE - 1);
	qlen = uart_circ_chars_pending(circ);

	/* Find minimum of the FIFO space, versus queue length */
	n = min(n, qlen);

	while (n > 0) {
		writeb(circ->buf[tail], &ch->ch_cls_uart->txrx);
		tail = (tail + 1) & (UART_XMIT_SIZE - 1);
		n--;
		ch->ch_txcount++;
		len_written++;
	}

	/* Update the final tail */
	circ->tail = tail & (UART_XMIT_SIZE - 1);

	if (len_written > ch->ch_t_tlevel)
		ch->ch_flags &= ~(CH_TX_FIFO_EMPTY | CH_TX_FIFO_LWM);

	if (uart_circ_empty(circ))
		uart_write_wakeup(&ch->uart_port);
}