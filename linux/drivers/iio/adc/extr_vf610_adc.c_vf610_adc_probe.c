#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  default_sample_time; } ;
struct vf610_adc {int /*<<< orphan*/  vref; int /*<<< orphan*/  clk; int /*<<< orphan*/  completion; TYPE_1__ adc_feature; int /*<<< orphan*/  max_adck_rate; int /*<<< orphan*/  vref_uv; TYPE_3__* dev; int /*<<< orphan*/  regs; } ;
struct resource {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct TYPE_11__ {int /*<<< orphan*/  of_node; TYPE_3__* parent; } ;
struct iio_dev {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_2__ dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEFAULT_SAMPLE_TIME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  dev_name (TYPE_3__*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_3__*,char*) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_3__*,int) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 int /*<<< orphan*/  devm_regulator_get (TYPE_3__*,char*) ; 
 int devm_request_irq (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iio_dev*) ; 
 int iio_device_register (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_pollfunc_store_time ; 
 struct vf610_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int iio_triggered_buffer_setup (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_triggered_buffer_setup_ops ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_property_read_u32_array (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct iio_dev*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_get_voltage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vf610_adc_cfg_init (struct vf610_adc*) ; 
 int /*<<< orphan*/  vf610_adc_hw_init (struct vf610_adc*) ; 
 int /*<<< orphan*/  vf610_adc_iio_channels ; 
 int /*<<< orphan*/  vf610_adc_iio_info ; 
 int /*<<< orphan*/  vf610_adc_isr ; 

__attribute__((used)) static int vf610_adc_probe(struct platform_device *pdev)
{
	struct vf610_adc *info;
	struct iio_dev *indio_dev;
	struct resource *mem;
	int irq;
	int ret;

	indio_dev = devm_iio_device_alloc(&pdev->dev, sizeof(struct vf610_adc));
	if (!indio_dev) {
		dev_err(&pdev->dev, "Failed allocating iio device\n");
		return -ENOMEM;
	}

	info = iio_priv(indio_dev);
	info->dev = &pdev->dev;

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	info->regs = devm_ioremap_resource(&pdev->dev, mem);
	if (IS_ERR(info->regs))
		return PTR_ERR(info->regs);

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	ret = devm_request_irq(info->dev, irq,
				vf610_adc_isr, 0,
				dev_name(&pdev->dev), indio_dev);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed requesting irq, irq = %d\n", irq);
		return ret;
	}

	info->clk = devm_clk_get(&pdev->dev, "adc");
	if (IS_ERR(info->clk)) {
		dev_err(&pdev->dev, "failed getting clock, err = %ld\n",
						PTR_ERR(info->clk));
		return PTR_ERR(info->clk);
	}

	info->vref = devm_regulator_get(&pdev->dev, "vref");
	if (IS_ERR(info->vref))
		return PTR_ERR(info->vref);

	ret = regulator_enable(info->vref);
	if (ret)
		return ret;

	info->vref_uv = regulator_get_voltage(info->vref);

	of_property_read_u32_array(pdev->dev.of_node, "fsl,adck-max-frequency",
			info->max_adck_rate, 3);

	ret = of_property_read_u32(pdev->dev.of_node, "min-sample-time",
			&info->adc_feature.default_sample_time);
	if (ret)
		info->adc_feature.default_sample_time = DEFAULT_SAMPLE_TIME;

	platform_set_drvdata(pdev, indio_dev);

	init_completion(&info->completion);

	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->dev.parent = &pdev->dev;
	indio_dev->dev.of_node = pdev->dev.of_node;
	indio_dev->info = &vf610_adc_iio_info;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = vf610_adc_iio_channels;
	indio_dev->num_channels = ARRAY_SIZE(vf610_adc_iio_channels);

	ret = clk_prepare_enable(info->clk);
	if (ret) {
		dev_err(&pdev->dev,
			"Could not prepare or enable the clock.\n");
		goto error_adc_clk_enable;
	}

	vf610_adc_cfg_init(info);
	vf610_adc_hw_init(info);

	ret = iio_triggered_buffer_setup(indio_dev, &iio_pollfunc_store_time,
					NULL, &iio_triggered_buffer_setup_ops);
	if (ret < 0) {
		dev_err(&pdev->dev, "Couldn't initialise the buffer\n");
		goto error_iio_device_register;
	}

	ret = iio_device_register(indio_dev);
	if (ret) {
		dev_err(&pdev->dev, "Couldn't register the device.\n");
		goto error_adc_buffer_init;
	}

	return 0;

error_adc_buffer_init:
	iio_triggered_buffer_cleanup(indio_dev);
error_iio_device_register:
	clk_disable_unprepare(info->clk);
error_adc_clk_enable:
	regulator_disable(info->vref);

	return ret;
}