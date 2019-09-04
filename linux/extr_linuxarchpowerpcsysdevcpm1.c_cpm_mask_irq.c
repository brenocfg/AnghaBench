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
struct irq_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cpic_cimr; } ;

/* Variables and functions */
 int /*<<< orphan*/  clrbits32 (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* cpic_reg ; 
 scalar_t__ irqd_to_hwirq (struct irq_data*) ; 

__attribute__((used)) static void cpm_mask_irq(struct irq_data *d)
{
	unsigned int cpm_vec = (unsigned int)irqd_to_hwirq(d);

	clrbits32(&cpic_reg->cpic_cimr, (1 << cpm_vec));
}