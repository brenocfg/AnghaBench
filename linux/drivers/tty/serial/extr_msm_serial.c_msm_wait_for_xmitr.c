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
 int /*<<< orphan*/  UART_CR ; 
 int /*<<< orphan*/  UART_CR_CMD_RESET_TX_READY ; 
 int /*<<< orphan*/  UART_ISR ; 
 int UART_ISR_TX_READY ; 
 int /*<<< orphan*/  UART_SR ; 
 int UART_SR_TX_EMPTY ; 
 int msm_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_write (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static inline void msm_wait_for_xmitr(struct uart_port *port)
{
	unsigned int timeout = 500000;

	while (!(msm_read(port, UART_SR) & UART_SR_TX_EMPTY)) {
		if (msm_read(port, UART_ISR) & UART_ISR_TX_READY)
			break;
		udelay(1);
		if (!timeout--)
			break;
	}
	msm_write(port, UART_CR_CMD_RESET_TX_READY, UART_CR);
}