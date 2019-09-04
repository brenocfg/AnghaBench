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
struct irq_data {int hwirq; } ;

/* Variables and functions */
 int /*<<< orphan*/  PBC_INTMASK_SET_REG ; 
 int /*<<< orphan*/  imx_writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void expio_unmask_irq(struct irq_data *d)
{
	u32 expio = d->hwirq;
	/* unmask the interrupt */
	imx_writew(1 << expio, PBC_INTMASK_SET_REG);
}