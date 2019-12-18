#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_9__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_8__ {TYPE_2__* parent; } ;
struct iio_dev {int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct cc10001_adc_device {int shared; unsigned long eoc_delay_ns; int start_delay_ns; int /*<<< orphan*/  reg; int /*<<< orphan*/  adc_clk; int /*<<< orphan*/  lock; int /*<<< orphan*/  reg_base; } ;

/* Variables and functions */
 scalar_t__ CC10001_ADC_NUM_CHANNELS ; 
 int CC10001_WAIT_CYCLES ; 
 int EINVAL ; 
 int ENOMEM ; 
 unsigned long GENMASK (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 unsigned long NSEC_PER_SEC ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int cc10001_adc_channel_init (struct iio_dev*,unsigned long) ; 
 int /*<<< orphan*/  cc10001_adc_info ; 
 int /*<<< orphan*/  cc10001_adc_power_up (struct cc10001_adc_device*) ; 
 int /*<<< orphan*/  cc10001_adc_trigger_h ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,char*) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_2__*,int) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 int /*<<< orphan*/  devm_regulator_get (TYPE_2__*,char*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct cc10001_adc_device* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int iio_triggered_buffer_setup (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct iio_dev*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cc10001_adc_probe(struct platform_device *pdev)
{
	struct device_node *node = pdev->dev.of_node;
	struct cc10001_adc_device *adc_dev;
	unsigned long adc_clk_rate;
	struct resource *res;
	struct iio_dev *indio_dev;
	unsigned long channel_map;
	int ret;

	indio_dev = devm_iio_device_alloc(&pdev->dev, sizeof(*adc_dev));
	if (indio_dev == NULL)
		return -ENOMEM;

	adc_dev = iio_priv(indio_dev);

	channel_map = GENMASK(CC10001_ADC_NUM_CHANNELS - 1, 0);
	if (!of_property_read_u32(node, "adc-reserved-channels", &ret)) {
		adc_dev->shared = true;
		channel_map &= ~ret;
	}

	adc_dev->reg = devm_regulator_get(&pdev->dev, "vref");
	if (IS_ERR(adc_dev->reg))
		return PTR_ERR(adc_dev->reg);

	ret = regulator_enable(adc_dev->reg);
	if (ret)
		return ret;

	indio_dev->dev.parent = &pdev->dev;
	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->info = &cc10001_adc_info;
	indio_dev->modes = INDIO_DIRECT_MODE;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	adc_dev->reg_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(adc_dev->reg_base)) {
		ret = PTR_ERR(adc_dev->reg_base);
		goto err_disable_reg;
	}

	adc_dev->adc_clk = devm_clk_get(&pdev->dev, "adc");
	if (IS_ERR(adc_dev->adc_clk)) {
		dev_err(&pdev->dev, "failed to get the clock\n");
		ret = PTR_ERR(adc_dev->adc_clk);
		goto err_disable_reg;
	}

	ret = clk_prepare_enable(adc_dev->adc_clk);
	if (ret) {
		dev_err(&pdev->dev, "failed to enable the clock\n");
		goto err_disable_reg;
	}

	adc_clk_rate = clk_get_rate(adc_dev->adc_clk);
	if (!adc_clk_rate) {
		ret = -EINVAL;
		dev_err(&pdev->dev, "null clock rate!\n");
		goto err_disable_clk;
	}

	adc_dev->eoc_delay_ns = NSEC_PER_SEC / adc_clk_rate;
	adc_dev->start_delay_ns = adc_dev->eoc_delay_ns * CC10001_WAIT_CYCLES;

	/*
	 * There is only one register to power-up/power-down the AUX ADC.
	 * If the ADC is shared among multiple CPUs, always power it up here.
	 * If the ADC is used only by the MIPS, power-up/power-down at runtime.
	 */
	if (adc_dev->shared)
		cc10001_adc_power_up(adc_dev);

	/* Setup the ADC channels available on the device */
	ret = cc10001_adc_channel_init(indio_dev, channel_map);
	if (ret < 0)
		goto err_disable_clk;

	mutex_init(&adc_dev->lock);

	ret = iio_triggered_buffer_setup(indio_dev, NULL,
					 &cc10001_adc_trigger_h, NULL);
	if (ret < 0)
		goto err_disable_clk;

	ret = iio_device_register(indio_dev);
	if (ret < 0)
		goto err_cleanup_buffer;

	platform_set_drvdata(pdev, indio_dev);

	return 0;

err_cleanup_buffer:
	iio_triggered_buffer_cleanup(indio_dev);
err_disable_clk:
	clk_disable_unprepare(adc_dev->adc_clk);
err_disable_reg:
	regulator_disable(adc_dev->reg);
	return ret;
}