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
struct TYPE_2__ {scalar_t__ base; } ;

/* Variables and functions */
 unsigned int ioread32 (scalar_t__) ; 
 unsigned int ioread32be (scalar_t__) ; 
 scalar_t__ static_branch_unlikely (int /*<<< orphan*/ *) ; 
 TYPE_1__* xintc_irqc ; 
 int /*<<< orphan*/  xintc_is_be ; 

__attribute__((used)) static unsigned int xintc_read(int reg)
{
	if (static_branch_unlikely(&xintc_is_be))
		return ioread32be(xintc_irqc->base + reg);
	else
		return ioread32(xintc_irqc->base + reg);
}