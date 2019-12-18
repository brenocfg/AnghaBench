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
struct wcove_tmu {int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  BXTWC_TMUIRQ ; 
 unsigned int BXTWC_TMU_ALRM_IRQ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static irqreturn_t bxt_wcove_tmu_irq_handler(int irq, void *data)
{
	struct wcove_tmu *wctmu = data;
	unsigned int tmu_irq;

	/* Read TMU interrupt reg */
	regmap_read(wctmu->regmap, BXTWC_TMUIRQ, &tmu_irq);
	if (tmu_irq & BXTWC_TMU_ALRM_IRQ) {
		/* clear TMU irq */
		regmap_write(wctmu->regmap, BXTWC_TMUIRQ, tmu_irq);
		return IRQ_HANDLED;
	}
	return IRQ_NONE;
}