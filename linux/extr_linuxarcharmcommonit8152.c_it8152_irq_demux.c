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
struct irq_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IT8152_INTC_LDCNIRR ; 
 int /*<<< orphan*/  IT8152_INTC_LPCNIRR ; 
 int /*<<< orphan*/  IT8152_INTC_PDCNIRR ; 
 int /*<<< orphan*/  IT8152_LD_IRQ (int) ; 
 int IT8152_LD_IRQ_COUNT ; 
 int /*<<< orphan*/  IT8152_LP_IRQ (int) ; 
 int IT8152_LP_IRQ_COUNT ; 
 int /*<<< orphan*/  IT8152_PD_IRQ (int) ; 
 int IT8152_PD_IRQ_COUNT ; 
 int __ffs (int) ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 

void it8152_irq_demux(struct irq_desc *desc)
{
       int bits_pd, bits_lp, bits_ld;
       int i;

       while (1) {
	       /* Read all */
	       bits_pd = __raw_readl(IT8152_INTC_PDCNIRR);
	       bits_lp = __raw_readl(IT8152_INTC_LPCNIRR);
	       bits_ld = __raw_readl(IT8152_INTC_LDCNIRR);

	       /* Ack */
	       __raw_writel((~bits_pd), IT8152_INTC_PDCNIRR);
	       __raw_writel((~bits_lp), IT8152_INTC_LPCNIRR);
	       __raw_writel((~bits_ld), IT8152_INTC_LDCNIRR);

	       if (!(bits_ld | bits_lp | bits_pd)) {
		       /* Re-read to guarantee, that there was a moment of
			  time, when they all three were 0. */
		       bits_pd = __raw_readl(IT8152_INTC_PDCNIRR);
		       bits_lp = __raw_readl(IT8152_INTC_LPCNIRR);
		       bits_ld = __raw_readl(IT8152_INTC_LDCNIRR);
		       if (!(bits_ld | bits_lp | bits_pd))
			       return;
	       }

	       bits_pd &= ((1 << IT8152_PD_IRQ_COUNT) - 1);
	       while (bits_pd) {
		       i = __ffs(bits_pd);
		       generic_handle_irq(IT8152_PD_IRQ(i));
		       bits_pd &= ~(1 << i);
	       }

	       bits_lp &= ((1 << IT8152_LP_IRQ_COUNT) - 1);
	       while (bits_lp) {
		       i = __ffs(bits_lp);
		       generic_handle_irq(IT8152_LP_IRQ(i));
		       bits_lp &= ~(1 << i);
	       }

	       bits_ld &= ((1 << IT8152_LD_IRQ_COUNT) - 1);
	       while (bits_ld) {
		       i = __ffs(bits_ld);
		       generic_handle_irq(IT8152_LD_IRQ(i));
		       bits_ld &= ~(1 << i);
	       }
       }
}