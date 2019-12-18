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
struct s3c_hwmon_pdata {struct s3c_hwmon_chcfg** in; } ;
struct s3c_hwmon_chcfg {int mult; scalar_t__ div; } ;
struct s3c_hwmon {int /*<<< orphan*/  client; int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/ * attrs; int /*<<< orphan*/  lock; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct s3c_hwmon_chcfg**) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct s3c_hwmon_pdata* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 struct s3c_hwmon* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwmon_device_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct s3c_hwmon*) ; 
 int /*<<< orphan*/  s3c_adc_register (struct platform_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c_adc_release (int /*<<< orphan*/ ) ; 
 int s3c_hwmon_add_raw (int /*<<< orphan*/ *) ; 
 int s3c_hwmon_create_attr (int /*<<< orphan*/ *,struct s3c_hwmon_chcfg*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  s3c_hwmon_remove_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s3c_hwmon_remove_raw (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int s3c_hwmon_probe(struct platform_device *dev)
{
	struct s3c_hwmon_pdata *pdata = dev_get_platdata(&dev->dev);
	struct s3c_hwmon *hwmon;
	int ret = 0;
	int i;

	if (!pdata) {
		dev_err(&dev->dev, "no platform data supplied\n");
		return -EINVAL;
	}

	hwmon = devm_kzalloc(&dev->dev, sizeof(struct s3c_hwmon), GFP_KERNEL);
	if (hwmon == NULL)
		return -ENOMEM;

	platform_set_drvdata(dev, hwmon);

	mutex_init(&hwmon->lock);

	/* Register with the core ADC driver. */

	hwmon->client = s3c_adc_register(dev, NULL, NULL, 0);
	if (IS_ERR(hwmon->client)) {
		dev_err(&dev->dev, "cannot register adc\n");
		return PTR_ERR(hwmon->client);
	}

	/* add attributes for our adc devices. */

	ret = s3c_hwmon_add_raw(&dev->dev);
	if (ret)
		goto err_registered;

	/* register with the hwmon core */

	hwmon->hwmon_dev = hwmon_device_register(&dev->dev);
	if (IS_ERR(hwmon->hwmon_dev)) {
		dev_err(&dev->dev, "error registering with hwmon\n");
		ret = PTR_ERR(hwmon->hwmon_dev);
		goto err_raw_attribute;
	}

	for (i = 0; i < ARRAY_SIZE(pdata->in); i++) {
		struct s3c_hwmon_chcfg *cfg = pdata->in[i];

		if (!cfg)
			continue;

		if (cfg->mult >= 0x10000)
			dev_warn(&dev->dev,
				 "channel %d multiplier too large\n",
				 i);

		if (cfg->div == 0) {
			dev_err(&dev->dev, "channel %d divider zero\n", i);
			continue;
		}

		ret = s3c_hwmon_create_attr(&dev->dev, pdata->in[i],
					    &hwmon->attrs[i], i);
		if (ret) {
			dev_err(&dev->dev,
					"error creating channel %d\n", i);

			for (i--; i >= 0; i--)
				s3c_hwmon_remove_attr(&dev->dev,
							      &hwmon->attrs[i]);

			goto err_hwmon_register;
		}
	}

	return 0;

 err_hwmon_register:
	hwmon_device_unregister(hwmon->hwmon_dev);

 err_raw_attribute:
	s3c_hwmon_remove_raw(&dev->dev);

 err_registered:
	s3c_adc_release(hwmon->client);

	return ret;
}