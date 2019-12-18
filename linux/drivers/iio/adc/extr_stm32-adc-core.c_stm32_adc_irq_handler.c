#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {scalar_t__ base; } ;
struct stm32_adc_priv {int /*<<< orphan*/  domain; TYPE_3__* cfg; TYPE_1__ common; } ;
struct irq_desc {int dummy; } ;
struct irq_chip {int dummy; } ;
struct TYPE_6__ {TYPE_2__* regs; } ;
struct TYPE_5__ {int eoc1_msk; int eoc2_msk; int eoc3_msk; scalar_t__ csr; } ;

/* Variables and functions */
 int /*<<< orphan*/  chained_irq_enter (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  chained_irq_exit (struct irq_chip*,struct irq_desc*) ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 struct stm32_adc_priv* irq_desc_get_handler_data (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_find_mapping (int /*<<< orphan*/ ,int) ; 
 int readl_relaxed (scalar_t__) ; 
 scalar_t__ stm32_adc_eoc_enabled (struct stm32_adc_priv*,int) ; 

__attribute__((used)) static void stm32_adc_irq_handler(struct irq_desc *desc)
{
	struct stm32_adc_priv *priv = irq_desc_get_handler_data(desc);
	struct irq_chip *chip = irq_desc_get_chip(desc);
	u32 status;

	chained_irq_enter(chip, desc);
	status = readl_relaxed(priv->common.base + priv->cfg->regs->csr);

	/*
	 * End of conversion may be handled by using IRQ or DMA. There may be a
	 * race here when two conversions complete at the same time on several
	 * ADCs. EOC may be read 'set' for several ADCs, with:
	 * - an ADC configured to use DMA (EOC triggers the DMA request, and
	 *   is then automatically cleared by DR read in hardware)
	 * - an ADC configured to use IRQs (EOCIE bit is set. The handler must
	 *   be called in this case)
	 * So both EOC status bit in CSR and EOCIE control bit must be checked
	 * before invoking the interrupt handler (e.g. call ISR only for
	 * IRQ-enabled ADCs).
	 */
	if (status & priv->cfg->regs->eoc1_msk &&
	    stm32_adc_eoc_enabled(priv, 0))
		generic_handle_irq(irq_find_mapping(priv->domain, 0));

	if (status & priv->cfg->regs->eoc2_msk &&
	    stm32_adc_eoc_enabled(priv, 1))
		generic_handle_irq(irq_find_mapping(priv->domain, 1));

	if (status & priv->cfg->regs->eoc3_msk &&
	    stm32_adc_eoc_enabled(priv, 2))
		generic_handle_irq(irq_find_mapping(priv->domain, 2));

	chained_irq_exit(chip, desc);
}