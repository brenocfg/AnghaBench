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
struct stm32_timer_trigger {int /*<<< orphan*/  regmap; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIM_ARR ; 
 int /*<<< orphan*/  TIM_CCER ; 
 int TIM_CCER_CCXE ; 
 int /*<<< orphan*/  TIM_CR1 ; 
 int TIM_CR1_ARPE ; 
 int TIM_CR1_CEN ; 
 int /*<<< orphan*/  TIM_EGR ; 
 int TIM_EGR_UG ; 
 int /*<<< orphan*/  TIM_PSC ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stm32_timer_stop(struct stm32_timer_trigger *priv)
{
	u32 ccer, cr1;

	regmap_read(priv->regmap, TIM_CCER, &ccer);
	if (ccer & TIM_CCER_CCXE)
		return;

	regmap_read(priv->regmap, TIM_CR1, &cr1);
	if (cr1 & TIM_CR1_CEN)
		clk_disable(priv->clk);

	/* Stop timer */
	regmap_update_bits(priv->regmap, TIM_CR1, TIM_CR1_ARPE, 0);
	regmap_update_bits(priv->regmap, TIM_CR1, TIM_CR1_CEN, 0);
	regmap_write(priv->regmap, TIM_PSC, 0);
	regmap_write(priv->regmap, TIM_ARR, 0);

	/* Make sure that registers are updated */
	regmap_update_bits(priv->regmap, TIM_EGR, TIM_EGR_UG, TIM_EGR_UG);
}