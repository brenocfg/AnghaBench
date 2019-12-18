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
typedef  int /*<<< orphan*/  u32 ;
struct stm32_timer_trigger {int has_trgo2; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIM_CR2 ; 
 int /*<<< orphan*/  TIM_CR2_MMS2 ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stm32_timer_detect_trgo2(struct stm32_timer_trigger *priv)
{
	u32 val;

	/*
	 * Master mode selection 2 bits can only be written and read back when
	 * timer supports it.
	 */
	regmap_update_bits(priv->regmap, TIM_CR2, TIM_CR2_MMS2, TIM_CR2_MMS2);
	regmap_read(priv->regmap, TIM_CR2, &val);
	regmap_update_bits(priv->regmap, TIM_CR2, TIM_CR2_MMS2, 0);
	priv->has_trgo2 = !!val;
}