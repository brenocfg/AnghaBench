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
struct TYPE_2__ {unsigned long ctl_addr; unsigned long irq_addr; } ;
struct ide_hw {unsigned long* io_ports_array; TYPE_1__ io_ports; } ;

/* Variables and functions */

__attribute__((used)) static void sgiioc4_init_hwif_ports(struct ide_hw *hw,
				    unsigned long data_port,
				    unsigned long ctrl_port,
				    unsigned long irq_port)
{
	unsigned long reg = data_port;
	int i;

	/* Registers are word (32 bit) aligned */
	for (i = 0; i <= 7; i++)
		hw->io_ports_array[i] = reg + i * 4;

	hw->io_ports.ctl_addr = ctrl_port;
	hw->io_ports.irq_addr = irq_port;
}