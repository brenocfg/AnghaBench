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
struct zilog_channel {int /*<<< orphan*/  control; } ;
struct TYPE_4__ {TYPE_1__* state; int /*<<< orphan*/  lock; } ;
struct uart_ip22zilog_port {struct uart_ip22zilog_port* next; TYPE_2__ port; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 unsigned char CHAEXT ; 
 unsigned char CHARxIP ; 
 unsigned char CHATxIP ; 
 unsigned char CHBEXT ; 
 unsigned char CHBRxIP ; 
 unsigned char CHBTxIP ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  R3 ; 
 int /*<<< orphan*/  RES_H_IUS ; 
 struct zilog_channel* ZILOG_CHANNEL_FROM_PORT (TYPE_2__*) ; 
 int /*<<< orphan*/  ZSDELAY () ; 
 int /*<<< orphan*/  ZS_WSYNC (struct zilog_channel*) ; 
 int ip22zilog_receive_chars (struct uart_ip22zilog_port*,struct zilog_channel*) ; 
 int /*<<< orphan*/  ip22zilog_status_handle (struct uart_ip22zilog_port*,struct zilog_channel*) ; 
 int /*<<< orphan*/  ip22zilog_transmit_chars (struct uart_ip22zilog_port*,struct zilog_channel*) ; 
 unsigned char read_zsreg (struct zilog_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t ip22zilog_interrupt(int irq, void *dev_id)
{
	struct uart_ip22zilog_port *up = dev_id;

	while (up) {
		struct zilog_channel *channel
			= ZILOG_CHANNEL_FROM_PORT(&up->port);
		unsigned char r3;
		bool push = false;

		spin_lock(&up->port.lock);
		r3 = read_zsreg(channel, R3);

		/* Channel A */
		if (r3 & (CHAEXT | CHATxIP | CHARxIP)) {
			writeb(RES_H_IUS, &channel->control);
			ZSDELAY();
			ZS_WSYNC(channel);

			if (r3 & CHARxIP)
				push = ip22zilog_receive_chars(up, channel);
			if (r3 & CHAEXT)
				ip22zilog_status_handle(up, channel);
			if (r3 & CHATxIP)
				ip22zilog_transmit_chars(up, channel);
		}
		spin_unlock(&up->port.lock);

		if (push)
			tty_flip_buffer_push(&up->port.state->port);

		/* Channel B */
		up = up->next;
		channel = ZILOG_CHANNEL_FROM_PORT(&up->port);
		push = false;

		spin_lock(&up->port.lock);
		if (r3 & (CHBEXT | CHBTxIP | CHBRxIP)) {
			writeb(RES_H_IUS, &channel->control);
			ZSDELAY();
			ZS_WSYNC(channel);

			if (r3 & CHBRxIP)
				push = ip22zilog_receive_chars(up, channel);
			if (r3 & CHBEXT)
				ip22zilog_status_handle(up, channel);
			if (r3 & CHBTxIP)
				ip22zilog_transmit_chars(up, channel);
		}
		spin_unlock(&up->port.lock);

		if (push)
			tty_flip_buffer_push(&up->port.state->port);

		up = up->next;
	}

	return IRQ_HANDLED;
}