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
typedef  int u32 ;
struct uart_port {int dummy; } ;
struct rp2_uart_port {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ RP2_CHAN_STAT ; 
 int RP2_CHAN_STAT_CTS_m ; 
 int RP2_CHAN_STAT_DCD_m ; 
 int RP2_CHAN_STAT_DSR_m ; 
 int RP2_CHAN_STAT_RI_m ; 
 unsigned int TIOCM_CAR ; 
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_DSR ; 
 unsigned int TIOCM_RI ; 
 struct rp2_uart_port* port_to_up (struct uart_port*) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static unsigned int rp2_uart_get_mctrl(struct uart_port *port)
{
	struct rp2_uart_port *up = port_to_up(port);
	u32 status;

	status = readl(up->base + RP2_CHAN_STAT);
	return ((status & RP2_CHAN_STAT_DCD_m) ? TIOCM_CAR : 0) |
	       ((status & RP2_CHAN_STAT_DSR_m) ? TIOCM_DSR : 0) |
	       ((status & RP2_CHAN_STAT_CTS_m) ? TIOCM_CTS : 0) |
	       ((status & RP2_CHAN_STAT_RI_m) ? TIOCM_RI : 0);
}