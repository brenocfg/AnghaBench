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
struct TYPE_2__ {int bus_reset; } ;
union blogic_cntrl_reg {scalar_t__ all; TYPE_1__ cr; } ;
struct blogic_adapter {scalar_t__ io_addr; } ;

/* Variables and functions */
 scalar_t__ BLOGIC_CNTRL_REG ; 
 int /*<<< orphan*/  outb (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void blogic_busreset(struct blogic_adapter *adapter)
{
	union blogic_cntrl_reg cr;
	cr.all = 0;
	cr.cr.bus_reset = true;
	outb(cr.all, adapter->io_addr + BLOGIC_CNTRL_REG);
}