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
struct sh7760_i2c_platdata {int speed_khz; } ;
struct resource {scalar_t__ start; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_4__ {int class; int retries; int /*<<< orphan*/  name; TYPE_1__ dev; struct cami2c* algo_data; int /*<<< orphan*/ * algo; int /*<<< orphan*/  nr; } ;
struct cami2c {int irq; struct cami2c* ioarea; int /*<<< orphan*/  iobase; TYPE_2__ adap; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int FCR_RFRST ; 
 int FCR_TFRST ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2CCCR ; 
 int /*<<< orphan*/  I2CFCR ; 
 int /*<<< orphan*/  I2CFIER ; 
 int /*<<< orphan*/  I2CFSR ; 
 int /*<<< orphan*/  I2CMAR ; 
 int /*<<< orphan*/  I2CMCR ; 
 int /*<<< orphan*/  I2CMIER ; 
 int /*<<< orphan*/  I2CMSR ; 
 int /*<<< orphan*/  I2CSAR ; 
 int /*<<< orphan*/  I2CSCR ; 
 int /*<<< orphan*/  I2CSIER ; 
 int /*<<< orphan*/  I2CSSR ; 
 int I2C_CLASS_HWMON ; 
 int I2C_CLASS_SPD ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  OUT32 (struct cami2c*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REGSIZE ; 
 int /*<<< orphan*/  SH7760_I2C_DEVNAME ; 
 int calc_CCR (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct sh7760_i2c_platdata* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,scalar_t__,int) ; 
 int /*<<< orphan*/  free_irq (int,struct cami2c*) ; 
 int i2c_add_numbered_adapter (TYPE_2__*) ; 
 int /*<<< orphan*/  ioremap (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cami2c*) ; 
 struct cami2c* kzalloc (int,int /*<<< orphan*/ ) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct cami2c*) ; 
 int /*<<< orphan*/  release_resource (struct cami2c*) ; 
 scalar_t__ request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cami2c*) ; 
 struct cami2c* request_mem_region (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh7760_i2c_algo ; 
 int /*<<< orphan*/  sh7760_i2c_irq ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,unsigned long) ; 

__attribute__((used)) static int sh7760_i2c_probe(struct platform_device *pdev)
{
	struct sh7760_i2c_platdata *pd;
	struct resource *res;
	struct cami2c *id;
	int ret;

	pd = dev_get_platdata(&pdev->dev);
	if (!pd) {
		dev_err(&pdev->dev, "no platform_data!\n");
		ret = -ENODEV;
		goto out0;
	}

	id = kzalloc(sizeof(struct cami2c), GFP_KERNEL);
	if (!id) {
		dev_err(&pdev->dev, "no mem for private data\n");
		ret = -ENOMEM;
		goto out0;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&pdev->dev, "no mmio resources\n");
		ret = -ENODEV;
		goto out1;
	}

	id->ioarea = request_mem_region(res->start, REGSIZE, pdev->name);
	if (!id->ioarea) {
		dev_err(&pdev->dev, "mmio already reserved\n");
		ret = -EBUSY;
		goto out1;
	}

	id->iobase = ioremap(res->start, REGSIZE);
	if (!id->iobase) {
		dev_err(&pdev->dev, "cannot ioremap\n");
		ret = -ENODEV;
		goto out2;
	}

	id->irq = platform_get_irq(pdev, 0);

	id->adap.nr = pdev->id;
	id->adap.algo = &sh7760_i2c_algo;
	id->adap.class = I2C_CLASS_HWMON | I2C_CLASS_SPD;
	id->adap.retries = 3;
	id->adap.algo_data = id;
	id->adap.dev.parent = &pdev->dev;
	snprintf(id->adap.name, sizeof(id->adap.name),
		"SH7760 I2C at %08lx", (unsigned long)res->start);

	OUT32(id, I2CMCR, 0);
	OUT32(id, I2CMSR, 0);
	OUT32(id, I2CMIER, 0);
	OUT32(id, I2CMAR, 0);
	OUT32(id, I2CSIER, 0);
	OUT32(id, I2CSAR, 0);
	OUT32(id, I2CSCR, 0);
	OUT32(id, I2CSSR, 0);
	OUT32(id, I2CFIER, 0);
	OUT32(id, I2CFCR, FCR_RFRST | FCR_TFRST);
	OUT32(id, I2CFSR, 0);

	ret = calc_CCR(pd->speed_khz * 1000);
	if (ret < 0) {
		dev_err(&pdev->dev, "invalid SCL clock: %dkHz\n",
			pd->speed_khz);
		goto out3;
	}
	OUT32(id, I2CCCR, ret);

	if (request_irq(id->irq, sh7760_i2c_irq, 0,
			SH7760_I2C_DEVNAME, id)) {
		dev_err(&pdev->dev, "cannot get irq %d\n", id->irq);
		ret = -EBUSY;
		goto out3;
	}

	ret = i2c_add_numbered_adapter(&id->adap);
	if (ret < 0)
		goto out4;

	platform_set_drvdata(pdev, id);

	dev_info(&pdev->dev, "%d kHz mmio %08x irq %d\n",
		 pd->speed_khz, res->start, id->irq);

	return 0;

out4:
	free_irq(id->irq, id);
out3:
	iounmap(id->iobase);
out2:
	release_resource(id->ioarea);
	kfree(id->ioarea);
out1:
	kfree(id);
out0:
	return ret;
}