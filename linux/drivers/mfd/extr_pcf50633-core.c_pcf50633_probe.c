#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct pcf50633_platform_data {int /*<<< orphan*/  (* probe_done ) (struct pcf50633*) ;int /*<<< orphan*/ * reg_init_data; } ;
struct pcf50633 {struct platform_device** regulator_pdev; TYPE_2__* dev; int /*<<< orphan*/  bl_pdev; int /*<<< orphan*/  adc_pdev; int /*<<< orphan*/  mbc_pdev; int /*<<< orphan*/  rtc_pdev; int /*<<< orphan*/  input_pdev; int /*<<< orphan*/  regmap; int /*<<< orphan*/  lock; struct pcf50633_platform_data* pdata; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_2__ dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PCF50633_NUM_REGULATORS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 struct pcf50633_platform_data* dev_get_platdata (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*,int,int) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 struct pcf50633* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct pcf50633*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcf50633_client_dev_register (struct pcf50633*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcf50633_irq_init (struct pcf50633*,int /*<<< orphan*/ ) ; 
 int pcf50633_reg_read (struct pcf50633*,int) ; 
 int /*<<< orphan*/  pcf50633_regmap_config ; 
 int /*<<< orphan*/  pcf_attr_group ; 
 int platform_device_add (struct platform_device*) ; 
 int platform_device_add_data (struct platform_device*,int /*<<< orphan*/ *,int) ; 
 struct platform_device* platform_device_alloc (char*,int) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 
 int /*<<< orphan*/  stub1 (struct pcf50633*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pcf50633_probe(struct i2c_client *client,
				const struct i2c_device_id *ids)
{
	struct pcf50633 *pcf;
	struct platform_device *pdev;
	struct pcf50633_platform_data *pdata = dev_get_platdata(&client->dev);
	int i, j, ret;
	int version, variant;

	if (!client->irq) {
		dev_err(&client->dev, "Missing IRQ\n");
		return -ENOENT;
	}

	pcf = devm_kzalloc(&client->dev, sizeof(*pcf), GFP_KERNEL);
	if (!pcf)
		return -ENOMEM;

	i2c_set_clientdata(client, pcf);
	pcf->dev = &client->dev;
	pcf->pdata = pdata;

	mutex_init(&pcf->lock);

	pcf->regmap = devm_regmap_init_i2c(client, &pcf50633_regmap_config);
	if (IS_ERR(pcf->regmap)) {
		ret = PTR_ERR(pcf->regmap);
		dev_err(pcf->dev, "Failed to allocate register map: %d\n", ret);
		return ret;
	}

	version = pcf50633_reg_read(pcf, 0);
	variant = pcf50633_reg_read(pcf, 1);
	if (version < 0 || variant < 0) {
		dev_err(pcf->dev, "Unable to probe pcf50633\n");
		ret = -ENODEV;
		return ret;
	}

	dev_info(pcf->dev, "Probed device version %d variant %d\n",
							version, variant);

	pcf50633_irq_init(pcf, client->irq);

	/* Create sub devices */
	pcf50633_client_dev_register(pcf, "pcf50633-input", &pcf->input_pdev);
	pcf50633_client_dev_register(pcf, "pcf50633-rtc", &pcf->rtc_pdev);
	pcf50633_client_dev_register(pcf, "pcf50633-mbc", &pcf->mbc_pdev);
	pcf50633_client_dev_register(pcf, "pcf50633-adc", &pcf->adc_pdev);
	pcf50633_client_dev_register(pcf, "pcf50633-backlight", &pcf->bl_pdev);


	for (i = 0; i < PCF50633_NUM_REGULATORS; i++) {
		pdev = platform_device_alloc("pcf50633-regulator", i);
		if (!pdev) {
			ret = -ENOMEM;
			goto err2;
		}

		pdev->dev.parent = pcf->dev;
		ret = platform_device_add_data(pdev, &pdata->reg_init_data[i],
					       sizeof(pdata->reg_init_data[i]));
		if (ret)
			goto err;

		ret = platform_device_add(pdev);
		if (ret)
			goto err;

		pcf->regulator_pdev[i] = pdev;
	}

	ret = sysfs_create_group(&client->dev.kobj, &pcf_attr_group);
	if (ret)
		dev_warn(pcf->dev, "error creating sysfs entries\n");

	if (pdata->probe_done)
		pdata->probe_done(pcf);

	return 0;

err:
	platform_device_put(pdev);
err2:
	for (j = 0; j < i; j++)
		platform_device_put(pcf->regulator_pdev[j]);

	return ret;
}