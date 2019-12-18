#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sm501_devdata {int irq; struct sm501_devdata* regs_claim; int /*<<< orphan*/  regs; TYPE_1__* io_res; void* mem_res; int /*<<< orphan*/  platdata; int /*<<< orphan*/  pdev_id; int /*<<< orphan*/ * dev; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sm501_devdata*) ; 
 struct sm501_devdata* kzalloc (int,int /*<<< orphan*/ ) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 void* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sm501_devdata*) ; 
 int /*<<< orphan*/  release_resource (struct sm501_devdata*) ; 
 struct sm501_devdata* request_mem_region (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  resource_size (TYPE_1__*) ; 
 int sm501_init_dev (struct sm501_devdata*) ; 

__attribute__((used)) static int sm501_plat_probe(struct platform_device *dev)
{
	struct sm501_devdata *sm;
	int ret;

	sm = kzalloc(sizeof(*sm), GFP_KERNEL);
	if (!sm) {
		ret = -ENOMEM;
		goto err1;
	}

	sm->dev = &dev->dev;
	sm->pdev_id = dev->id;
	sm->platdata = dev_get_platdata(&dev->dev);

	ret = platform_get_irq(dev, 0);
	if (ret < 0)
		goto err_res;
	sm->irq = ret;

	sm->io_res = platform_get_resource(dev, IORESOURCE_MEM, 1);
	sm->mem_res = platform_get_resource(dev, IORESOURCE_MEM, 0);
	if (!sm->io_res || !sm->mem_res) {
		dev_err(&dev->dev, "failed to get IO resource\n");
		ret = -ENOENT;
		goto err_res;
	}

	sm->regs_claim = request_mem_region(sm->io_res->start,
					    0x100, "sm501");
	if (!sm->regs_claim) {
		dev_err(&dev->dev, "cannot claim registers\n");
		ret = -EBUSY;
		goto err_res;
	}

	platform_set_drvdata(dev, sm);

	sm->regs = ioremap(sm->io_res->start, resource_size(sm->io_res));
	if (!sm->regs) {
		dev_err(&dev->dev, "cannot remap registers\n");
		ret = -EIO;
		goto err_claim;
	}

	return sm501_init_dev(sm);

 err_claim:
	release_resource(sm->regs_claim);
	kfree(sm->regs_claim);
 err_res:
	kfree(sm);
 err1:
	return ret;

}