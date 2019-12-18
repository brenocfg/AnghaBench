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
struct stm32_timer_trigger {unsigned long long max_arr; int /*<<< orphan*/  regmap; int /*<<< orphan*/  clk; int /*<<< orphan*/  dev; } ;
struct iio_trigger {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int MAX_TIM_PSC ; 
 int /*<<< orphan*/  TIM_ARR ; 
 int /*<<< orphan*/  TIM_CCER ; 
 int TIM_CCER_CCXE ; 
 int /*<<< orphan*/  TIM_CR1 ; 
 int TIM_CR1_ARPE ; 
 int TIM_CR1_CEN ; 
 int /*<<< orphan*/  TIM_CR2 ; 
 int TIM_CR2_MMS ; 
 int TIM_CR2_MMS2 ; 
 int TIM_CR2_MMS2_SHIFT ; 
 int TIM_CR2_MMS_SHIFT ; 
 int /*<<< orphan*/  TIM_EGR ; 
 int TIM_EGR_UG ; 
 int /*<<< orphan*/  TIM_PSC ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 scalar_t__ clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  do_div (unsigned long long,int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long) ; 
 scalar_t__ stm32_timer_is_trgo2_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_timer_start(struct stm32_timer_trigger *priv,
			     struct iio_trigger *trig,
			     unsigned int frequency)
{
	unsigned long long prd, div;
	int prescaler = 0;
	u32 ccer, cr1;

	/* Period and prescaler values depends of clock rate */
	div = (unsigned long long)clk_get_rate(priv->clk);

	do_div(div, frequency);

	prd = div;

	/*
	 * Increase prescaler value until we get a result that fit
	 * with auto reload register maximum value.
	 */
	while (div > priv->max_arr) {
		prescaler++;
		div = prd;
		do_div(div, (prescaler + 1));
	}
	prd = div;

	if (prescaler > MAX_TIM_PSC) {
		dev_err(priv->dev, "prescaler exceeds the maximum value\n");
		return -EINVAL;
	}

	/* Check if nobody else use the timer */
	regmap_read(priv->regmap, TIM_CCER, &ccer);
	if (ccer & TIM_CCER_CCXE)
		return -EBUSY;

	regmap_read(priv->regmap, TIM_CR1, &cr1);
	if (!(cr1 & TIM_CR1_CEN))
		clk_enable(priv->clk);

	regmap_write(priv->regmap, TIM_PSC, prescaler);
	regmap_write(priv->regmap, TIM_ARR, prd - 1);
	regmap_update_bits(priv->regmap, TIM_CR1, TIM_CR1_ARPE, TIM_CR1_ARPE);

	/* Force master mode to update mode */
	if (stm32_timer_is_trgo2_name(trig->name))
		regmap_update_bits(priv->regmap, TIM_CR2, TIM_CR2_MMS2,
				   0x2 << TIM_CR2_MMS2_SHIFT);
	else
		regmap_update_bits(priv->regmap, TIM_CR2, TIM_CR2_MMS,
				   0x2 << TIM_CR2_MMS_SHIFT);

	/* Make sure that registers are updated */
	regmap_update_bits(priv->regmap, TIM_EGR, TIM_EGR_UG, TIM_EGR_UG);

	/* Enable controller */
	regmap_update_bits(priv->regmap, TIM_CR1, TIM_CR1_CEN, TIM_CR1_CEN);

	return 0;
}