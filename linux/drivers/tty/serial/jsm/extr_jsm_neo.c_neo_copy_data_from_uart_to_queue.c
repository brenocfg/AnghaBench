#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct jsm_channel {int ch_r_head; int ch_r_tail; int ch_cached_lsr; int ch_flags; int* ch_rqueue; int* ch_equeue; int ch_c_iflag; int ch_e_head; scalar_t__ ch_rxcount; TYPE_2__* ch_bd; TYPE_1__* ch_neo_uart; int /*<<< orphan*/  ch_err_overrun; } ;
struct TYPE_4__ {int /*<<< orphan*/  pci_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  txrxburst; int /*<<< orphan*/  lsr; int /*<<< orphan*/  rfifo; } ;

/* Variables and functions */
 int CH_FIFO_ENABLED ; 
 int CH_TX_FIFO_EMPTY ; 
 int CH_TX_FIFO_LWM ; 
 int EQUEUEMASK ; 
 int IGNBRK ; 
 int /*<<< orphan*/  READ ; 
 int RQUEUEMASK ; 
 int RQUEUESIZE ; 
 int UART_17158_RX_FIFO_DATA_ERROR ; 
 int UART_17158_TX_AND_FIFO_CLR ; 
 int UART_LSR_BI ; 
 int UART_LSR_DR ; 
 int UART_LSR_THRE ; 
 int /*<<< orphan*/  jsm_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  jsm_input (struct jsm_channel*) ; 
 int /*<<< orphan*/  memcpy_fromio (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 
 int readb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void neo_copy_data_from_uart_to_queue(struct jsm_channel *ch)
{
	int qleft = 0;
	u8 linestatus = 0;
	u8 error_mask = 0;
	int n = 0;
	int total = 0;
	u16 head;
	u16 tail;

	/* cache head and tail of queue */
	head = ch->ch_r_head & RQUEUEMASK;
	tail = ch->ch_r_tail & RQUEUEMASK;

	/* Get our cached LSR */
	linestatus = ch->ch_cached_lsr;
	ch->ch_cached_lsr = 0;

	/* Store how much space we have left in the queue */
	if ((qleft = tail - head - 1) < 0)
		qleft += RQUEUEMASK + 1;

	/*
	 * If the UART is not in FIFO mode, force the FIFO copy to
	 * NOT be run, by setting total to 0.
	 *
	 * On the other hand, if the UART IS in FIFO mode, then ask
	 * the UART to give us an approximation of data it has RX'ed.
	 */
	if (!(ch->ch_flags & CH_FIFO_ENABLED))
		total = 0;
	else {
		total = readb(&ch->ch_neo_uart->rfifo);

		/*
		 * EXAR chip bug - RX FIFO COUNT - Fudge factor.
		 *
		 * This resolves a problem/bug with the Exar chip that sometimes
		 * returns a bogus value in the rfifo register.
		 * The count can be any where from 0-3 bytes "off".
		 * Bizarre, but true.
		 */
		total -= 3;
	}

	/*
	 * Finally, bound the copy to make sure we don't overflow
	 * our own queue...
	 * The byte by byte copy loop below this loop this will
	 * deal with the queue overflow possibility.
	 */
	total = min(total, qleft);

	while (total > 0) {
		/*
		 * Grab the linestatus register, we need to check
		 * to see if there are any errors in the FIFO.
		 */
		linestatus = readb(&ch->ch_neo_uart->lsr);

		/*
		 * Break out if there is a FIFO error somewhere.
		 * This will allow us to go byte by byte down below,
		 * finding the exact location of the error.
		 */
		if (linestatus & UART_17158_RX_FIFO_DATA_ERROR)
			break;

		/* Make sure we don't go over the end of our queue */
		n = min(((u32) total), (RQUEUESIZE - (u32) head));

		/*
		 * Cut down n even further if needed, this is to fix
		 * a problem with memcpy_fromio() with the Neo on the
		 * IBM pSeries platform.
		 * 15 bytes max appears to be the magic number.
		 */
		n = min((u32) n, (u32) 12);

		/*
		 * Since we are grabbing the linestatus register, which
		 * will reset some bits after our read, we need to ensure
		 * we don't miss our TX FIFO emptys.
		 */
		if (linestatus & (UART_LSR_THRE | UART_17158_TX_AND_FIFO_CLR))
			ch->ch_flags |= (CH_TX_FIFO_EMPTY | CH_TX_FIFO_LWM);

		linestatus = 0;

		/* Copy data from uart to the queue */
		memcpy_fromio(ch->ch_rqueue + head, &ch->ch_neo_uart->txrxburst, n);
		/*
		 * Since RX_FIFO_DATA_ERROR was 0, we are guaranteed
		 * that all the data currently in the FIFO is free of
		 * breaks and parity/frame/orun errors.
		 */
		memset(ch->ch_equeue + head, 0, n);

		/* Add to and flip head if needed */
		head = (head + n) & RQUEUEMASK;
		total -= n;
		qleft -= n;
		ch->ch_rxcount += n;
	}

	/*
	 * Create a mask to determine whether we should
	 * insert the character (if any) into our queue.
	 */
	if (ch->ch_c_iflag & IGNBRK)
		error_mask |= UART_LSR_BI;

	/*
	 * Now cleanup any leftover bytes still in the UART.
	 * Also deal with any possible queue overflow here as well.
	 */
	while (1) {

		/*
		 * Its possible we have a linestatus from the loop above
		 * this, so we "OR" on any extra bits.
		 */
		linestatus |= readb(&ch->ch_neo_uart->lsr);

		/*
		 * If the chip tells us there is no more data pending to
		 * be read, we can then leave.
		 * But before we do, cache the linestatus, just in case.
		 */
		if (!(linestatus & UART_LSR_DR)) {
			ch->ch_cached_lsr = linestatus;
			break;
		}

		/* No need to store this bit */
		linestatus &= ~UART_LSR_DR;

		/*
		 * Since we are grabbing the linestatus register, which
		 * will reset some bits after our read, we need to ensure
		 * we don't miss our TX FIFO emptys.
		 */
		if (linestatus & (UART_LSR_THRE | UART_17158_TX_AND_FIFO_CLR)) {
			linestatus &= ~(UART_LSR_THRE | UART_17158_TX_AND_FIFO_CLR);
			ch->ch_flags |= (CH_TX_FIFO_EMPTY | CH_TX_FIFO_LWM);
		}

		/*
		 * Discard character if we are ignoring the error mask.
		 */
		if (linestatus & error_mask) {
			u8 discard;
			linestatus = 0;
			memcpy_fromio(&discard, &ch->ch_neo_uart->txrxburst, 1);
			continue;
		}

		/*
		 * If our queue is full, we have no choice but to drop some data.
		 * The assumption is that HWFLOW or SWFLOW should have stopped
		 * things way way before we got to this point.
		 *
		 * I decided that I wanted to ditch the oldest data first,
		 * I hope thats okay with everyone? Yes? Good.
		 */
		while (qleft < 1) {
			jsm_dbg(READ, &ch->ch_bd->pci_dev,
				"Queue full, dropping DATA:%x LSR:%x\n",
				ch->ch_rqueue[tail], ch->ch_equeue[tail]);

			ch->ch_r_tail = tail = (tail + 1) & RQUEUEMASK;
			ch->ch_err_overrun++;
			qleft++;
		}

		memcpy_fromio(ch->ch_rqueue + head, &ch->ch_neo_uart->txrxburst, 1);
		ch->ch_equeue[head] = (u8) linestatus;

		jsm_dbg(READ, &ch->ch_bd->pci_dev, "DATA/LSR pair: %x %x\n",
			ch->ch_rqueue[head], ch->ch_equeue[head]);

		/* Ditch any remaining linestatus value. */
		linestatus = 0;

		/* Add to and flip head if needed */
		head = (head + 1) & RQUEUEMASK;

		qleft--;
		ch->ch_rxcount++;
	}

	/*
	 * Write new final heads to channel structure.
	 */
	ch->ch_r_head = head & RQUEUEMASK;
	ch->ch_e_head = head & EQUEUEMASK;
	jsm_input(ch);
}