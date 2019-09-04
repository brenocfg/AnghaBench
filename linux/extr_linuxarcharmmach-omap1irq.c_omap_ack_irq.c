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
struct TYPE_2__ {scalar_t__ va; } ;

/* Variables and functions */
 scalar_t__ IRQ_CONTROL_REG_OFFSET ; 
 TYPE_1__* irq_banks ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void omap_ack_irq(int irq)
{
	if (irq > 31)
		writel_relaxed(0x1, irq_banks[1].va + IRQ_CONTROL_REG_OFFSET);

	writel_relaxed(0x1, irq_banks[0].va + IRQ_CONTROL_REG_OFFSET);
}