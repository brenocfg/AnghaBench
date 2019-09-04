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
struct TYPE_2__ {int /*<<< orphan*/  len; } ;
struct arch_hw_breakpoint {unsigned long address; TYPE_1__ ctrl; } ;

/* Variables and functions */
 unsigned long TASK_SIZE ; 
 unsigned int get_hbp_len (int /*<<< orphan*/ ) ; 

int arch_check_bp_in_kernelspace(struct arch_hw_breakpoint *hw)
{
	unsigned int len;
	unsigned long va;

	va = hw->address;
	len = get_hbp_len(hw->ctrl.len);

	return (va >= TASK_SIZE) && ((va + len - 1) >= TASK_SIZE);
}