#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {int /*<<< orphan*/  id; TYPE_2__ dev; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; TYPE_2__* parent; } ;
struct i2c_algo_iop3xx_data {int class; int /*<<< orphan*/  ioaddr; struct i2c_algo_iop3xx_data* algo_data; int /*<<< orphan*/  lock; int /*<<< orphan*/  waitq; int /*<<< orphan*/ * algo; int /*<<< orphan*/  timeout; int /*<<< orphan*/  nr; TYPE_1__ dev; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; scalar_t__ id; void* gpio_sda; void* gpio_scl; } ;
struct i2c_adapter {int class; int /*<<< orphan*/  ioaddr; struct i2c_adapter* algo_data; int /*<<< orphan*/  lock; int /*<<< orphan*/  waitq; int /*<<< orphan*/ * algo; int /*<<< orphan*/  timeout; int /*<<< orphan*/  nr; TYPE_1__ dev; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; scalar_t__ id; void* gpio_sda; void* gpio_scl; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_ASIS ; 
 int /*<<< orphan*/  HZ ; 
 int I2C_CLASS_HWMON ; 
 int I2C_CLASS_SPD ; 
 int /*<<< orphan*/  IOP3XX_I2C_IO_SIZE ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 void* devm_gpiod_get_optional (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_add_numbered_adapter (struct i2c_algo_iop3xx_data*) ; 
 int /*<<< orphan*/  i2c_id ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iop3xx_i2c_algo ; 
 int /*<<< orphan*/  iop3xx_i2c_enable (struct i2c_algo_iop3xx_data*) ; 
 int /*<<< orphan*/  iop3xx_i2c_irq_handler ; 
 int /*<<< orphan*/  iop3xx_i2c_reset (struct i2c_algo_iop3xx_data*) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct i2c_algo_iop3xx_data*) ; 
 struct i2c_algo_iop3xx_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct i2c_algo_iop3xx_data*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct i2c_algo_iop3xx_data*) ; 
 int /*<<< orphan*/  request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iop3xx_i2c_probe(struct platform_device *pdev)
{
	struct resource *res;
	int ret, irq;
	struct i2c_adapter *new_adapter;
	struct i2c_algo_iop3xx_data *adapter_data;

	new_adapter = kzalloc(sizeof(struct i2c_adapter), GFP_KERNEL);
	if (!new_adapter) {
		ret = -ENOMEM;
		goto out;
	}

	adapter_data = kzalloc(sizeof(struct i2c_algo_iop3xx_data), GFP_KERNEL);
	if (!adapter_data) {
		ret = -ENOMEM;
		goto free_adapter;
	}

	adapter_data->gpio_scl = devm_gpiod_get_optional(&pdev->dev,
							 "scl",
							 GPIOD_ASIS);
	if (IS_ERR(adapter_data->gpio_scl))
		return PTR_ERR(adapter_data->gpio_scl);
	adapter_data->gpio_sda = devm_gpiod_get_optional(&pdev->dev,
							 "sda",
							 GPIOD_ASIS);
	if (IS_ERR(adapter_data->gpio_sda))
		return PTR_ERR(adapter_data->gpio_sda);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		ret = -ENODEV;
		goto free_both;
	}

	if (!request_mem_region(res->start, IOP3XX_I2C_IO_SIZE, pdev->name)) {
		ret = -EBUSY;
		goto free_both;
	}

	/* set the adapter enumeration # */
	adapter_data->id = i2c_id++;

	adapter_data->ioaddr = ioremap(res->start, IOP3XX_I2C_IO_SIZE);
	if (!adapter_data->ioaddr) {
		ret = -ENOMEM;
		goto release_region;
	}

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		ret = -ENXIO;
		goto unmap;
	}
	ret = request_irq(irq, iop3xx_i2c_irq_handler, 0,
				pdev->name, adapter_data);

	if (ret) {
		ret = -EIO;
		goto unmap;
	}

	memcpy(new_adapter->name, pdev->name, strlen(pdev->name));
	new_adapter->owner = THIS_MODULE;
	new_adapter->class = I2C_CLASS_HWMON | I2C_CLASS_SPD;
	new_adapter->dev.parent = &pdev->dev;
	new_adapter->dev.of_node = pdev->dev.of_node;
	new_adapter->nr = pdev->id;

	/*
	 * Default values...should these come in from board code?
	 */
	new_adapter->timeout = HZ;
	new_adapter->algo = &iop3xx_i2c_algo;

	init_waitqueue_head(&adapter_data->waitq);
	spin_lock_init(&adapter_data->lock);

	iop3xx_i2c_reset(adapter_data);
	iop3xx_i2c_enable(adapter_data);

	platform_set_drvdata(pdev, new_adapter);
	new_adapter->algo_data = adapter_data;

	i2c_add_numbered_adapter(new_adapter);

	return 0;

unmap:
	iounmap(adapter_data->ioaddr);

release_region:
	release_mem_region(res->start, IOP3XX_I2C_IO_SIZE);

free_both:
	kfree(adapter_data);

free_adapter:
	kfree(new_adapter);

out:
	return ret;
}