#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct siox_master {scalar_t__ busno; int /*<<< orphan*/  pushpull; } ;
struct siox_gpio_ddata {void* dld; void* dclk; void* dout; void* din; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 void* devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct siox_master*) ; 
 int /*<<< orphan*/  siox_gpio_pushpull ; 
 struct siox_master* siox_master_alloc (struct device*,int) ; 
 struct siox_gpio_ddata* siox_master_get_devdata (struct siox_master*) ; 
 int /*<<< orphan*/  siox_master_put (struct siox_master*) ; 
 int siox_master_register (struct siox_master*) ; 

__attribute__((used)) static int siox_gpio_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct siox_gpio_ddata *ddata;
	int ret;
	struct siox_master *smaster;

	smaster = siox_master_alloc(&pdev->dev, sizeof(*ddata));
	if (!smaster) {
		dev_err(dev, "failed to allocate siox master\n");
		return -ENOMEM;
	}

	platform_set_drvdata(pdev, smaster);
	ddata = siox_master_get_devdata(smaster);

	ddata->din = devm_gpiod_get(dev, "din", GPIOD_IN);
	if (IS_ERR(ddata->din)) {
		ret = PTR_ERR(ddata->din);
		dev_err(dev, "Failed to get %s GPIO: %d\n", "din", ret);
		goto err;
	}

	ddata->dout = devm_gpiod_get(dev, "dout", GPIOD_OUT_LOW);
	if (IS_ERR(ddata->dout)) {
		ret = PTR_ERR(ddata->dout);
		dev_err(dev, "Failed to get %s GPIO: %d\n", "dout", ret);
		goto err;
	}

	ddata->dclk = devm_gpiod_get(dev, "dclk", GPIOD_OUT_LOW);
	if (IS_ERR(ddata->dclk)) {
		ret = PTR_ERR(ddata->dclk);
		dev_err(dev, "Failed to get %s GPIO: %d\n", "dclk", ret);
		goto err;
	}

	ddata->dld = devm_gpiod_get(dev, "dld", GPIOD_OUT_LOW);
	if (IS_ERR(ddata->dld)) {
		ret = PTR_ERR(ddata->dld);
		dev_err(dev, "Failed to get %s GPIO: %d\n", "dld", ret);
		goto err;
	}

	smaster->pushpull = siox_gpio_pushpull;
	/* XXX: determine automatically like spi does */
	smaster->busno = 0;

	ret = siox_master_register(smaster);
	if (ret) {
		dev_err(dev, "Failed to register siox master: %d\n", ret);
err:
		siox_master_put(smaster);
	}

	return ret;
}