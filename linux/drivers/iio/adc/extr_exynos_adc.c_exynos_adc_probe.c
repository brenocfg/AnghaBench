#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct s3c2410_ts_mach_info {int delay; } ;
struct resource {int dummy; } ;
struct TYPE_13__ {struct device_node* of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct TYPE_11__ {struct device_node* of_node; TYPE_3__* parent; } ;
struct iio_dev {TYPE_1__ dev; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; int /*<<< orphan*/  name; } ;
struct exynos_adc {int irq; int tsirq; int delay; void* vdd; TYPE_2__* data; int /*<<< orphan*/  input; void* sclk; void* clk; int /*<<< orphan*/  completion; TYPE_3__* dev; void* pmu_map; void* regs; } ;
struct device_node {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* exit_hw ) (struct exynos_adc*) ;int /*<<< orphan*/  (* init_hw ) (struct exynos_adc*) ;int /*<<< orphan*/  num_channels; scalar_t__ needs_sclk; scalar_t__ needs_adc_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_INPUT ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 scalar_t__ IS_REACHABLE (int /*<<< orphan*/ ) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 struct s3c2410_ts_mach_info* dev_get_platdata (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_name (TYPE_3__*) ; 
 int /*<<< orphan*/  device_for_each_child (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* devm_clk_get (TYPE_3__*,char*) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_3__*,int) ; 
 void* devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 void* devm_regulator_get (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  exynos_adc_disable_clk (struct exynos_adc*) ; 
 int exynos_adc_enable_clk (struct exynos_adc*) ; 
 TYPE_2__* exynos_adc_get_data (struct platform_device*) ; 
 int /*<<< orphan*/  exynos_adc_iio_channels ; 
 int /*<<< orphan*/  exynos_adc_iio_info ; 
 int /*<<< orphan*/  exynos_adc_isr ; 
 int /*<<< orphan*/  exynos_adc_match ; 
 int exynos_adc_prepare_clk (struct exynos_adc*) ; 
 int /*<<< orphan*/  exynos_adc_remove_devices ; 
 int exynos_adc_ts_init (struct exynos_adc*) ; 
 int /*<<< orphan*/  exynos_adc_unprepare_clk (struct exynos_adc*) ; 
 int /*<<< orphan*/  free_irq (int,struct exynos_adc*) ; 
 int iio_device_register (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct exynos_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int of_platform_populate (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int platform_get_irq (struct platform_device*,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct iio_dev*) ; 
 int /*<<< orphan*/  regulator_disable (void*) ; 
 int regulator_enable (void*) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct exynos_adc*) ; 
 int /*<<< orphan*/  stub1 (struct exynos_adc*) ; 
 int /*<<< orphan*/  stub2 (struct exynos_adc*) ; 
 void* syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 

__attribute__((used)) static int exynos_adc_probe(struct platform_device *pdev)
{
	struct exynos_adc *info = NULL;
	struct device_node *np = pdev->dev.of_node;
	struct s3c2410_ts_mach_info *pdata = dev_get_platdata(&pdev->dev);
	struct iio_dev *indio_dev = NULL;
	struct resource	*mem;
	bool has_ts = false;
	int ret = -ENODEV;
	int irq;

	indio_dev = devm_iio_device_alloc(&pdev->dev, sizeof(struct exynos_adc));
	if (!indio_dev) {
		dev_err(&pdev->dev, "failed allocating iio device\n");
		return -ENOMEM;
	}

	info = iio_priv(indio_dev);

	info->data = exynos_adc_get_data(pdev);
	if (!info->data) {
		dev_err(&pdev->dev, "failed getting exynos_adc_data\n");
		return -EINVAL;
	}

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	info->regs = devm_ioremap_resource(&pdev->dev, mem);
	if (IS_ERR(info->regs))
		return PTR_ERR(info->regs);


	if (info->data->needs_adc_phy) {
		info->pmu_map = syscon_regmap_lookup_by_phandle(
					pdev->dev.of_node,
					"samsung,syscon-phandle");
		if (IS_ERR(info->pmu_map)) {
			dev_err(&pdev->dev, "syscon regmap lookup failed.\n");
			return PTR_ERR(info->pmu_map);
		}
	}

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;
	info->irq = irq;

	irq = platform_get_irq(pdev, 1);
	if (irq == -EPROBE_DEFER)
		return irq;

	info->tsirq = irq;

	info->dev = &pdev->dev;

	init_completion(&info->completion);

	info->clk = devm_clk_get(&pdev->dev, "adc");
	if (IS_ERR(info->clk)) {
		dev_err(&pdev->dev, "failed getting clock, err = %ld\n",
							PTR_ERR(info->clk));
		return PTR_ERR(info->clk);
	}

	if (info->data->needs_sclk) {
		info->sclk = devm_clk_get(&pdev->dev, "sclk");
		if (IS_ERR(info->sclk)) {
			dev_err(&pdev->dev,
				"failed getting sclk clock, err = %ld\n",
				PTR_ERR(info->sclk));
			return PTR_ERR(info->sclk);
		}
	}

	info->vdd = devm_regulator_get(&pdev->dev, "vdd");
	if (IS_ERR(info->vdd)) {
		dev_err(&pdev->dev, "failed getting regulator, err = %ld\n",
							PTR_ERR(info->vdd));
		return PTR_ERR(info->vdd);
	}

	ret = regulator_enable(info->vdd);
	if (ret)
		return ret;

	ret = exynos_adc_prepare_clk(info);
	if (ret)
		goto err_disable_reg;

	ret = exynos_adc_enable_clk(info);
	if (ret)
		goto err_unprepare_clk;

	platform_set_drvdata(pdev, indio_dev);

	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->dev.parent = &pdev->dev;
	indio_dev->dev.of_node = pdev->dev.of_node;
	indio_dev->info = &exynos_adc_iio_info;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = exynos_adc_iio_channels;
	indio_dev->num_channels = info->data->num_channels;

	ret = request_irq(info->irq, exynos_adc_isr,
					0, dev_name(&pdev->dev), info);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed requesting irq, irq = %d\n",
							info->irq);
		goto err_disable_clk;
	}

	ret = iio_device_register(indio_dev);
	if (ret)
		goto err_irq;

	if (info->data->init_hw)
		info->data->init_hw(info);

	/* leave out any TS related code if unreachable */
	if (IS_REACHABLE(CONFIG_INPUT)) {
		has_ts = of_property_read_bool(pdev->dev.of_node,
					       "has-touchscreen") || pdata;
	}

	if (pdata)
		info->delay = pdata->delay;
	else
		info->delay = 10000;

	if (has_ts)
		ret = exynos_adc_ts_init(info);
	if (ret)
		goto err_iio;

	ret = of_platform_populate(np, exynos_adc_match, NULL, &indio_dev->dev);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed adding child nodes\n");
		goto err_of_populate;
	}

	return 0;

err_of_populate:
	device_for_each_child(&indio_dev->dev, NULL,
				exynos_adc_remove_devices);
	if (has_ts) {
		input_unregister_device(info->input);
		free_irq(info->tsirq, info);
	}
err_iio:
	iio_device_unregister(indio_dev);
err_irq:
	free_irq(info->irq, info);
err_disable_clk:
	if (info->data->exit_hw)
		info->data->exit_hw(info);
	exynos_adc_disable_clk(info);
err_unprepare_clk:
	exynos_adc_unprepare_clk(info);
err_disable_reg:
	regulator_disable(info->vdd);
	return ret;
}