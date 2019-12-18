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
typedef  int /*<<< orphan*/  u32 ;
struct uart_port {int read_status_mask; int ignore_status_mask; int /*<<< orphan*/  lock; scalar_t__ membase; } ;
struct ktermios {unsigned int c_cflag; unsigned int c_iflag; } ;

/* Variables and functions */
 scalar_t__ AML_UART_CONTROL ; 
 int /*<<< orphan*/  AML_UART_DATA_LEN_5BIT ; 
 int /*<<< orphan*/  AML_UART_DATA_LEN_6BIT ; 
 int /*<<< orphan*/  AML_UART_DATA_LEN_7BIT ; 
 int /*<<< orphan*/  AML_UART_DATA_LEN_8BIT ; 
 int /*<<< orphan*/  AML_UART_DATA_LEN_MASK ; 
 int AML_UART_FRAME_ERR ; 
 int /*<<< orphan*/  AML_UART_PARITY_EN ; 
 int AML_UART_PARITY_ERR ; 
 int /*<<< orphan*/  AML_UART_PARITY_TYPE ; 
 int /*<<< orphan*/  AML_UART_STOP_BIT_1SB ; 
 int /*<<< orphan*/  AML_UART_STOP_BIT_2SB ; 
 int /*<<< orphan*/  AML_UART_STOP_BIT_LEN_MASK ; 
 int /*<<< orphan*/  AML_UART_TWO_WIRE_EN ; 
 int AML_UART_TX_FIFO_WERR ; 
 unsigned int CRTSCTS ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 unsigned int CSIZE ; 
 unsigned int CSTOPB ; 
 unsigned int IGNPAR ; 
 unsigned int INPCK ; 
 unsigned int PARENB ; 
 unsigned int PARODD ; 
 int /*<<< orphan*/  meson_uart_change_speed (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int,int) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void meson_uart_set_termios(struct uart_port *port,
				   struct ktermios *termios,
				   struct ktermios *old)
{
	unsigned int cflags, iflags, baud;
	unsigned long flags;
	u32 val;

	spin_lock_irqsave(&port->lock, flags);

	cflags = termios->c_cflag;
	iflags = termios->c_iflag;

	val = readl(port->membase + AML_UART_CONTROL);

	val &= ~AML_UART_DATA_LEN_MASK;
	switch (cflags & CSIZE) {
	case CS8:
		val |= AML_UART_DATA_LEN_8BIT;
		break;
	case CS7:
		val |= AML_UART_DATA_LEN_7BIT;
		break;
	case CS6:
		val |= AML_UART_DATA_LEN_6BIT;
		break;
	case CS5:
		val |= AML_UART_DATA_LEN_5BIT;
		break;
	}

	if (cflags & PARENB)
		val |= AML_UART_PARITY_EN;
	else
		val &= ~AML_UART_PARITY_EN;

	if (cflags & PARODD)
		val |= AML_UART_PARITY_TYPE;
	else
		val &= ~AML_UART_PARITY_TYPE;

	val &= ~AML_UART_STOP_BIT_LEN_MASK;
	if (cflags & CSTOPB)
		val |= AML_UART_STOP_BIT_2SB;
	else
		val |= AML_UART_STOP_BIT_1SB;

	if (cflags & CRTSCTS)
		val &= ~AML_UART_TWO_WIRE_EN;
	else
		val |= AML_UART_TWO_WIRE_EN;

	writel(val, port->membase + AML_UART_CONTROL);

	baud = uart_get_baud_rate(port, termios, old, 50, 4000000);
	meson_uart_change_speed(port, baud);

	port->read_status_mask = AML_UART_TX_FIFO_WERR;
	if (iflags & INPCK)
		port->read_status_mask |= AML_UART_PARITY_ERR |
					  AML_UART_FRAME_ERR;

	port->ignore_status_mask = 0;
	if (iflags & IGNPAR)
		port->ignore_status_mask |= AML_UART_PARITY_ERR |
					    AML_UART_FRAME_ERR;

	uart_update_timeout(port, termios->c_cflag, baud);
	spin_unlock_irqrestore(&port->lock, flags);
}