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
struct ipw_hardware {scalar_t__ hw_version; TYPE_1__* memory_info_regs; scalar_t__ base_port; } ;
struct TYPE_2__ {int /*<<< orphan*/  memreg_pc_interrupt_ack; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCR_RXDONE ; 
 scalar_t__ HW_VERSION_1 ; 
 scalar_t__ IODCR ; 
 int /*<<< orphan*/  MEMRX_PCINTACKK ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acknowledge_data_read(struct ipw_hardware *hw)
{
	if (hw->hw_version == HW_VERSION_1)
		outw(DCR_RXDONE, hw->base_port + IODCR);
	else
		writew(MEMRX_PCINTACKK,
				&hw->memory_info_regs->memreg_pc_interrupt_ack);
}