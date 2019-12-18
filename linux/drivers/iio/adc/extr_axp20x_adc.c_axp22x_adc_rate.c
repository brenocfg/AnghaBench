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
struct axp20x_adc_iio {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXP20X_ADC_RATE ; 
 int /*<<< orphan*/  AXP20X_ADC_RATE_MASK ; 
 int /*<<< orphan*/  AXP22X_ADC_RATE_HZ (int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int axp22x_adc_rate(struct axp20x_adc_iio *info, int rate)
{
	return regmap_update_bits(info->regmap, AXP20X_ADC_RATE,
				  AXP20X_ADC_RATE_MASK,
				  AXP22X_ADC_RATE_HZ(rate));
}