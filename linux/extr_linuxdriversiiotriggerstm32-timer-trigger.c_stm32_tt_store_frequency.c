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
struct stm32_timer_trigger {int dummy; } ;
struct iio_trigger {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct stm32_timer_trigger* iio_trigger_get_drvdata (struct iio_trigger*) ; 
 int kstrtouint (char const*,int,unsigned int*) ; 
 int stm32_timer_start (struct stm32_timer_trigger*,struct iio_trigger*,unsigned int) ; 
 int /*<<< orphan*/  stm32_timer_stop (struct stm32_timer_trigger*) ; 
 struct iio_trigger* to_iio_trigger (struct device*) ; 

__attribute__((used)) static ssize_t stm32_tt_store_frequency(struct device *dev,
					struct device_attribute *attr,
					const char *buf, size_t len)
{
	struct iio_trigger *trig = to_iio_trigger(dev);
	struct stm32_timer_trigger *priv = iio_trigger_get_drvdata(trig);
	unsigned int freq;
	int ret;

	ret = kstrtouint(buf, 10, &freq);
	if (ret)
		return ret;

	if (freq == 0) {
		stm32_timer_stop(priv);
	} else {
		ret = stm32_timer_start(priv, trig, freq);
		if (ret)
			return ret;
	}

	return len;
}