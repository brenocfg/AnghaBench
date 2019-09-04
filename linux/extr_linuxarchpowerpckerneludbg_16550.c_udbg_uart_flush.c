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

/* Variables and functions */
 int LSR_THRE ; 
 int /*<<< orphan*/  UART_LSR ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int udbg_uart_in (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void udbg_uart_flush(void)
{
	if (!udbg_uart_in)
		return;

	/* wait for idle */
	while ((udbg_uart_in(UART_LSR) & LSR_THRE) == 0)
		cpu_relax();
}