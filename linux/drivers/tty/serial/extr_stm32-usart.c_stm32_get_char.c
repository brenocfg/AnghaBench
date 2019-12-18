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
typedef  int /*<<< orphan*/  u32 ;
struct uart_port {scalar_t__ membase; } ;
struct stm32_usart_offsets {scalar_t__ rdr; } ;
struct stm32_port {unsigned long* rx_buf; unsigned long rdr_mask; scalar_t__ rx_ch; TYPE_1__* info; } ;
struct TYPE_2__ {struct stm32_usart_offsets ofs; } ;

/* Variables and functions */
 size_t RX_BUF_L ; 
 unsigned long readl_relaxed (scalar_t__) ; 
 struct stm32_port* to_stm32_port (struct uart_port*) ; 

__attribute__((used)) static unsigned long stm32_get_char(struct uart_port *port, u32 *sr,
				    int *last_res)
{
	struct stm32_port *stm32_port = to_stm32_port(port);
	struct stm32_usart_offsets *ofs = &stm32_port->info->ofs;
	unsigned long c;

	if (stm32_port->rx_ch) {
		c = stm32_port->rx_buf[RX_BUF_L - (*last_res)--];
		if ((*last_res) == 0)
			*last_res = RX_BUF_L;
	} else {
		c = readl_relaxed(port->membase + ofs->rdr);
		/* apply RDR data mask */
		c &= stm32_port->rdr_mask;
	}

	return c;
}