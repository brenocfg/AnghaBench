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
typedef  int u32 ;
struct resource {int /*<<< orphan*/  start; } ;
struct rcar_thermal_priv {int id; int /*<<< orphan*/  list; TYPE_2__* zone; int /*<<< orphan*/  work; int /*<<< orphan*/  lock; struct rcar_thermal_chip const* chip; struct rcar_thermal_common* common; TYPE_2__* base; } ;
struct rcar_thermal_common {TYPE_2__* base; int /*<<< orphan*/  head; struct device* dev; int /*<<< orphan*/  lock; } ;
struct rcar_thermal_chip {int nirqs; scalar_t__ irq_per_ch; scalar_t__ use_of_thermal; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_8__ {TYPE_1__* tzp; } ;
struct TYPE_7__ {int no_hwmon; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ENR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IDLE_INTERVAL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int PTR_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rcar_thermal_common*) ; 
 TYPE_2__* devm_thermal_zone_of_sensor_register (struct device*,int,struct rcar_thermal_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct rcar_thermal_chip* of_device_get_match_data (struct device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rcar_thermal_common*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  rcar_thermal_common_write (struct rcar_thermal_common*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rcar_thermal_irq ; 
 int /*<<< orphan*/  rcar_thermal_irq_enable (struct rcar_thermal_priv*) ; 
 int /*<<< orphan*/  rcar_thermal_remove (struct platform_device*) ; 
 int rcar_thermal_update_temp (struct rcar_thermal_priv*) ; 
 int /*<<< orphan*/  rcar_thermal_work ; 
 int /*<<< orphan*/  rcar_thermal_zone_of_ops ; 
 int /*<<< orphan*/  rcar_thermal_zone_ops ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int thermal_add_hwmon_sysfs (TYPE_2__*) ; 
 TYPE_2__* thermal_zone_device_register (char*,int,int /*<<< orphan*/ ,struct rcar_thermal_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rcar_thermal_probe(struct platform_device *pdev)
{
	struct rcar_thermal_common *common;
	struct rcar_thermal_priv *priv;
	struct device *dev = &pdev->dev;
	struct resource *res, *irq;
	const struct rcar_thermal_chip *chip = of_device_get_match_data(dev);
	int mres = 0;
	int i;
	int ret = -ENODEV;
	int idle = IDLE_INTERVAL;
	u32 enr_bits = 0;

	common = devm_kzalloc(dev, sizeof(*common), GFP_KERNEL);
	if (!common)
		return -ENOMEM;

	platform_set_drvdata(pdev, common);

	INIT_LIST_HEAD(&common->head);
	spin_lock_init(&common->lock);
	common->dev = dev;

	pm_runtime_enable(dev);
	pm_runtime_get_sync(dev);

	for (i = 0; i < chip->nirqs; i++) {
		irq = platform_get_resource(pdev, IORESOURCE_IRQ, i);
		if (!irq)
			continue;
		if (!common->base) {
			/*
			 * platform has IRQ support.
			 * Then, driver uses common registers
			 * rcar_has_irq_support() will be enabled
			 */
			res = platform_get_resource(pdev, IORESOURCE_MEM,
						    mres++);
			common->base = devm_ioremap_resource(dev, res);
			if (IS_ERR(common->base))
				return PTR_ERR(common->base);

			idle = 0; /* polling delay is not needed */
		}

		ret = devm_request_irq(dev, irq->start, rcar_thermal_irq,
				       IRQF_SHARED, dev_name(dev), common);
		if (ret) {
			dev_err(dev, "irq request failed\n ");
			goto error_unregister;
		}

		/* update ENR bits */
		if (chip->irq_per_ch)
			enr_bits |= 1 << i;
	}

	for (i = 0;; i++) {
		res = platform_get_resource(pdev, IORESOURCE_MEM, mres++);
		if (!res)
			break;

		priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
		if (!priv) {
			ret = -ENOMEM;
			goto error_unregister;
		}

		priv->base = devm_ioremap_resource(dev, res);
		if (IS_ERR(priv->base)) {
			ret = PTR_ERR(priv->base);
			goto error_unregister;
		}

		priv->common = common;
		priv->id = i;
		priv->chip = chip;
		mutex_init(&priv->lock);
		INIT_LIST_HEAD(&priv->list);
		INIT_DELAYED_WORK(&priv->work, rcar_thermal_work);
		ret = rcar_thermal_update_temp(priv);
		if (ret < 0)
			goto error_unregister;

		if (chip->use_of_thermal)
			priv->zone = devm_thermal_zone_of_sensor_register(
						dev, i, priv,
						&rcar_thermal_zone_of_ops);
		else
			priv->zone = thermal_zone_device_register(
						"rcar_thermal",
						1, 0, priv,
						&rcar_thermal_zone_ops, NULL, 0,
						idle);
		if (IS_ERR(priv->zone)) {
			dev_err(dev, "can't register thermal zone\n");
			ret = PTR_ERR(priv->zone);
			priv->zone = NULL;
			goto error_unregister;
		}

		if (chip->use_of_thermal) {
			/*
			 * thermal_zone doesn't enable hwmon as default,
			 * but, enable it here to keep compatible
			 */
			priv->zone->tzp->no_hwmon = false;
			ret = thermal_add_hwmon_sysfs(priv->zone);
			if (ret)
				goto error_unregister;
		}

		rcar_thermal_irq_enable(priv);

		list_move_tail(&priv->list, &common->head);

		/* update ENR bits */
		if (!chip->irq_per_ch)
			enr_bits |= 3 << (i * 8);
	}

	if (common->base && enr_bits)
		rcar_thermal_common_write(common, ENR, enr_bits);

	dev_info(dev, "%d sensor probed\n", i);

	return 0;

error_unregister:
	rcar_thermal_remove(pdev);

	return ret;
}