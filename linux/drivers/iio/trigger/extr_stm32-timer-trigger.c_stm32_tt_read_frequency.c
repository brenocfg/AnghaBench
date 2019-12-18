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
struct stm32_timer_trigger {int /*<<< orphan*/  clk; int /*<<< orphan*/  regmap; } ;
struct iio_trigger {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  TIM_ARR ; 
 int /*<<< orphan*/  TIM_CR1 ; 
 int TIM_CR1_CEN ; 
 int /*<<< orphan*/  TIM_PSC ; 
 scalar_t__ clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (unsigned long long,int) ; 
 struct stm32_timer_trigger* iio_trigger_get_drvdata (struct iio_trigger*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 struct iio_trigger* to_iio_trigger (struct device*) ; 

__attribute__((used)) static ssize_t stm32_tt_read_frequency(struct device *dev,
				       struct device_attribute *attr, char *buf)
{
	struct iio_trigger *trig = to_iio_trigger(dev);
	struct stm32_timer_trigger *priv = iio_trigger_get_drvdata(trig);
	u32 psc, arr, cr1;
	unsigned long long freq = 0;

	regmap_read(priv->regmap, TIM_CR1, &cr1);
	regmap_read(priv->regmap, TIM_PSC, &psc);
	regmap_read(priv->regmap, TIM_ARR, &arr);

	if (cr1 & TIM_CR1_CEN) {
		freq = (unsigned long long)clk_get_rate(priv->clk);
		do_div(freq, psc + 1);
		do_div(freq, arr + 1);
	}

	return sprintf(buf, "%d\n", (unsigned int)freq);
}