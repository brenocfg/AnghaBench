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
typedef  scalar_t__ u32 ;
struct TYPE_5__ {TYPE_1__* dev; } ;
struct stm32_pwm {scalar_t__* capture; scalar_t__ max_arr; int /*<<< orphan*/  regmap; TYPE_2__ chip; } ;
struct pwm_device {int hwpwm; TYPE_3__* chip; } ;
struct device {int dummy; } ;
typedef  enum stm32_timers_dmas { ____Placeholder_stm32_timers_dmas } stm32_timers_dmas ;
struct TYPE_6__ {int npwm; } ;
struct TYPE_4__ {struct device* parent; } ;

/* Variables and functions */
 int STM32_TIMERS_DMA_CH1 ; 
 int STM32_TIMERS_DMA_CH3 ; 
 int /*<<< orphan*/  TIM_CCER ; 
 scalar_t__ TIM_CCER_CC12E ; 
 scalar_t__ TIM_CCER_CC34E ; 
 scalar_t__ TIM_CCR1 ; 
 scalar_t__ TIM_CCR3 ; 
 int /*<<< orphan*/  TIM_CR1 ; 
 scalar_t__ TIM_CR1_CEN ; 
 int /*<<< orphan*/  TIM_EGR ; 
 scalar_t__ TIM_EGR_UG ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int stm32_timers_dma_burst_read (struct device*,scalar_t__*,int,scalar_t__,int,int,unsigned long) ; 

__attribute__((used)) static int stm32_pwm_raw_capture(struct stm32_pwm *priv, struct pwm_device *pwm,
				 unsigned long tmo_ms, u32 *raw_prd,
				 u32 *raw_dty)
{
	struct device *parent = priv->chip.dev->parent;
	enum stm32_timers_dmas dma_id;
	u32 ccen, ccr;
	int ret;

	/* Ensure registers have been updated, enable counter and capture */
	regmap_update_bits(priv->regmap, TIM_EGR, TIM_EGR_UG, TIM_EGR_UG);
	regmap_update_bits(priv->regmap, TIM_CR1, TIM_CR1_CEN, TIM_CR1_CEN);

	/* Use cc1 or cc3 DMA resp for PWM input channels 1 & 2 or 3 & 4 */
	dma_id = pwm->hwpwm < 2 ? STM32_TIMERS_DMA_CH1 : STM32_TIMERS_DMA_CH3;
	ccen = pwm->hwpwm < 2 ? TIM_CCER_CC12E : TIM_CCER_CC34E;
	ccr = pwm->hwpwm < 2 ? TIM_CCR1 : TIM_CCR3;
	regmap_update_bits(priv->regmap, TIM_CCER, ccen, ccen);

	/*
	 * Timer DMA burst mode. Request 2 registers, 2 bursts, to get both
	 * CCR1 & CCR2 (or CCR3 & CCR4) on each capture event.
	 * We'll get two capture snapchots: { CCR1, CCR2 }, { CCR1, CCR2 }
	 * or { CCR3, CCR4 }, { CCR3, CCR4 }
	 */
	ret = stm32_timers_dma_burst_read(parent, priv->capture, dma_id, ccr, 2,
					  2, tmo_ms);
	if (ret)
		goto stop;

	/* Period: t2 - t0 (take care of counter overflow) */
	if (priv->capture[0] <= priv->capture[2])
		*raw_prd = priv->capture[2] - priv->capture[0];
	else
		*raw_prd = priv->max_arr - priv->capture[0] + priv->capture[2];

	/* Duty cycle capture requires at least two capture units */
	if (pwm->chip->npwm < 2)
		*raw_dty = 0;
	else if (priv->capture[0] <= priv->capture[3])
		*raw_dty = priv->capture[3] - priv->capture[0];
	else
		*raw_dty = priv->max_arr - priv->capture[0] + priv->capture[3];

	if (*raw_dty > *raw_prd) {
		/*
		 * Race beetween PWM input and DMA: it may happen
		 * falling edge triggers new capture on TI2/4 before DMA
		 * had a chance to read CCR2/4. It means capture[1]
		 * contains period + duty_cycle. So, subtract period.
		 */
		*raw_dty -= *raw_prd;
	}

stop:
	regmap_update_bits(priv->regmap, TIM_CCER, ccen, 0);
	regmap_update_bits(priv->regmap, TIM_CR1, TIM_CR1_CEN, 0);

	return ret;
}