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
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 unsigned long BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDS32_SR_INT_MASK2 ; 
 unsigned long __nds32__mfsr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __nds32__mtsr_dsb (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ativic32_mask_irq(struct irq_data *data)
{
	unsigned long int_mask2 = __nds32__mfsr(NDS32_SR_INT_MASK2);
	__nds32__mtsr_dsb(int_mask2 & (~(BIT(data->hwirq))), NDS32_SR_INT_MASK2);
}