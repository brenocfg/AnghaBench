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
struct arch_hw_breakpoint {int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int is_kernel_addr (int /*<<< orphan*/ ) ; 

int arch_check_bp_in_kernelspace(struct arch_hw_breakpoint *hw)
{
	return is_kernel_addr(hw->address);
}