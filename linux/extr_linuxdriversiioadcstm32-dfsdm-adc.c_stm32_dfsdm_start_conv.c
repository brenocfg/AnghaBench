#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stm32_dfsdm_adc {TYPE_1__* dfsdm; int /*<<< orphan*/  fl_id; } ;
struct regmap {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  channel; } ;
struct TYPE_5__ {struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFSDM_CR1 (int /*<<< orphan*/ ) ; 
 unsigned int DFSDM_CR1_RCONT (int) ; 
 int /*<<< orphan*/  DFSDM_CR1_RCONT_MASK ; 
 unsigned int DFSDM_CR1_RDMAEN (int) ; 
 int /*<<< orphan*/  DFSDM_CR1_RDMAEN_MASK ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int stm32_dfsdm_filter_configure (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stm32_dfsdm_start_channel (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int stm32_dfsdm_start_filter (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_dfsdm_stop_channel (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_dfsdm_start_conv(struct stm32_dfsdm_adc *adc,
				  const struct iio_chan_spec *chan,
				  bool dma)
{
	struct regmap *regmap = adc->dfsdm->regmap;
	int ret;
	unsigned int dma_en = 0, cont_en = 0;

	ret = stm32_dfsdm_start_channel(adc->dfsdm, chan->channel);
	if (ret < 0)
		return ret;

	ret = stm32_dfsdm_filter_configure(adc->dfsdm, adc->fl_id,
					   chan->channel);
	if (ret < 0)
		goto stop_channels;

	if (dma) {
		/* Enable DMA transfer*/
		dma_en =  DFSDM_CR1_RDMAEN(1);
		/* Enable conversion triggered by SPI clock*/
		cont_en = DFSDM_CR1_RCONT(1);
	}
	/* Enable DMA transfer*/
	ret = regmap_update_bits(regmap, DFSDM_CR1(adc->fl_id),
				 DFSDM_CR1_RDMAEN_MASK, dma_en);
	if (ret < 0)
		goto stop_channels;

	/* Enable conversion triggered by SPI clock*/
	ret = regmap_update_bits(regmap, DFSDM_CR1(adc->fl_id),
				 DFSDM_CR1_RCONT_MASK, cont_en);
	if (ret < 0)
		goto stop_channels;

	ret = stm32_dfsdm_start_filter(adc->dfsdm, adc->fl_id);
	if (ret < 0)
		goto stop_channels;

	return 0;

stop_channels:
	regmap_update_bits(regmap, DFSDM_CR1(adc->fl_id),
			   DFSDM_CR1_RDMAEN_MASK, 0);

	regmap_update_bits(regmap, DFSDM_CR1(adc->fl_id),
			   DFSDM_CR1_RCONT_MASK, 0);
	stm32_dfsdm_stop_channel(adc->dfsdm, chan->channel);

	return ret;
}