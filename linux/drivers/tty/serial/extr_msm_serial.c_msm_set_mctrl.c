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

/* Variables and functions */
 unsigned int TIOCM_RTS ; 
 int /*<<< orphan*/  UART_CR ; 
 unsigned int UART_CR_CMD_RESET_RFR ; 
 int /*<<< orphan*/  UART_MR1 ; 
 unsigned int UART_MR1_RX_RDY_CTL ; 
 unsigned int msm_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_write (struct uart_port*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void msm_set_mctrl(struct uart_port *port, unsigned int mctrl)
{
	unsigned int mr;

	mr = msm_read(port, UART_MR1);

	if (!(mctrl & TIOCM_RTS)) {
		mr &= ~UART_MR1_RX_RDY_CTL;
		msm_write(port, mr, UART_MR1);
		msm_write(port, UART_CR_CMD_RESET_RFR, UART_CR);
	} else {
		mr |= UART_MR1_RX_RDY_CTL;
		msm_write(port, mr, UART_MR1);
	}
}