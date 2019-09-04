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
struct vf610_dac {int /*<<< orphan*/  clk; int /*<<< orphan*/  regs; TYPE_2__* dev; } ;
struct resource {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; TYPE_2__* parent; } ;
struct iio_dev {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,char*) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_2__*,int) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct vf610_dac* iio_priv (struct iio_dev*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct iio_dev*) ; 
 int /*<<< orphan*/  vf610_dac_iio_channels ; 
 int /*<<< orphan*/  vf610_dac_iio_info ; 
 int /*<<< orphan*/  vf610_dac_init (struct vf610_dac*) ; 

__attribute__((used)) static int vf610_dac_probe(struct platform_device *pdev)
{
	struct iio_dev *indio_dev;
	struct vf610_dac *info;
	struct resource *mem;
	int ret;

	indio_dev = devm_iio_device_alloc(&pdev->dev,
					sizeof(struct vf610_dac));
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

	info->clk = devm_clk_get(&pdev->dev, "dac");
	if (IS_ERR(info->clk)) {
		dev_err(&pdev->dev, "Failed getting clock, err = %ld\n",
			PTR_ERR(info->clk));
		return PTR_ERR(info->clk);
	}

	platform_set_drvdata(pdev, indio_dev);

	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->dev.parent = &pdev->dev;
	indio_dev->dev.of_node = pdev->dev.of_node;
	indio_dev->info = &vf610_dac_iio_info;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = vf610_dac_iio_channels;
	indio_dev->num_channels = ARRAY_SIZE(vf610_dac_iio_channels);

	ret = clk_prepare_enable(info->clk);
	if (ret) {
		dev_err(&pdev->dev,
			"Could not prepare or enable the clock\n");
		return ret;
	}

	vf610_dac_init(info);

	ret = iio_device_register(indio_dev);
	if (ret) {
		dev_err(&pdev->dev, "Couldn't register the device\n");
		goto error_iio_device_register;
	}

	return 0;

error_iio_device_register:
	clk_disable_unprepare(info->clk);

	return ret;
}