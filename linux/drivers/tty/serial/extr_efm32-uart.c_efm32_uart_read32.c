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
 int /*<<< orphan*/  readl_relaxed (unsigned int) ; 

__attribute__((used)) static u32 efm32_uart_read32(struct efm32_uart_port *efm_port,
		unsigned offset)
{
	return readl_relaxed(efm_port->port.membase + offset);
}