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
typedef  int u32 ;
struct irq_chip_generic {scalar_t__ reg_base; } ;

/* Variables and functions */
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void ls_intc_set_bit(struct irq_chip_generic *gc,
							unsigned int offset,
							u32 mask, bool set)
{
	if (set)
		writel(readl(gc->reg_base + offset) | mask,
		gc->reg_base + offset);
	else
		writel(readl(gc->reg_base + offset) & ~mask,
		gc->reg_base + offset);
}