#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct tty_port {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  rcv_break; int /*<<< orphan*/  framing_err; int /*<<< orphan*/  parity_err; int /*<<< orphan*/  overrun_err; } ;
struct ipoctal_channel {int isr_rx_rdy_mask; TYPE_6__* regs; TYPE_4__* block_regs; TYPE_2__ stats; struct tty_port tty_port; } ;
struct TYPE_11__ {int /*<<< orphan*/  sr; int /*<<< orphan*/  rhr; } ;
struct TYPE_7__ {int /*<<< orphan*/  cr; } ;
struct TYPE_12__ {TYPE_5__ r; TYPE_1__ w; } ;
struct TYPE_9__ {int /*<<< orphan*/  isr; } ;
struct TYPE_10__ {TYPE_3__ r; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_CMD_RESET_ERR_STATUS ; 
 int SR_ERROR ; 
 int SR_FRAMING_ERROR ; 
 int SR_OVERRUN_ERROR ; 
 int SR_PARITY_ERROR ; 
 int SR_RECEIVED_BREAK ; 
 unsigned char TTY_BREAK ; 
 unsigned char TTY_FRAME ; 
 unsigned char TTY_NORMAL ; 
 unsigned char TTY_OVERRUN ; 
 unsigned char TTY_PARITY ; 
 void* ioread8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite8 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_port*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_port*,unsigned char,unsigned char) ; 

__attribute__((used)) static void ipoctal_irq_rx(struct ipoctal_channel *channel, u8 sr)
{
	struct tty_port *port = &channel->tty_port;
	unsigned char value;
	unsigned char flag;
	u8 isr;

	do {
		value = ioread8(&channel->regs->r.rhr);
		flag = TTY_NORMAL;
		/* Error: count statistics */
		if (sr & SR_ERROR) {
			iowrite8(CR_CMD_RESET_ERR_STATUS, &channel->regs->w.cr);

			if (sr & SR_OVERRUN_ERROR) {
				channel->stats.overrun_err++;
				/* Overrun doesn't affect the current character*/
				tty_insert_flip_char(port, 0, TTY_OVERRUN);
			}
			if (sr & SR_PARITY_ERROR) {
				channel->stats.parity_err++;
				flag = TTY_PARITY;
			}
			if (sr & SR_FRAMING_ERROR) {
				channel->stats.framing_err++;
				flag = TTY_FRAME;
			}
			if (sr & SR_RECEIVED_BREAK) {
				channel->stats.rcv_break++;
				flag = TTY_BREAK;
			}
		}
		tty_insert_flip_char(port, value, flag);

		/* Check if there are more characters in RX FIFO
		 * If there are more, the isr register for this channel
		 * has enabled the RxRDY|FFULL bit.
		 */
		isr = ioread8(&channel->block_regs->r.isr);
		sr = ioread8(&channel->regs->r.sr);
	} while (isr & channel->isr_rx_rdy_mask);

	tty_flip_buffer_push(port);
}