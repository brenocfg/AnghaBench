#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct resource {int start; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; TYPE_1__ dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  devm_request_region (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_add_adapter (TYPE_2__*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 TYPE_2__ sch_adapter ; 
 int sch_smba ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 

__attribute__((used)) static int smbus_sch_probe(struct platform_device *dev)
{
	struct resource *res;
	int retval;

	res = platform_get_resource(dev, IORESOURCE_IO, 0);
	if (!res)
		return -EBUSY;

	if (!devm_request_region(&dev->dev, res->start, resource_size(res),
				 dev->name)) {
		dev_err(&dev->dev, "SMBus region 0x%x already in use!\n",
			sch_smba);
		return -EBUSY;
	}

	sch_smba = res->start;

	dev_dbg(&dev->dev, "SMBA = 0x%X\n", sch_smba);

	/* set up the sysfs linkage to our parent device */
	sch_adapter.dev.parent = &dev->dev;

	snprintf(sch_adapter.name, sizeof(sch_adapter.name),
		"SMBus SCH adapter at %04x", sch_smba);

	retval = i2c_add_adapter(&sch_adapter);
	if (retval)
		sch_smba = 0;

	return retval;
}