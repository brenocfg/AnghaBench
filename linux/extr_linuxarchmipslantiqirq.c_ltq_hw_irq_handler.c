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
struct irq_desc {int dummy; } ;

/* Variables and functions */
 int INT_NUM_IM_OFFSET ; 
 scalar_t__ LTQ_EBU_PCC_ISTAT ; 
 int LTQ_ICU_EBU_IRQ ; 
 int /*<<< orphan*/  LTQ_ICU_IM0_IOSR ; 
 int MIPS_CPU_IRQ_CASCADE ; 
 int __fls (int) ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 int irq_desc_get_irq (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_linear_revmap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ltq_domain ; 
 int ltq_ebu_r32 (scalar_t__) ; 
 int /*<<< orphan*/  ltq_ebu_w32 (int,scalar_t__) ; 
 int ltq_icu_r32 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ltq_hw_irq_handler(struct irq_desc *desc)
{
	int module = irq_desc_get_irq(desc) - 2;
	u32 irq;
	int hwirq;

	irq = ltq_icu_r32(module, LTQ_ICU_IM0_IOSR);
	if (irq == 0)
		return;

	/*
	 * silicon bug causes only the msb set to 1 to be valid. all
	 * other bits might be bogus
	 */
	irq = __fls(irq);
	hwirq = irq + MIPS_CPU_IRQ_CASCADE + (INT_NUM_IM_OFFSET * module);
	generic_handle_irq(irq_linear_revmap(ltq_domain, hwirq));

	/* if this is a EBU irq, we need to ack it or get a deadlock */
	if ((irq == LTQ_ICU_EBU_IRQ) && (module == 0) && LTQ_EBU_PCC_ISTAT)
		ltq_ebu_w32(ltq_ebu_r32(LTQ_EBU_PCC_ISTAT) | 0x10,
			LTQ_EBU_PCC_ISTAT);
}