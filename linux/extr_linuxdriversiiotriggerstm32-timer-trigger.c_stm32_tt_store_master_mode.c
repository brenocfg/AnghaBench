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
struct stm32_timer_trigger {int /*<<< orphan*/  regmap; } ;
struct iio_trigger {int /*<<< orphan*/  name; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int MASTER_MODE2_MAX ; 
 int MASTER_MODE_MAX ; 
 int /*<<< orphan*/  TIM_CR2 ; 
 int TIM_CR2_MMS ; 
 int TIM_CR2_MMS2 ; 
 int TIM_CR2_MMS2_SHIFT ; 
 int TIM_CR2_MMS_SHIFT ; 
 int /*<<< orphan*/  TIM_EGR ; 
 int TIM_EGR_UG ; 
 struct stm32_timer_trigger* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/ * master_mode_table ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ stm32_timer_is_trgo2_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 struct iio_trigger* to_iio_trigger (struct device*) ; 

__attribute__((used)) static ssize_t stm32_tt_store_master_mode(struct device *dev,
					  struct device_attribute *attr,
					  const char *buf, size_t len)
{
	struct stm32_timer_trigger *priv = dev_get_drvdata(dev);
	struct iio_trigger *trig = to_iio_trigger(dev);
	u32 mask, shift, master_mode_max;
	int i;

	if (stm32_timer_is_trgo2_name(trig->name)) {
		mask = TIM_CR2_MMS2;
		shift = TIM_CR2_MMS2_SHIFT;
		master_mode_max = MASTER_MODE2_MAX;
	} else {
		mask = TIM_CR2_MMS;
		shift = TIM_CR2_MMS_SHIFT;
		master_mode_max = MASTER_MODE_MAX;
	}

	for (i = 0; i <= master_mode_max; i++) {
		if (!strncmp(master_mode_table[i], buf,
			     strlen(master_mode_table[i]))) {
			regmap_update_bits(priv->regmap, TIM_CR2, mask,
					   i << shift);
			/* Make sure that registers are updated */
			regmap_update_bits(priv->regmap, TIM_EGR,
					   TIM_EGR_UG, TIM_EGR_UG);
			return len;
		}
	}

	return -EINVAL;
}