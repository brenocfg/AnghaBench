#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device {int /*<<< orphan*/  parent; int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct dln2_platform_data {int port; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; struct device* parent; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; TYPE_3__ dev; int /*<<< orphan*/ * quirks; int /*<<< orphan*/ * algo; int /*<<< orphan*/  class; int /*<<< orphan*/  owner; } ;
struct dln2_i2c {int port; TYPE_1__ adapter; struct platform_device* pdev; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_COMPANION (struct device*) ; 
 int /*<<< orphan*/  ACPI_COMPANION_SET (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DLN2_I2C_BUF_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_CLASS_HWMON ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct dln2_platform_data* dev_get_platdata (struct device*) ; 
 char* dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kmalloc (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dln2_i2c* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int dln2_i2c_enable (struct dln2_i2c*,int) ; 
 int /*<<< orphan*/  dln2_i2c_quirks ; 
 int /*<<< orphan*/  dln2_i2c_usb_algorithm ; 
 int i2c_add_adapter (TYPE_1__*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_1__*,struct dln2_i2c*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct dln2_i2c*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char*,int) ; 

__attribute__((used)) static int dln2_i2c_probe(struct platform_device *pdev)
{
	int ret;
	struct dln2_i2c *dln2;
	struct device *dev = &pdev->dev;
	struct dln2_platform_data *pdata = dev_get_platdata(&pdev->dev);

	dln2 = devm_kzalloc(dev, sizeof(*dln2), GFP_KERNEL);
	if (!dln2)
		return -ENOMEM;

	dln2->buf = devm_kmalloc(dev, DLN2_I2C_BUF_SIZE, GFP_KERNEL);
	if (!dln2->buf)
		return -ENOMEM;

	dln2->pdev = pdev;
	dln2->port = pdata->port;

	/* setup i2c adapter description */
	dln2->adapter.owner = THIS_MODULE;
	dln2->adapter.class = I2C_CLASS_HWMON;
	dln2->adapter.algo = &dln2_i2c_usb_algorithm;
	dln2->adapter.quirks = &dln2_i2c_quirks;
	dln2->adapter.dev.parent = dev;
	ACPI_COMPANION_SET(&dln2->adapter.dev, ACPI_COMPANION(&pdev->dev));
	dln2->adapter.dev.of_node = dev->of_node;
	i2c_set_adapdata(&dln2->adapter, dln2);
	snprintf(dln2->adapter.name, sizeof(dln2->adapter.name), "%s-%s-%d",
		 "dln2-i2c", dev_name(pdev->dev.parent), dln2->port);

	platform_set_drvdata(pdev, dln2);

	/* initialize the i2c interface */
	ret = dln2_i2c_enable(dln2, true);
	if (ret < 0) {
		dev_err(dev, "failed to initialize adapter: %d\n", ret);
		return ret;
	}

	/* and finally attach to i2c layer */
	ret = i2c_add_adapter(&dln2->adapter);
	if (ret < 0)
		goto out_disable;

	return 0;

out_disable:
	dln2_i2c_enable(dln2, false);

	return ret;
}