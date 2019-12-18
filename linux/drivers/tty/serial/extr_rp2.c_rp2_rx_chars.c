#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct tty_port {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  rx; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; TYPE_2__ icount; TYPE_1__* state; } ;
struct rp2_uart_port {TYPE_3__ port; scalar_t__ base; } ;
struct TYPE_5__ {struct tty_port port; } ;

/* Variables and functions */
 scalar_t__ RP2_DATA_BYTE ; 
 int RP2_DATA_BYTE_BREAK_m ; 
 int RP2_DATA_BYTE_ERR_FRAMING_m ; 
 int /*<<< orphan*/  RP2_DATA_BYTE_ERR_OVERRUN_m ; 
 int RP2_DATA_BYTE_ERR_PARITY_m ; 
 int RP2_DATA_BYTE_EXCEPTION_MASK ; 
 int RP2_DUMMY_READ ; 
 scalar_t__ RP2_RX_FIFO_COUNT ; 
 char TTY_BREAK ; 
 char TTY_FRAME ; 
 char TTY_NORMAL ; 
 char TTY_PARITY ; 
 scalar_t__ likely (int) ; 
 int readw (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_port*) ; 
 int /*<<< orphan*/  uart_handle_sysrq_char (TYPE_3__*,char) ; 
 int /*<<< orphan*/  uart_insert_char (TYPE_3__*,int,int /*<<< orphan*/ ,char,char) ; 

__attribute__((used)) static void rp2_rx_chars(struct rp2_uart_port *up)
{
	u16 bytes = readw(up->base + RP2_RX_FIFO_COUNT);
	struct tty_port *port = &up->port.state->port;

	for (; bytes != 0; bytes--) {
		u32 byte = readw(up->base + RP2_DATA_BYTE) | RP2_DUMMY_READ;
		char ch = byte & 0xff;

		if (likely(!(byte & RP2_DATA_BYTE_EXCEPTION_MASK))) {
			if (!uart_handle_sysrq_char(&up->port, ch))
				uart_insert_char(&up->port, byte, 0, ch,
						 TTY_NORMAL);
		} else {
			char flag = TTY_NORMAL;

			if (byte & RP2_DATA_BYTE_BREAK_m)
				flag = TTY_BREAK;
			else if (byte & RP2_DATA_BYTE_ERR_FRAMING_m)
				flag = TTY_FRAME;
			else if (byte & RP2_DATA_BYTE_ERR_PARITY_m)
				flag = TTY_PARITY;
			uart_insert_char(&up->port, byte,
					 RP2_DATA_BYTE_ERR_OVERRUN_m, ch, flag);
		}
		up->port.icount.rx++;
	}

	spin_unlock(&up->port.lock);
	tty_flip_buffer_push(port);
	spin_lock(&up->port.lock);
}