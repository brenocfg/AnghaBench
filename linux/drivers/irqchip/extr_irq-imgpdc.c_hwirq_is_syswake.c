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
typedef  scalar_t__ irq_hw_number_t ;

/* Variables and functions */
 scalar_t__ SYS0_HWIRQ ; 

__attribute__((used)) static unsigned int hwirq_is_syswake(irq_hw_number_t hw)
{
	return hw >= SYS0_HWIRQ;
}