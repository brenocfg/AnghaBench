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
struct thermal_zone_device {TYPE_1__* tzp; } ;
struct resource {int dummy; } ;
struct rcar_gen3_thermal_tsc {int id; struct thermal_zone_device* zone; struct thermal_zone_device* base; } ;
struct rcar_gen3_thermal_priv {int num_tscs; int /*<<< orphan*/  (* thermal_init ) (struct rcar_gen3_thermal_tsc*) ;struct rcar_gen3_thermal_tsc** tscs; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {int no_hwmon; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (struct thermal_zone_device*) ; 
 int PTR_ERR (struct thermal_zone_device*) ; 
 int TSC_MAX_NUM ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int,int) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,struct thermal_zone_device*) ; 
 struct thermal_zone_device* devm_ioremap_resource (struct device*,struct resource*) ; 
 char* devm_kasprintf (struct device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct rcar_gen3_thermal_priv*) ; 
 struct thermal_zone_device* devm_thermal_zone_of_sensor_register (struct device*,int,struct rcar_gen3_thermal_tsc*,int /*<<< orphan*/ *) ; 
 int* of_device_get_match_data (struct device*) ; 
 int of_thermal_get_ntrips (struct thermal_zone_device*) ; 
 int platform_get_irq (struct platform_device*,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rcar_gen3_thermal_priv*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  r8a7795es1 ; 
 int /*<<< orphan*/  rcar_gen3_hwmon_action ; 
 int /*<<< orphan*/  rcar_gen3_thermal_calc_coefs (struct rcar_gen3_thermal_tsc*,int*,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  rcar_gen3_thermal_init (struct rcar_gen3_thermal_tsc*) ; 
 int /*<<< orphan*/  rcar_gen3_thermal_init_r8a7795es1 (struct rcar_gen3_thermal_tsc*) ; 
 int /*<<< orphan*/  rcar_gen3_thermal_irq ; 
 int /*<<< orphan*/  rcar_gen3_thermal_remove (struct platform_device*) ; 
 int /*<<< orphan*/  rcar_gen3_tz_of_ops ; 
 int /*<<< orphan*/  rcar_thermal_irq_set (struct rcar_gen3_thermal_priv*,int) ; 
 scalar_t__ soc_device_match (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct rcar_gen3_thermal_tsc*) ; 
 int /*<<< orphan*/ * thcode ; 
 int thermal_add_hwmon_sysfs (struct thermal_zone_device*) ; 

__attribute__((used)) static int rcar_gen3_thermal_probe(struct platform_device *pdev)
{
	struct rcar_gen3_thermal_priv *priv;
	struct device *dev = &pdev->dev;
	const int *rcar_gen3_ths_tj_1 = of_device_get_match_data(dev);
	struct resource *res;
	struct thermal_zone_device *zone;
	int ret, irq, i;
	char *irqname;

	/* default values if FUSEs are missing */
	/* TODO: Read values from hardware on supported platforms */
	int ptat[3] = { 2631, 1509, 435 };

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->thermal_init = rcar_gen3_thermal_init;
	if (soc_device_match(r8a7795es1))
		priv->thermal_init = rcar_gen3_thermal_init_r8a7795es1;

	platform_set_drvdata(pdev, priv);

	/*
	 * Request 2 (of the 3 possible) IRQs, the driver only needs to
	 * to trigger on the low and high trip points of the current
	 * temp window at this point.
	 */
	for (i = 0; i < 2; i++) {
		irq = platform_get_irq(pdev, i);
		if (irq < 0)
			return irq;

		irqname = devm_kasprintf(dev, GFP_KERNEL, "%s:ch%d",
					 dev_name(dev), i);
		if (!irqname)
			return -ENOMEM;

		ret = devm_request_threaded_irq(dev, irq, NULL,
						rcar_gen3_thermal_irq,
						IRQF_ONESHOT, irqname, priv);
		if (ret)
			return ret;
	}

	pm_runtime_enable(dev);
	pm_runtime_get_sync(dev);

	for (i = 0; i < TSC_MAX_NUM; i++) {
		struct rcar_gen3_thermal_tsc *tsc;

		res = platform_get_resource(pdev, IORESOURCE_MEM, i);
		if (!res)
			break;

		tsc = devm_kzalloc(dev, sizeof(*tsc), GFP_KERNEL);
		if (!tsc) {
			ret = -ENOMEM;
			goto error_unregister;
		}

		tsc->base = devm_ioremap_resource(dev, res);
		if (IS_ERR(tsc->base)) {
			ret = PTR_ERR(tsc->base);
			goto error_unregister;
		}
		tsc->id = i;

		priv->tscs[i] = tsc;

		priv->thermal_init(tsc);
		rcar_gen3_thermal_calc_coefs(tsc, ptat, thcode[i],
					     *rcar_gen3_ths_tj_1);

		zone = devm_thermal_zone_of_sensor_register(dev, i, tsc,
							    &rcar_gen3_tz_of_ops);
		if (IS_ERR(zone)) {
			dev_err(dev, "Can't register thermal zone\n");
			ret = PTR_ERR(zone);
			goto error_unregister;
		}
		tsc->zone = zone;

		tsc->zone->tzp->no_hwmon = false;
		ret = thermal_add_hwmon_sysfs(tsc->zone);
		if (ret)
			goto error_unregister;

		ret = devm_add_action_or_reset(dev, rcar_gen3_hwmon_action, zone);
		if (ret) {
			goto error_unregister;
		}

		ret = of_thermal_get_ntrips(tsc->zone);
		if (ret < 0)
			goto error_unregister;

		dev_info(dev, "TSC%d: Loaded %d trip points\n", i, ret);
	}

	priv->num_tscs = i;

	if (!priv->num_tscs) {
		ret = -ENODEV;
		goto error_unregister;
	}

	rcar_thermal_irq_set(priv, true);

	return 0;

error_unregister:
	rcar_gen3_thermal_remove(pdev);

	return ret;
}