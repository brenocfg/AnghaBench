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
typedef  int u8 ;
struct uart_port {int dummy; } ;
struct TYPE_2__ {int (* get_ipcr ) (struct uart_port*) ;} ;

/* Variables and functions */
 int MPC52xx_PSC_CTS ; 
 int MPC52xx_PSC_DCD ; 
 unsigned int TIOCM_CAR ; 
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_DSR ; 
 TYPE_1__* psc_ops ; 
 int stub1 (struct uart_port*) ; 

__attribute__((used)) static unsigned int
mpc52xx_uart_get_mctrl(struct uart_port *port)
{
	unsigned int ret = TIOCM_DSR;
	u8 status = psc_ops->get_ipcr(port);

	if (!(status & MPC52xx_PSC_CTS))
		ret |= TIOCM_CTS;
	if (!(status & MPC52xx_PSC_DCD))
		ret |= TIOCM_CAR;

	return ret;
}