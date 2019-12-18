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
struct imx6ul_tsc {int /*<<< orphan*/  completion; scalar_t__ adc_regs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ REG_ADC_HS ; 
 scalar_t__ REG_ADC_R0 ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static irqreturn_t adc_irq_fn(int irq, void *dev_id)
{
	struct imx6ul_tsc *tsc = dev_id;
	u32 coco;
	u32 value;

	coco = readl(tsc->adc_regs + REG_ADC_HS);
	if (coco & 0x01) {
		value = readl(tsc->adc_regs + REG_ADC_R0);
		complete(&tsc->completion);
	}

	return IRQ_HANDLED;
}