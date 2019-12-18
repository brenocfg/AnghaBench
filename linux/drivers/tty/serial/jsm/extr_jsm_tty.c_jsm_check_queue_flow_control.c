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
struct jsm_channel {int ch_r_tail; int ch_r_head; int ch_c_cflag; int ch_flags; int ch_c_iflag; TYPE_1__* ch_bd; int /*<<< orphan*/  ch_stops_sent; } ;
struct board_ops {int /*<<< orphan*/  (* send_start_character ) (struct jsm_channel*) ;int /*<<< orphan*/  (* enable_receiver ) (struct jsm_channel*) ;int /*<<< orphan*/  (* send_stop_character ) (struct jsm_channel*) ;int /*<<< orphan*/  (* disable_receiver ) (struct jsm_channel*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  pci_dev; struct board_ops* bd_ops; } ;

/* Variables and functions */
 int CH_RECEIVER_OFF ; 
 int CRTSCTS ; 
 int IXOFF ; 
 int /*<<< orphan*/  MAX_STOPS_SENT ; 
 int /*<<< orphan*/  READ ; 
 scalar_t__ RQUEUEMASK ; 
 int RQUEUESIZE ; 
 int /*<<< orphan*/  jsm_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  stub1 (struct jsm_channel*) ; 
 int /*<<< orphan*/  stub2 (struct jsm_channel*) ; 
 int /*<<< orphan*/  stub3 (struct jsm_channel*) ; 
 int /*<<< orphan*/  stub4 (struct jsm_channel*) ; 

void jsm_check_queue_flow_control(struct jsm_channel *ch)
{
	struct board_ops *bd_ops = ch->ch_bd->bd_ops;
	int qleft;

	/* Store how much space we have left in the queue */
	if ((qleft = ch->ch_r_tail - ch->ch_r_head - 1) < 0)
		qleft += RQUEUEMASK + 1;

	/*
	 * Check to see if we should enforce flow control on our queue because
	 * the ld (or user) isn't reading data out of our queue fast enuf.
	 *
	 * NOTE: This is done based on what the current flow control of the
	 * port is set for.
	 *
	 * 1) HWFLOW (RTS) - Turn off the UART's Receive interrupt.
	 *	This will cause the UART's FIFO to back up, and force
	 *	the RTS signal to be dropped.
	 * 2) SWFLOW (IXOFF) - Keep trying to send a stop character to
	 *	the other side, in hopes it will stop sending data to us.
	 * 3) NONE - Nothing we can do.  We will simply drop any extra data
	 *	that gets sent into us when the queue fills up.
	 */
	if (qleft < 256) {
		/* HWFLOW */
		if (ch->ch_c_cflag & CRTSCTS) {
			if (!(ch->ch_flags & CH_RECEIVER_OFF)) {
				bd_ops->disable_receiver(ch);
				ch->ch_flags |= (CH_RECEIVER_OFF);
				jsm_dbg(READ, &ch->ch_bd->pci_dev,
					"Internal queue hit hilevel mark (%d)! Turning off interrupts\n",
					qleft);
			}
		}
		/* SWFLOW */
		else if (ch->ch_c_iflag & IXOFF) {
			if (ch->ch_stops_sent <= MAX_STOPS_SENT) {
				bd_ops->send_stop_character(ch);
				ch->ch_stops_sent++;
				jsm_dbg(READ, &ch->ch_bd->pci_dev,
					"Sending stop char! Times sent: %x\n",
					ch->ch_stops_sent);
			}
		}
	}

	/*
	 * Check to see if we should unenforce flow control because
	 * ld (or user) finally read enuf data out of our queue.
	 *
	 * NOTE: This is done based on what the current flow control of the
	 * port is set for.
	 *
	 * 1) HWFLOW (RTS) - Turn back on the UART's Receive interrupt.
	 *	This will cause the UART's FIFO to raise RTS back up,
	 *	which will allow the other side to start sending data again.
	 * 2) SWFLOW (IXOFF) - Send a start character to
	 *	the other side, so it will start sending data to us again.
	 * 3) NONE - Do nothing. Since we didn't do anything to turn off the
	 *	other side, we don't need to do anything now.
	 */
	if (qleft > (RQUEUESIZE / 2)) {
		/* HWFLOW */
		if (ch->ch_c_cflag & CRTSCTS) {
			if (ch->ch_flags & CH_RECEIVER_OFF) {
				bd_ops->enable_receiver(ch);
				ch->ch_flags &= ~(CH_RECEIVER_OFF);
				jsm_dbg(READ, &ch->ch_bd->pci_dev,
					"Internal queue hit lowlevel mark (%d)! Turning on interrupts\n",
					qleft);
			}
		}
		/* SWFLOW */
		else if (ch->ch_c_iflag & IXOFF && ch->ch_stops_sent) {
			ch->ch_stops_sent = 0;
			bd_ops->send_start_character(ch);
			jsm_dbg(READ, &ch->ch_bd->pci_dev,
				"Sending start char!\n");
		}
	}
}