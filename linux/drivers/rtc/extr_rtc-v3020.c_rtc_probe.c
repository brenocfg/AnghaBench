#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct v3020_platform_data {scalar_t__ use_gpio; } ;
struct v3020 {TYPE_3__* ops; int /*<<< orphan*/  rtc; int /*<<< orphan*/  leftshift; TYPE_1__* gpio; } ;
struct platform_device {int /*<<< orphan*/  dev; TYPE_2__* resource; } ;
struct TYPE_7__ {int (* map_io ) (struct v3020*,struct platform_device*,struct v3020_platform_data*) ;int (* read_bit ) (struct v3020*) ;int /*<<< orphan*/  (* unmap_io ) (struct v3020*) ;} ;
struct TYPE_6__ {scalar_t__ start; } ;
struct TYPE_5__ {int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 size_t V3020_CS ; 
 size_t V3020_IO ; 
 size_t V3020_RD ; 
 int /*<<< orphan*/  V3020_SECONDS ; 
 int /*<<< orphan*/  V3020_STATUS_0 ; 
 size_t V3020_WR ; 
 struct v3020_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned long long,int /*<<< orphan*/ ,...) ; 
 struct v3020* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_rtc_device_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct v3020*) ; 
 int stub1 (struct v3020*,struct platform_device*,struct v3020_platform_data*) ; 
 int stub2 (struct v3020*) ; 
 int /*<<< orphan*/  stub3 (struct v3020*) ; 
 int v3020_get_reg (struct v3020*,int /*<<< orphan*/ ) ; 
 TYPE_3__ v3020_gpio_ops ; 
 TYPE_3__ v3020_mmio_ops ; 
 int /*<<< orphan*/  v3020_rtc_ops ; 
 int /*<<< orphan*/  v3020_set_reg (struct v3020*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rtc_probe(struct platform_device *pdev)
{
	struct v3020_platform_data *pdata = dev_get_platdata(&pdev->dev);
	struct v3020 *chip;
	int retval = -EBUSY;
	int i;
	int temp;

	chip = devm_kzalloc(&pdev->dev, sizeof(*chip), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	if (pdata->use_gpio)
		chip->ops = &v3020_gpio_ops;
	else
		chip->ops = &v3020_mmio_ops;

	retval = chip->ops->map_io(chip, pdev, pdata);
	if (retval)
		return retval;

	/* Make sure the v3020 expects a communication cycle
	 * by reading 8 times */
	for (i = 0; i < 8; i++)
		temp = chip->ops->read_bit(chip);

	/* Test chip by doing a write/read sequence
	 * to the chip ram */
	v3020_set_reg(chip, V3020_SECONDS, 0x33);
	if (v3020_get_reg(chip, V3020_SECONDS) != 0x33) {
		retval = -ENODEV;
		goto err_io;
	}

	/* Make sure frequency measurement mode, test modes, and lock
	 * are all disabled */
	v3020_set_reg(chip, V3020_STATUS_0, 0x0);

	if (pdata->use_gpio)
		dev_info(&pdev->dev, "Chip available at GPIOs "
			 "%d, %d, %d, %d\n",
			 chip->gpio[V3020_CS].gpio, chip->gpio[V3020_WR].gpio,
			 chip->gpio[V3020_RD].gpio, chip->gpio[V3020_IO].gpio);
	else
		dev_info(&pdev->dev, "Chip available at "
			 "physical address 0x%llx,"
			 "data connected to D%d\n",
			 (unsigned long long)pdev->resource[0].start,
			 chip->leftshift);

	platform_set_drvdata(pdev, chip);

	chip->rtc = devm_rtc_device_register(&pdev->dev, "v3020",
					&v3020_rtc_ops, THIS_MODULE);
	if (IS_ERR(chip->rtc)) {
		retval = PTR_ERR(chip->rtc);
		goto err_io;
	}

	return 0;

err_io:
	chip->ops->unmap_io(chip);

	return retval;
}