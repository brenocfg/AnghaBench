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

/* Variables and functions */
 int /*<<< orphan*/  cpu_relax () ; 
 int lpuart32_read (struct uart_port*,unsigned int) ; 

__attribute__((used)) static void lpuart32_wait_bit_set(struct uart_port *port, unsigned int offset,
				  u32 bit)
{
	while (!(lpuart32_read(port, offset) & bit))
		cpu_relax();
}