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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct c67x00_platform_data {int /*<<< orphan*/  hpi_regstep; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; int /*<<< orphan*/  regstep; int /*<<< orphan*/  lock; } ;
struct c67x00_device {TYPE_1__ hpi; int /*<<< orphan*/ * sie; struct platform_device* pdev; void* pdata; } ;

/* Variables and functions */
 int C67X00_SIES ; 
 int EBUSY ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  c67x00_irq ; 
 int /*<<< orphan*/  c67x00_ll_hpi_reg_init (struct c67x00_device*) ; 
 int /*<<< orphan*/  c67x00_ll_init (struct c67x00_device*) ; 
 int c67x00_ll_reset (struct c67x00_device*) ; 
 int /*<<< orphan*/  c67x00_probe_sie (int /*<<< orphan*/ *,struct c67x00_device*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 void* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct c67x00_device*) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct c67x00_device*) ; 
 struct c67x00_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct c67x00_device*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct c67x00_device*) ; 
 int /*<<< orphan*/  request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int c67x00_drv_probe(struct platform_device *pdev)
{
	struct c67x00_device *c67x00;
	struct c67x00_platform_data *pdata;
	struct resource *res, *res2;
	int ret, i;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -ENODEV;

	res2 = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!res2)
		return -ENODEV;

	pdata = dev_get_platdata(&pdev->dev);
	if (!pdata)
		return -ENODEV;

	c67x00 = kzalloc(sizeof(*c67x00), GFP_KERNEL);
	if (!c67x00)
		return -ENOMEM;

	if (!request_mem_region(res->start, resource_size(res),
				pdev->name)) {
		dev_err(&pdev->dev, "Memory region busy\n");
		ret = -EBUSY;
		goto request_mem_failed;
	}
	c67x00->hpi.base = ioremap(res->start, resource_size(res));
	if (!c67x00->hpi.base) {
		dev_err(&pdev->dev, "Unable to map HPI registers\n");
		ret = -EIO;
		goto map_failed;
	}

	spin_lock_init(&c67x00->hpi.lock);
	c67x00->hpi.regstep = pdata->hpi_regstep;
	c67x00->pdata = dev_get_platdata(&pdev->dev);
	c67x00->pdev = pdev;

	c67x00_ll_init(c67x00);
	c67x00_ll_hpi_reg_init(c67x00);

	ret = request_irq(res2->start, c67x00_irq, 0, pdev->name, c67x00);
	if (ret) {
		dev_err(&pdev->dev, "Cannot claim IRQ\n");
		goto request_irq_failed;
	}

	ret = c67x00_ll_reset(c67x00);
	if (ret) {
		dev_err(&pdev->dev, "Device reset failed\n");
		goto reset_failed;
	}

	for (i = 0; i < C67X00_SIES; i++)
		c67x00_probe_sie(&c67x00->sie[i], c67x00, i);

	platform_set_drvdata(pdev, c67x00);

	return 0;

 reset_failed:
	free_irq(res2->start, c67x00);
 request_irq_failed:
	iounmap(c67x00->hpi.base);
 map_failed:
	release_mem_region(res->start, resource_size(res));
 request_mem_failed:
	kfree(c67x00);

	return ret;
}