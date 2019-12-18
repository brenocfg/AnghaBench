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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
struct envelope {unsigned long invert; int /*<<< orphan*/  read_lock; int /*<<< orphan*/  comp_irq; int /*<<< orphan*/  comp_irq_trigger; int /*<<< orphan*/  comp_irq_trigger_inv; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 struct envelope* iio_priv (struct iio_dev*) ; 
 int irq_set_irq_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t envelope_store_invert(struct iio_dev *indio_dev,
				     uintptr_t private,
				     struct iio_chan_spec const *ch,
				     const char *buf, size_t len)
{
	struct envelope *env = iio_priv(indio_dev);
	unsigned long invert;
	int ret;
	u32 trigger;

	ret = kstrtoul(buf, 0, &invert);
	if (ret < 0)
		return ret;
	if (invert > 1)
		return -EINVAL;

	trigger = invert ? env->comp_irq_trigger_inv : env->comp_irq_trigger;

	mutex_lock(&env->read_lock);
	if (invert != env->invert)
		ret = irq_set_irq_type(env->comp_irq, trigger);
	if (!ret) {
		env->invert = invert;
		ret = len;
	}
	mutex_unlock(&env->read_lock);

	return ret;
}