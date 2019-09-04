#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stm32_dfsdm_adc {TYPE_1__* dfsdm; int /*<<< orphan*/  fl_id; } ;
struct regmap {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  channel; } ;
struct TYPE_3__ {struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFSDM_CR1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DFSDM_CR1_RCONT_MASK ; 
 int /*<<< orphan*/  DFSDM_CR1_RDMAEN_MASK ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_dfsdm_stop_channel (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_dfsdm_stop_filter (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stm32_dfsdm_stop_conv(struct stm32_dfsdm_adc *adc,
				  const struct iio_chan_spec *chan)
{
	struct regmap *regmap = adc->dfsdm->regmap;

	stm32_dfsdm_stop_filter(adc->dfsdm, adc->fl_id);

	/* Clean conversion options */
	regmap_update_bits(regmap, DFSDM_CR1(adc->fl_id),
			   DFSDM_CR1_RDMAEN_MASK, 0);

	regmap_update_bits(regmap, DFSDM_CR1(adc->fl_id),
			   DFSDM_CR1_RCONT_MASK, 0);

	stm32_dfsdm_stop_channel(adc->dfsdm, chan->channel);
}