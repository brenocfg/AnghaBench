#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct thermal_zone_device {int dummy; } ;
struct resource {int dummy; } ;
struct TYPE_11__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct mtk_thermal {struct thermal_zone_device* clk_auxadc; struct thermal_zone_device* clk_peri_therm; TYPE_1__* conf; TYPE_2__* dev; int /*<<< orphan*/  lock; struct thermal_zone_device* thermal_base; } ;
struct device_node {int dummy; } ;
struct TYPE_10__ {int num_controller; int num_banks; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct thermal_zone_device*) ; 
 scalar_t__ OF_BAD_ADDR ; 
 int PTR_ERR (struct thermal_zone_device*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct thermal_zone_device*) ; 
 int clk_prepare_enable (struct thermal_zone_device*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int device_reset (TYPE_2__*) ; 
 void* devm_clk_get (TYPE_2__*,char*) ; 
 struct thermal_zone_device* devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct mtk_thermal* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 struct thermal_zone_device* devm_thermal_zone_of_sensor_register (TYPE_2__*,int /*<<< orphan*/ ,struct mtk_thermal*,int /*<<< orphan*/ *) ; 
 int mtk_thermal_get_calibration_data (TYPE_2__*,struct mtk_thermal*) ; 
 int /*<<< orphan*/  mtk_thermal_init_bank (struct mtk_thermal*,int,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  mtk_thermal_ops ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* of_device_get_match_data (TYPE_2__*) ; 
 scalar_t__ of_get_phys_base (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mtk_thermal*) ; 

__attribute__((used)) static int mtk_thermal_probe(struct platform_device *pdev)
{
	int ret, i, ctrl_id;
	struct device_node *auxadc, *apmixedsys, *np = pdev->dev.of_node;
	struct mtk_thermal *mt;
	struct resource *res;
	u64 auxadc_phys_base, apmixed_phys_base;
	struct thermal_zone_device *tzdev;

	mt = devm_kzalloc(&pdev->dev, sizeof(*mt), GFP_KERNEL);
	if (!mt)
		return -ENOMEM;

	mt->conf = of_device_get_match_data(&pdev->dev);

	mt->clk_peri_therm = devm_clk_get(&pdev->dev, "therm");
	if (IS_ERR(mt->clk_peri_therm))
		return PTR_ERR(mt->clk_peri_therm);

	mt->clk_auxadc = devm_clk_get(&pdev->dev, "auxadc");
	if (IS_ERR(mt->clk_auxadc))
		return PTR_ERR(mt->clk_auxadc);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	mt->thermal_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(mt->thermal_base))
		return PTR_ERR(mt->thermal_base);

	ret = mtk_thermal_get_calibration_data(&pdev->dev, mt);
	if (ret)
		return ret;

	mutex_init(&mt->lock);

	mt->dev = &pdev->dev;

	auxadc = of_parse_phandle(np, "mediatek,auxadc", 0);
	if (!auxadc) {
		dev_err(&pdev->dev, "missing auxadc node\n");
		return -ENODEV;
	}

	auxadc_phys_base = of_get_phys_base(auxadc);

	of_node_put(auxadc);

	if (auxadc_phys_base == OF_BAD_ADDR) {
		dev_err(&pdev->dev, "Can't get auxadc phys address\n");
		return -EINVAL;
	}

	apmixedsys = of_parse_phandle(np, "mediatek,apmixedsys", 0);
	if (!apmixedsys) {
		dev_err(&pdev->dev, "missing apmixedsys node\n");
		return -ENODEV;
	}

	apmixed_phys_base = of_get_phys_base(apmixedsys);

	of_node_put(apmixedsys);

	if (apmixed_phys_base == OF_BAD_ADDR) {
		dev_err(&pdev->dev, "Can't get auxadc phys address\n");
		return -EINVAL;
	}

	ret = device_reset(&pdev->dev);
	if (ret)
		return ret;

	ret = clk_prepare_enable(mt->clk_auxadc);
	if (ret) {
		dev_err(&pdev->dev, "Can't enable auxadc clk: %d\n", ret);
		return ret;
	}

	ret = clk_prepare_enable(mt->clk_peri_therm);
	if (ret) {
		dev_err(&pdev->dev, "Can't enable peri clk: %d\n", ret);
		goto err_disable_clk_auxadc;
	}

	for (ctrl_id = 0; ctrl_id < mt->conf->num_controller ; ctrl_id++)
		for (i = 0; i < mt->conf->num_banks; i++)
			mtk_thermal_init_bank(mt, i, apmixed_phys_base,
					      auxadc_phys_base, ctrl_id);

	platform_set_drvdata(pdev, mt);

	tzdev = devm_thermal_zone_of_sensor_register(&pdev->dev, 0, mt,
						     &mtk_thermal_ops);
	if (IS_ERR(tzdev)) {
		ret = PTR_ERR(tzdev);
		goto err_disable_clk_peri_therm;
	}

	return 0;

err_disable_clk_peri_therm:
	clk_disable_unprepare(mt->clk_peri_therm);
err_disable_clk_auxadc:
	clk_disable_unprepare(mt->clk_auxadc);

	return ret;
}