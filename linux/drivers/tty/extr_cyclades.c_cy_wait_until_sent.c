#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tty_struct {int /*<<< orphan*/  name; struct cyclades_port* driver_data; } ;
struct cyclades_port {int xmit_fifo_size; int timeout; struct cyclades_card* card; } ;
struct cyclades_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CySRER ; 
 int CyTxRdy ; 
 int HZ ; 
 int /*<<< orphan*/  cy_is_Z (struct cyclades_card*) ; 
 int cyy_readb (struct cyclades_port*,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (int) ; 
 int min (int,int) ; 
 scalar_t__ msleep_interruptible (int /*<<< orphan*/ ) ; 
 scalar_t__ serial_paranoia_check (struct cyclades_port*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static void cy_wait_until_sent(struct tty_struct *tty, int timeout)
{
	struct cyclades_card *card;
	struct cyclades_port *info = tty->driver_data;
	unsigned long orig_jiffies;
	int char_time;

	if (serial_paranoia_check(info, tty->name, "cy_wait_until_sent"))
		return;

	if (info->xmit_fifo_size == 0)
		return;		/* Just in case.... */

	orig_jiffies = jiffies;
	/*
	 * Set the check interval to be 1/5 of the estimated time to
	 * send a single character, and make it at least 1.  The check
	 * interval should also be less than the timeout.
	 *
	 * Note: we have to use pretty tight timings here to satisfy
	 * the NIST-PCTS.
	 */
	char_time = (info->timeout - HZ / 50) / info->xmit_fifo_size;
	char_time = char_time / 5;
	if (char_time <= 0)
		char_time = 1;
	if (timeout < 0)
		timeout = 0;
	if (timeout)
		char_time = min(char_time, timeout);
	/*
	 * If the transmitter hasn't cleared in twice the approximate
	 * amount of time to send the entire FIFO, it probably won't
	 * ever clear.  This assumes the UART isn't doing flow
	 * control, which is currently the case.  Hence, if it ever
	 * takes longer than info->timeout, this is probably due to a
	 * UART bug of some kind.  So, we clamp the timeout parameter at
	 * 2*info->timeout.
	 */
	if (!timeout || timeout > 2 * info->timeout)
		timeout = 2 * info->timeout;

	card = info->card;
	if (!cy_is_Z(card)) {
		while (cyy_readb(info, CySRER) & CyTxRdy) {
			if (msleep_interruptible(jiffies_to_msecs(char_time)))
				break;
			if (timeout && time_after(jiffies, orig_jiffies +
					timeout))
				break;
		}
	}
	/* Run one more char cycle */
	msleep_interruptible(jiffies_to_msecs(char_time * 5));
}