#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_6__ {int /*<<< orphan*/ * parent; } ;
struct men_z069_drv {TYPE_1__ wdt; struct resource* mem; int /*<<< orphan*/ * base; } ;
struct mcb_device_id {int dummy; } ;
struct mcb_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct resource*) ; 
 int PTR_ERR (struct resource*) ; 
 int /*<<< orphan*/ * devm_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct men_z069_drv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcb_release_mem (struct resource*) ; 
 struct resource* mcb_request_mem (struct mcb_device*,char*) ; 
 int /*<<< orphan*/  mcb_set_drvdata (struct mcb_device*,struct men_z069_drv*) ; 
 TYPE_1__ men_z069_wdt ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  watchdog_init_timeout (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int watchdog_register_device (TYPE_1__*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (TYPE_1__*,struct men_z069_drv*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int men_z069_probe(struct mcb_device *dev,
			  const struct mcb_device_id *id)
{
	struct men_z069_drv *drv;
	struct resource *mem;

	drv = devm_kzalloc(&dev->dev, sizeof(struct men_z069_drv), GFP_KERNEL);
	if (!drv)
		return -ENOMEM;

	mem = mcb_request_mem(dev, "z069-wdt");
	if (IS_ERR(mem))
		return PTR_ERR(mem);

	drv->base = devm_ioremap(&dev->dev, mem->start, resource_size(mem));
	if (drv->base == NULL)
		goto release_mem;

	drv->mem = mem;

	drv->wdt = men_z069_wdt;
	watchdog_init_timeout(&drv->wdt, 0, &dev->dev);
	watchdog_set_nowayout(&drv->wdt, nowayout);
	watchdog_set_drvdata(&drv->wdt, drv);
	drv->wdt.parent = &dev->dev;
	mcb_set_drvdata(dev, drv);

	return watchdog_register_device(&men_z069_wdt);

release_mem:
	mcb_release_mem(mem);
	return -ENOMEM;
}