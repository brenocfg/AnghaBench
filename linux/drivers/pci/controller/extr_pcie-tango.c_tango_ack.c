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
struct tango_pcie {int base; } ;
struct irq_data {int hwirq; struct tango_pcie* chip_data; } ;

/* Variables and functions */
 int BIT (int) ; 
 int SMP8759_STATUS ; 
 int /*<<< orphan*/  writel_relaxed (int,int) ; 

__attribute__((used)) static void tango_ack(struct irq_data *d)
{
	struct tango_pcie *pcie = d->chip_data;
	u32 offset = (d->hwirq / 32) * 4;
	u32 bit = BIT(d->hwirq % 32);

	writel_relaxed(bit, pcie->base + SMP8759_STATUS + offset);
}