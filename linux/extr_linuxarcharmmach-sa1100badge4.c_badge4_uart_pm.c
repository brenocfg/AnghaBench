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
typedef  int /*<<< orphan*/  u_int ;
struct uart_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDCR0_UART ; 
 int /*<<< orphan*/  Ser1SDCR0 ; 

__attribute__((used)) static void
badge4_uart_pm(struct uart_port *port, u_int state, u_int oldstate)
{
	if (!state) {
		Ser1SDCR0 |= SDCR0_UART;
	}
}