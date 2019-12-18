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
typedef  unsigned long u32 ;

/* Variables and functions */
 unsigned long IRQS_PER_IDX ; 
 unsigned long NR_HW_IRQS ; 

__attribute__((used)) static u32 hwirq_to_reg_set(unsigned long hwirq)
{
	return (hwirq / (NR_HW_IRQS * IRQS_PER_IDX));
}