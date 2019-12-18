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
struct stm32_dfsdm_adc {int nconv; struct stm32_dfsdm* dfsdm; } ;
struct stm32_dfsdm {int /*<<< orphan*/  regmap; } ;
struct iio_trigger {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFSDM_CR1 (unsigned int) ; 
 int /*<<< orphan*/  DFSDM_CR1_DFEN (int) ; 
 int /*<<< orphan*/  DFSDM_CR1_DFEN_MASK ; 
 int /*<<< orphan*/  DFSDM_CR1_RSWSTART (int) ; 
 int /*<<< orphan*/  DFSDM_CR1_RSWSTART_MASK ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_dfsdm_start_filter(struct stm32_dfsdm_adc *adc,
				    unsigned int fl_id,
				    struct iio_trigger *trig)
{
	struct stm32_dfsdm *dfsdm = adc->dfsdm;
	int ret;

	/* Enable filter */
	ret = regmap_update_bits(dfsdm->regmap, DFSDM_CR1(fl_id),
				 DFSDM_CR1_DFEN_MASK, DFSDM_CR1_DFEN(1));
	if (ret < 0)
		return ret;

	/* Nothing more to do for injected (scan mode/triggered) conversions */
	if (adc->nconv > 1 || trig)
		return 0;

	/* Software start (single or continuous) regular conversion */
	return regmap_update_bits(dfsdm->regmap, DFSDM_CR1(fl_id),
				  DFSDM_CR1_RSWSTART_MASK,
				  DFSDM_CR1_RSWSTART(1));
}