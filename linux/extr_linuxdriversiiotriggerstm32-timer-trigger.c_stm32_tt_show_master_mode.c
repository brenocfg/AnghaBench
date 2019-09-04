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
typedef  size_t u32 ;
struct stm32_timer_trigger {int /*<<< orphan*/  regmap; } ;
struct iio_trigger {int /*<<< orphan*/  name; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  TIM_CR2 ; 
 size_t TIM_CR2_MMS ; 
 size_t TIM_CR2_MMS2 ; 
 size_t TIM_CR2_MMS2_SHIFT ; 
 size_t TIM_CR2_MMS_SHIFT ; 
 struct stm32_timer_trigger* dev_get_drvdata (struct device*) ; 
 char** master_mode_table ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ stm32_timer_is_trgo2_name (int /*<<< orphan*/ ) ; 
 struct iio_trigger* to_iio_trigger (struct device*) ; 

__attribute__((used)) static ssize_t stm32_tt_show_master_mode(struct device *dev,
					 struct device_attribute *attr,
					 char *buf)
{
	struct stm32_timer_trigger *priv = dev_get_drvdata(dev);
	struct iio_trigger *trig = to_iio_trigger(dev);
	u32 cr2;

	regmap_read(priv->regmap, TIM_CR2, &cr2);

	if (stm32_timer_is_trgo2_name(trig->name))
		cr2 = (cr2 & TIM_CR2_MMS2) >> TIM_CR2_MMS2_SHIFT;
	else
		cr2 = (cr2 & TIM_CR2_MMS) >> TIM_CR2_MMS_SHIFT;

	return snprintf(buf, PAGE_SIZE, "%s\n", master_mode_table[cr2]);
}