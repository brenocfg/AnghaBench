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
struct stm32_dfsdm_adc {unsigned int* buffer; int /*<<< orphan*/  fl_id; int /*<<< orphan*/  completion; TYPE_1__* dfsdm; } ;
struct regmap {int dummy; } ;
struct iio_dev {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFSDM_CR2 (int /*<<< orphan*/ ) ; 
 unsigned int DFSDM_CR2_ROVRIE_MASK ; 
 int /*<<< orphan*/  DFSDM_ICR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DFSDM_ICR_CLRROVRF_MASK ; 
 int /*<<< orphan*/  DFSDM_ISR (int /*<<< orphan*/ ) ; 
 unsigned int DFSDM_ISR_REOCF_MASK ; 
 unsigned int DFSDM_ISR_ROVRF_MASK ; 
 int /*<<< orphan*/  DFSDM_RDATAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct iio_dev* iio_priv_to_dev (struct stm32_dfsdm_adc*) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t stm32_dfsdm_irq(int irq, void *arg)
{
	struct stm32_dfsdm_adc *adc = arg;
	struct iio_dev *indio_dev = iio_priv_to_dev(adc);
	struct regmap *regmap = adc->dfsdm->regmap;
	unsigned int status, int_en;

	regmap_read(regmap, DFSDM_ISR(adc->fl_id), &status);
	regmap_read(regmap, DFSDM_CR2(adc->fl_id), &int_en);

	if (status & DFSDM_ISR_REOCF_MASK) {
		/* Read the data register clean the IRQ status */
		regmap_read(regmap, DFSDM_RDATAR(adc->fl_id), adc->buffer);
		complete(&adc->completion);
	}

	if (status & DFSDM_ISR_ROVRF_MASK) {
		if (int_en & DFSDM_CR2_ROVRIE_MASK)
			dev_warn(&indio_dev->dev, "Overrun detected\n");
		regmap_update_bits(regmap, DFSDM_ICR(adc->fl_id),
				   DFSDM_ICR_CLRROVRF_MASK,
				   DFSDM_ICR_CLRROVRF_MASK);
	}

	return IRQ_HANDLED;
}