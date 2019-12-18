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
struct rp2_uart_port {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ RP2_UART_CTL ; 
 int RP2_UART_CTL_FLUSH_RX_m ; 
 int RP2_UART_CTL_FLUSH_TX_m ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  rp2_rmw_clr (struct rp2_uart_port*,scalar_t__,int) ; 
 int /*<<< orphan*/  rp2_rmw_set (struct rp2_uart_port*,scalar_t__,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static inline void rp2_flush_fifos(struct rp2_uart_port *up)
{
	rp2_rmw_set(up, RP2_UART_CTL,
		    RP2_UART_CTL_FLUSH_RX_m | RP2_UART_CTL_FLUSH_TX_m);
	readl(up->base + RP2_UART_CTL);
	udelay(10);
	rp2_rmw_clr(up, RP2_UART_CTL,
		    RP2_UART_CTL_FLUSH_RX_m | RP2_UART_CTL_FLUSH_TX_m);
}