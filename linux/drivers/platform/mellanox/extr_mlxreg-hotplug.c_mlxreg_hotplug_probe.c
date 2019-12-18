#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mlxreg_hotplug_priv_data {scalar_t__ irq; int after_probe; int /*<<< orphan*/  hwmon; int /*<<< orphan*/  groups; int /*<<< orphan*/  dwork_irq; int /*<<< orphan*/  lock; struct platform_device* pdev; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
struct mlxreg_core_hotplug_platform_data {scalar_t__ irq; int /*<<< orphan*/  regmap; int /*<<< orphan*/  deferred_nr; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_SHARED ; 
 int IRQF_TRIGGER_FALLING ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 struct mlxreg_core_hotplug_platform_data* dev_get_platdata (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct mlxreg_hotplug_priv_data*) ; 
 int /*<<< orphan*/  devm_hwmon_device_register_with_groups (TYPE_1__*,char*,struct mlxreg_hotplug_priv_data*,int /*<<< orphan*/ ) ; 
 struct mlxreg_hotplug_priv_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_1__*,int,int /*<<< orphan*/ ,int,char*,struct mlxreg_hotplug_priv_data*) ; 
 int /*<<< orphan*/  disable_irq (int) ; 
 struct i2c_adapter* i2c_get_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_put_adapter (struct i2c_adapter*) ; 
 int mlxreg_hotplug_attr_init (struct mlxreg_hotplug_priv_data*) ; 
 int /*<<< orphan*/  mlxreg_hotplug_irq_handler ; 
 int /*<<< orphan*/  mlxreg_hotplug_set_irq (struct mlxreg_hotplug_priv_data*) ; 
 int /*<<< orphan*/  mlxreg_hotplug_work_handler ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlxreg_hotplug_probe(struct platform_device *pdev)
{
	struct mlxreg_core_hotplug_platform_data *pdata;
	struct mlxreg_hotplug_priv_data *priv;
	struct i2c_adapter *deferred_adap;
	int err;

	pdata = dev_get_platdata(&pdev->dev);
	if (!pdata) {
		dev_err(&pdev->dev, "Failed to get platform data.\n");
		return -EINVAL;
	}

	/* Defer probing if the necessary adapter is not configured yet. */
	deferred_adap = i2c_get_adapter(pdata->deferred_nr);
	if (!deferred_adap)
		return -EPROBE_DEFER;
	i2c_put_adapter(deferred_adap);

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	if (pdata->irq) {
		priv->irq = pdata->irq;
	} else {
		priv->irq = platform_get_irq(pdev, 0);
		if (priv->irq < 0)
			return priv->irq;
	}

	priv->regmap = pdata->regmap;
	priv->dev = pdev->dev.parent;
	priv->pdev = pdev;

	err = devm_request_irq(&pdev->dev, priv->irq,
			       mlxreg_hotplug_irq_handler, IRQF_TRIGGER_FALLING
			       | IRQF_SHARED, "mlxreg-hotplug", priv);
	if (err) {
		dev_err(&pdev->dev, "Failed to request irq: %d\n", err);
		return err;
	}

	disable_irq(priv->irq);
	spin_lock_init(&priv->lock);
	INIT_DELAYED_WORK(&priv->dwork_irq, mlxreg_hotplug_work_handler);
	dev_set_drvdata(&pdev->dev, priv);

	err = mlxreg_hotplug_attr_init(priv);
	if (err) {
		dev_err(&pdev->dev, "Failed to allocate attributes: %d\n",
			err);
		return err;
	}

	priv->hwmon = devm_hwmon_device_register_with_groups(&pdev->dev,
					"mlxreg_hotplug", priv, priv->groups);
	if (IS_ERR(priv->hwmon)) {
		dev_err(&pdev->dev, "Failed to register hwmon device %ld\n",
			PTR_ERR(priv->hwmon));
		return PTR_ERR(priv->hwmon);
	}

	/* Perform initial interrupts setup. */
	mlxreg_hotplug_set_irq(priv);
	priv->after_probe = true;

	return 0;
}