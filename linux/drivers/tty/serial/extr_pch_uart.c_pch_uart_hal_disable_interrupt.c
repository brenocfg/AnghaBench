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
typedef  unsigned int u8 ;
struct eg20t_port {scalar_t__ membase; } ;

/* Variables and functions */
 unsigned int PCH_UART_IER_MASK ; 
 scalar_t__ UART_IER ; 
 unsigned int ioread8 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite8 (unsigned int,scalar_t__) ; 

__attribute__((used)) static void pch_uart_hal_disable_interrupt(struct eg20t_port *priv,
					   unsigned int flag)
{
	u8 ier = ioread8(priv->membase + UART_IER);
	ier &= ~(flag & PCH_UART_IER_MASK);
	iowrite8(ier, priv->membase + UART_IER);
}