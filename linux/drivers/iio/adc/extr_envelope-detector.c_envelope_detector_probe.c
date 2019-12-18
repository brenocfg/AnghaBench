#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; struct device* parent; } ;
struct iio_dev {int num_channels; int /*<<< orphan*/ * channels; int /*<<< orphan*/ * info; TYPE_1__ dev; int /*<<< orphan*/  name; } ;
struct envelope {int comp_interval; scalar_t__ comp_irq; int comp_irq_trigger; int comp_irq_trigger_inv; int /*<<< orphan*/  dac_max; int /*<<< orphan*/  dac; int /*<<< orphan*/  comp_timeout; int /*<<< orphan*/  done; int /*<<< orphan*/  read_lock; int /*<<< orphan*/  comp_lock; } ;
typedef  enum iio_chan_type { ____Placeholder_iio_chan_type } iio_chan_type ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int IIO_VOLTAGE ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_HIGH ; 
 int IRQF_TRIGGER_LOW ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  devm_iio_channel_get (struct device*,char*) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int devm_iio_device_register (struct device*,struct iio_dev*) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct envelope*) ; 
 int /*<<< orphan*/  envelope_detector_comp_isr ; 
 int /*<<< orphan*/  envelope_detector_iio_channel ; 
 int /*<<< orphan*/  envelope_detector_info ; 
 int /*<<< orphan*/  envelope_detector_timeout ; 
 int iio_get_channel_type (int /*<<< orphan*/ ,int*) ; 
 struct envelope* iio_priv (struct iio_dev*) ; 
 int iio_read_max_channel_raw (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int irq_get_trigger_type (int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ platform_get_irq_byname (struct platform_device*,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct iio_dev*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int envelope_detector_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct iio_dev *indio_dev;
	struct envelope *env;
	enum iio_chan_type type;
	int ret;

	indio_dev = devm_iio_device_alloc(dev, sizeof(*env));
	if (!indio_dev)
		return -ENOMEM;

	platform_set_drvdata(pdev, indio_dev);
	env = iio_priv(indio_dev);
	env->comp_interval = 50; /* some sensible default? */

	spin_lock_init(&env->comp_lock);
	mutex_init(&env->read_lock);
	init_completion(&env->done);
	INIT_DELAYED_WORK(&env->comp_timeout, envelope_detector_timeout);

	indio_dev->name = dev_name(dev);
	indio_dev->dev.parent = dev;
	indio_dev->dev.of_node = dev->of_node;
	indio_dev->info = &envelope_detector_info;
	indio_dev->channels = &envelope_detector_iio_channel;
	indio_dev->num_channels = 1;

	env->dac = devm_iio_channel_get(dev, "dac");
	if (IS_ERR(env->dac)) {
		if (PTR_ERR(env->dac) != -EPROBE_DEFER)
			dev_err(dev, "failed to get dac input channel\n");
		return PTR_ERR(env->dac);
	}

	env->comp_irq = platform_get_irq_byname(pdev, "comp");
	if (env->comp_irq < 0)
		return env->comp_irq;

	ret = devm_request_irq(dev, env->comp_irq, envelope_detector_comp_isr,
			       0, "envelope-detector", env);
	if (ret) {
		if (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to request interrupt\n");
		return ret;
	}
	env->comp_irq_trigger = irq_get_trigger_type(env->comp_irq);
	if (env->comp_irq_trigger & IRQF_TRIGGER_RISING)
		env->comp_irq_trigger_inv |= IRQF_TRIGGER_FALLING;
	if (env->comp_irq_trigger & IRQF_TRIGGER_FALLING)
		env->comp_irq_trigger_inv |= IRQF_TRIGGER_RISING;
	if (env->comp_irq_trigger & IRQF_TRIGGER_HIGH)
		env->comp_irq_trigger_inv |= IRQF_TRIGGER_LOW;
	if (env->comp_irq_trigger & IRQF_TRIGGER_LOW)
		env->comp_irq_trigger_inv |= IRQF_TRIGGER_HIGH;

	ret = iio_get_channel_type(env->dac, &type);
	if (ret < 0)
		return ret;

	if (type != IIO_VOLTAGE) {
		dev_err(dev, "dac is of the wrong type\n");
		return -EINVAL;
	}

	ret = iio_read_max_channel_raw(env->dac, &env->dac_max);
	if (ret < 0) {
		dev_err(dev, "dac does not indicate its raw maximum value\n");
		return ret;
	}

	return devm_iio_device_register(dev, indio_dev);
}