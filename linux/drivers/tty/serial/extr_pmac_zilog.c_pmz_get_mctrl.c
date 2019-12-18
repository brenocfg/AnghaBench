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
struct uart_port {int dummy; } ;
struct uart_pmac_port {int dummy; } ;

/* Variables and functions */
 unsigned char CTS ; 
 unsigned char DCD ; 
 int /*<<< orphan*/  R0 ; 
 unsigned char SYNC_HUNT ; 
 unsigned int TIOCM_CAR ; 
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_DSR ; 
 unsigned char read_zsreg (struct uart_pmac_port*,int /*<<< orphan*/ ) ; 
 struct uart_pmac_port* to_pmz (struct uart_port*) ; 

__attribute__((used)) static unsigned int pmz_get_mctrl(struct uart_port *port)
{
	struct uart_pmac_port *uap = to_pmz(port);
	unsigned char status;
	unsigned int ret;

	status = read_zsreg(uap, R0);

	ret = 0;
	if (status & DCD)
		ret |= TIOCM_CAR;
	if (status & SYNC_HUNT)
		ret |= TIOCM_DSR;
	if (!(status & CTS))
		ret |= TIOCM_CTS;

	return ret;
}