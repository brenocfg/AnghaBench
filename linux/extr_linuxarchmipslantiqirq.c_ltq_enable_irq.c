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
typedef  int /*<<< orphan*/  u32 ;
struct irq_data {int hwirq; } ;

/* Variables and functions */
 int BIT (int) ; 
 int INT_NUM_IM_OFFSET ; 
 int /*<<< orphan*/  LTQ_ICU_IM0_IER ; 
 int MIPS_CPU_IRQ_CASCADE ; 
 int ltq_icu_r32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ltq_icu_w32 (int,int,int /*<<< orphan*/ ) ; 

void ltq_enable_irq(struct irq_data *d)
{
	u32 ier = LTQ_ICU_IM0_IER;
	int offset = d->hwirq - MIPS_CPU_IRQ_CASCADE;
	int im = offset / INT_NUM_IM_OFFSET;

	offset %= INT_NUM_IM_OFFSET;
	ltq_icu_w32(im, ltq_icu_r32(im, ier) | BIT(offset), ier);
}