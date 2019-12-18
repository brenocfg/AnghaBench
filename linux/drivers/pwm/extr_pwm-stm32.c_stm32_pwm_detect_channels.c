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
struct stm32_pwm {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIM_CCER ; 
 int TIM_CCER_CC1E ; 
 int TIM_CCER_CC2E ; 
 int TIM_CCER_CC3E ; 
 int TIM_CCER_CC4E ; 
 int /*<<< orphan*/  TIM_CCER_CCXE ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_pwm_detect_channels(struct stm32_pwm *priv)
{
	u32 ccer;
	int npwm = 0;

	/*
	 * If channels enable bits don't exist writing 1 will have no
	 * effect so we can detect and count them.
	 */
	regmap_update_bits(priv->regmap,
			   TIM_CCER, TIM_CCER_CCXE, TIM_CCER_CCXE);
	regmap_read(priv->regmap, TIM_CCER, &ccer);
	regmap_update_bits(priv->regmap, TIM_CCER, TIM_CCER_CCXE, 0);

	if (ccer & TIM_CCER_CC1E)
		npwm++;

	if (ccer & TIM_CCER_CC2E)
		npwm++;

	if (ccer & TIM_CCER_CC3E)
		npwm++;

	if (ccer & TIM_CCER_CC4E)
		npwm++;

	return npwm;
}