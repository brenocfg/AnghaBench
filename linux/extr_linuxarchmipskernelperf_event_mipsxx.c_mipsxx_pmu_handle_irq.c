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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  mipsxx_pmu_handle_shared_irq () ; 

__attribute__((used)) static irqreturn_t mipsxx_pmu_handle_irq(int irq, void *dev)
{
	return mipsxx_pmu_handle_shared_irq();
}