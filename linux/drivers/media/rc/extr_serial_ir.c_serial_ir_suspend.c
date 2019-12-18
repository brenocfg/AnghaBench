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
struct platform_device {int dummy; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  UART_IER ; 
 int UART_IER_MSI ; 
 int UART_IER_RDI ; 
 int UART_IER_RLSI ; 
 int UART_IER_THRI ; 
 int /*<<< orphan*/  UART_IIR ; 
 int /*<<< orphan*/  UART_LCR ; 
 int UART_LCR_DLAB ; 
 int /*<<< orphan*/  UART_LSR ; 
 int /*<<< orphan*/  UART_MSR ; 
 int /*<<< orphan*/  UART_RX ; 
 int sinp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soutp (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int serial_ir_suspend(struct platform_device *dev,
			     pm_message_t state)
{
	/* Set DLAB 0. */
	soutp(UART_LCR, sinp(UART_LCR) & (~UART_LCR_DLAB));

	/* Disable all interrupts */
	soutp(UART_IER, sinp(UART_IER) &
	      (~(UART_IER_MSI | UART_IER_RLSI | UART_IER_THRI | UART_IER_RDI)));

	/* Clear registers. */
	sinp(UART_LSR);
	sinp(UART_RX);
	sinp(UART_IIR);
	sinp(UART_MSR);

	return 0;
}