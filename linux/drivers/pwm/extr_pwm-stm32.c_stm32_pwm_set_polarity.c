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
struct stm32_pwm {int /*<<< orphan*/  regmap; scalar_t__ have_complementary_output; } ;
typedef  enum pwm_polarity { ____Placeholder_pwm_polarity } pwm_polarity ;

/* Variables and functions */
 int PWM_POLARITY_NORMAL ; 
 int /*<<< orphan*/  TIM_CCER ; 
 int TIM_CCER_CC1NP ; 
 int TIM_CCER_CC1P ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int stm32_pwm_set_polarity(struct stm32_pwm *priv, int ch,
				  enum pwm_polarity polarity)
{
	u32 mask;

	mask = TIM_CCER_CC1P << (ch * 4);
	if (priv->have_complementary_output)
		mask |= TIM_CCER_CC1NP << (ch * 4);

	regmap_update_bits(priv->regmap, TIM_CCER, mask,
			   polarity == PWM_POLARITY_NORMAL ? 0 : mask);

	return 0;
}