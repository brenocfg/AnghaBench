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
typedef  int u32 ;
struct serial_rs485 {int flags; int /*<<< orphan*/  delay_rts_after_send; int /*<<< orphan*/  delay_rts_before_send; } ;
struct uart_port {scalar_t__ membase; int /*<<< orphan*/  uartclk; struct serial_rs485 rs485; } ;
struct stm32_usart_offsets {scalar_t__ cr1; scalar_t__ cr3; scalar_t__ brr; } ;
struct stm32_usart_config {int /*<<< orphan*/  uart_enable_bit; } ;
struct stm32_port {TYPE_1__* info; } ;
struct TYPE_2__ {struct stm32_usart_config cfg; struct stm32_usart_offsets ofs; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int DIV_ROUND_CLOSEST (int /*<<< orphan*/ ,int) ; 
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 int SER_RS485_ENABLED ; 
 int SER_RS485_RTS_AFTER_SEND ; 
 int SER_RS485_RTS_ON_SEND ; 
 int SER_RS485_RX_DURING_TX ; 
 int USART_BRR_04_R_SHIFT ; 
 int USART_CR1_DEAT_MASK ; 
 int USART_CR1_DEDT_MASK ; 
 int USART_CR1_OVER8 ; 
 int USART_CR3_DEM ; 
 int USART_CR3_DEP ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  stm32_clr_bits (struct uart_port*,scalar_t__,int) ; 
 int /*<<< orphan*/  stm32_config_reg_rs485 (int*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stm32_set_bits (struct uart_port*,scalar_t__,int) ; 
 struct stm32_port* to_stm32_port (struct uart_port*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int stm32_config_rs485(struct uart_port *port,
			      struct serial_rs485 *rs485conf)
{
	struct stm32_port *stm32_port = to_stm32_port(port);
	struct stm32_usart_offsets *ofs = &stm32_port->info->ofs;
	struct stm32_usart_config *cfg = &stm32_port->info->cfg;
	u32 usartdiv, baud, cr1, cr3;
	bool over8;

	stm32_clr_bits(port, ofs->cr1, BIT(cfg->uart_enable_bit));

	port->rs485 = *rs485conf;

	rs485conf->flags |= SER_RS485_RX_DURING_TX;

	if (rs485conf->flags & SER_RS485_ENABLED) {
		cr1 = readl_relaxed(port->membase + ofs->cr1);
		cr3 = readl_relaxed(port->membase + ofs->cr3);
		usartdiv = readl_relaxed(port->membase + ofs->brr);
		usartdiv = usartdiv & GENMASK(15, 0);
		over8 = cr1 & USART_CR1_OVER8;

		if (over8)
			usartdiv = usartdiv | (usartdiv & GENMASK(4, 0))
				   << USART_BRR_04_R_SHIFT;

		baud = DIV_ROUND_CLOSEST(port->uartclk, usartdiv);
		stm32_config_reg_rs485(&cr1, &cr3,
				       rs485conf->delay_rts_before_send,
				       rs485conf->delay_rts_after_send, baud);

		if (rs485conf->flags & SER_RS485_RTS_ON_SEND) {
			cr3 &= ~USART_CR3_DEP;
			rs485conf->flags &= ~SER_RS485_RTS_AFTER_SEND;
		} else {
			cr3 |= USART_CR3_DEP;
			rs485conf->flags |= SER_RS485_RTS_AFTER_SEND;
		}

		writel_relaxed(cr3, port->membase + ofs->cr3);
		writel_relaxed(cr1, port->membase + ofs->cr1);
	} else {
		stm32_clr_bits(port, ofs->cr3, USART_CR3_DEM | USART_CR3_DEP);
		stm32_clr_bits(port, ofs->cr1,
			       USART_CR1_DEDT_MASK | USART_CR1_DEAT_MASK);
	}

	stm32_set_bits(port, ofs->cr1, BIT(cfg->uart_enable_bit));

	return 0;
}