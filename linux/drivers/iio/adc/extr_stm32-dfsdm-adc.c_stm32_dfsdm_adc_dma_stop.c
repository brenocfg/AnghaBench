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
struct stm32_dfsdm_adc {int /*<<< orphan*/  dma_chan; int /*<<< orphan*/  fl_id; TYPE_1__* dfsdm; } ;
struct iio_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFSDM_CR1 (int /*<<< orphan*/ ) ; 
 int DFSDM_CR1_JDMAEN_MASK ; 
 int DFSDM_CR1_RDMAEN_MASK ; 
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ ) ; 
 struct stm32_dfsdm_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stm32_dfsdm_adc_dma_stop(struct iio_dev *indio_dev)
{
	struct stm32_dfsdm_adc *adc = iio_priv(indio_dev);

	if (!adc->dma_chan)
		return;

	regmap_update_bits(adc->dfsdm->regmap, DFSDM_CR1(adc->fl_id),
			   DFSDM_CR1_RDMAEN_MASK | DFSDM_CR1_JDMAEN_MASK, 0);
	dmaengine_terminate_all(adc->dma_chan);
}