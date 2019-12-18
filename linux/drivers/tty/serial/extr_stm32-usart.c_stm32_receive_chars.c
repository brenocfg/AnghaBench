#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {int /*<<< orphan*/  frame; int /*<<< orphan*/  brk; int /*<<< orphan*/  parity; int /*<<< orphan*/  overrun; int /*<<< orphan*/  rx; } ;
struct uart_port {int read_status_mask; int /*<<< orphan*/  lock; TYPE_4__ icount; int /*<<< orphan*/  irq; TYPE_1__* state; } ;
struct tty_port {TYPE_3__* tty; } ;
struct stm32_usart_offsets {scalar_t__ icr; } ;
struct stm32_port {int /*<<< orphan*/  last_res; TYPE_2__* info; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {struct stm32_usart_offsets ofs; } ;
struct TYPE_5__ {struct tty_port port; } ;

/* Variables and functions */
 char TTY_BREAK ; 
 char TTY_FRAME ; 
 char TTY_NORMAL ; 
 char TTY_PARITY ; 
 scalar_t__ UNDEF_REG ; 
 int USART_ICR_FECF ; 
 int USART_ICR_ORECF ; 
 int USART_ICR_PECF ; 
 int USART_SR_DUMMY_RX ; 
 int USART_SR_ERR_MASK ; 
 int USART_SR_FE ; 
 int USART_SR_ORE ; 
 int USART_SR_PE ; 
 int /*<<< orphan*/  irq_get_irq_data (int /*<<< orphan*/ ) ; 
 scalar_t__ irqd_is_wakeup_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_wakeup_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm32_clr_bits (struct uart_port*,scalar_t__,int) ; 
 unsigned long stm32_get_char (struct uart_port*,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ stm32_pending_rx (struct uart_port*,int*,int /*<<< orphan*/ *,int) ; 
 struct stm32_port* to_stm32_port (struct uart_port*) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_port*) ; 
 scalar_t__ uart_handle_break (struct uart_port*) ; 
 scalar_t__ uart_handle_sysrq_char (struct uart_port*,unsigned long) ; 
 int /*<<< orphan*/  uart_insert_char (struct uart_port*,int,int,unsigned long,char) ; 

__attribute__((used)) static void stm32_receive_chars(struct uart_port *port, bool threaded)
{
	struct tty_port *tport = &port->state->port;
	struct stm32_port *stm32_port = to_stm32_port(port);
	struct stm32_usart_offsets *ofs = &stm32_port->info->ofs;
	unsigned long c;
	u32 sr;
	char flag;

	if (irqd_is_wakeup_set(irq_get_irq_data(port->irq)))
		pm_wakeup_event(tport->tty->dev, 0);

	while (stm32_pending_rx(port, &sr, &stm32_port->last_res, threaded)) {
		sr |= USART_SR_DUMMY_RX;
		flag = TTY_NORMAL;

		/*
		 * Status bits has to be cleared before reading the RDR:
		 * In FIFO mode, reading the RDR will pop the next data
		 * (if any) along with its status bits into the SR.
		 * Not doing so leads to misalignement between RDR and SR,
		 * and clear status bits of the next rx data.
		 *
		 * Clear errors flags for stm32f7 and stm32h7 compatible
		 * devices. On stm32f4 compatible devices, the error bit is
		 * cleared by the sequence [read SR - read DR].
		 */
		if ((sr & USART_SR_ERR_MASK) && ofs->icr != UNDEF_REG)
			stm32_clr_bits(port, ofs->icr, USART_ICR_ORECF |
				       USART_ICR_PECF | USART_ICR_FECF);

		c = stm32_get_char(port, &sr, &stm32_port->last_res);
		port->icount.rx++;
		if (sr & USART_SR_ERR_MASK) {
			if (sr & USART_SR_ORE) {
				port->icount.overrun++;
			} else if (sr & USART_SR_PE) {
				port->icount.parity++;
			} else if (sr & USART_SR_FE) {
				/* Break detection if character is null */
				if (!c) {
					port->icount.brk++;
					if (uart_handle_break(port))
						continue;
				} else {
					port->icount.frame++;
				}
			}

			sr &= port->read_status_mask;

			if (sr & USART_SR_PE) {
				flag = TTY_PARITY;
			} else if (sr & USART_SR_FE) {
				if (!c)
					flag = TTY_BREAK;
				else
					flag = TTY_FRAME;
			}
		}

		if (uart_handle_sysrq_char(port, c))
			continue;
		uart_insert_char(port, sr, USART_SR_ORE, c, flag);
	}

	spin_unlock(&port->lock);
	tty_flip_buffer_push(tport);
	spin_lock(&port->lock);
}