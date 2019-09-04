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
struct TYPE_2__ {int /*<<< orphan*/  IntPend; } ;

/* Variables and functions */
 int MPC52xx_IRQ_L2_MASK ; 
 int irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* sdma ; 

__attribute__((used)) static void mpc52xx_sdma_ack(struct irq_data *d)
{
	int l2irq = irqd_to_hwirq(d) & MPC52xx_IRQ_L2_MASK;
	out_be32(&sdma->IntPend, 1 << l2irq);
}