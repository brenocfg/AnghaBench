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
struct TYPE_2__ {int /*<<< orphan*/  memreg_card_present; } ;

/* Variables and functions */
 scalar_t__ CARD_PRESENT_VALUE ; 
 scalar_t__ HW_VERSION_1 ; 
 scalar_t__ IOIR ; 
 int inw (scalar_t__) ; 
 scalar_t__ readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int is_card_present(struct ipw_hardware *hw)
{
	if (hw->hw_version == HW_VERSION_1)
		return inw(hw->base_port + IOIR) != 0xFFFF;
	else
		return readl(&hw->memory_info_regs->memreg_card_present) ==
		    CARD_PRESENT_VALUE;
}