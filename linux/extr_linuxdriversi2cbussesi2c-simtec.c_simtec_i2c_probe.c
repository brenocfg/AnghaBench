#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; TYPE_1__ dev; TYPE_2__* algo_data; int /*<<< orphan*/  owner; } ;
struct TYPE_6__ {int udelay; int /*<<< orphan*/  timeout; int /*<<< orphan*/  getscl; int /*<<< orphan*/  getsda; int /*<<< orphan*/  setscl; int /*<<< orphan*/  setsda; struct simtec_i2c_data* data; } ;
struct simtec_i2c_data {TYPE_3__* ioarea; int /*<<< orphan*/ * reg; TYPE_4__ adap; TYPE_2__ bit; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_bit_add_bus (TYPE_4__*) ; 
 int /*<<< orphan*/ * ioremap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct simtec_i2c_data*) ; 
 struct simtec_i2c_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct simtec_i2c_data*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int) ; 
 TYPE_3__* request_mem_region (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int resource_size (struct resource*) ; 
 int /*<<< orphan*/  simtec_i2c_getscl ; 
 int /*<<< orphan*/  simtec_i2c_getsda ; 
 int /*<<< orphan*/  simtec_i2c_setscl ; 
 int /*<<< orphan*/  simtec_i2c_setsda ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int simtec_i2c_probe(struct platform_device *dev)
{
	struct simtec_i2c_data *pd;
	struct resource *res;
	int size;
	int ret;

	pd = kzalloc(sizeof(struct simtec_i2c_data), GFP_KERNEL);
	if (pd == NULL)
		return -ENOMEM;

	platform_set_drvdata(dev, pd);

	res = platform_get_resource(dev, IORESOURCE_MEM, 0);
	if (res == NULL) {
		dev_err(&dev->dev, "cannot find IO resource\n");
		ret = -ENOENT;
		goto err;
	}

	size = resource_size(res);

	pd->ioarea = request_mem_region(res->start, size, dev->name);
	if (pd->ioarea == NULL) {
		dev_err(&dev->dev, "cannot request IO\n");
		ret = -ENXIO;
		goto err;
	}

	pd->reg = ioremap(res->start, size);
	if (pd->reg == NULL) {
		dev_err(&dev->dev, "cannot map IO\n");
		ret = -ENXIO;
		goto err_res;
	}

	/* setup the private data */

	pd->adap.owner = THIS_MODULE;
	pd->adap.algo_data = &pd->bit;
	pd->adap.dev.parent = &dev->dev;

	strlcpy(pd->adap.name, "Simtec I2C", sizeof(pd->adap.name));

	pd->bit.data = pd;
	pd->bit.setsda = simtec_i2c_setsda;
	pd->bit.setscl = simtec_i2c_setscl;
	pd->bit.getsda = simtec_i2c_getsda;
	pd->bit.getscl = simtec_i2c_getscl;
	pd->bit.timeout = HZ;
	pd->bit.udelay = 20;

	ret = i2c_bit_add_bus(&pd->adap);
	if (ret)
		goto err_all;

	return 0;

 err_all:
	iounmap(pd->reg);

 err_res:
	release_mem_region(pd->ioarea->start, size);

 err:
	kfree(pd);
	return ret;
}