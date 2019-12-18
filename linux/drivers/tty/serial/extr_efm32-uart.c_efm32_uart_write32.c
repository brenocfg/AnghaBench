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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {unsigned int membase; } ;
struct efm32_uart_port {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void efm32_uart_write32(struct efm32_uart_port *efm_port,
		u32 value, unsigned offset)
{
	writel_relaxed(value, efm_port->port.membase + offset);
}