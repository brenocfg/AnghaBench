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
struct resource {int start; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct i2c_adapter {int /*<<< orphan*/  nr; TYPE_1__ dev; int /*<<< orphan*/  class; int /*<<< orphan*/ * algo; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_CLASS_HWMON ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int i2c_add_numbered_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  kfree (struct i2c_adapter*) ; 
 struct i2c_adapter* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct i2c_adapter*) ; 
 int /*<<< orphan*/  puv3_i2c_algorithm ; 
 int /*<<< orphan*/  release_mem_region (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_mem_region (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 

__attribute__((used)) static int puv3_i2c_probe(struct platform_device *pdev)
{
	struct i2c_adapter *adapter;
	struct resource *mem;
	int rc;

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!mem)
		return -ENODEV;

	if (!request_mem_region(mem->start, resource_size(mem), "puv3_i2c"))
		return -EBUSY;

	adapter = kzalloc(sizeof(struct i2c_adapter), GFP_KERNEL);
	if (adapter == NULL) {
		dev_err(&pdev->dev, "can't allocate interface!\n");
		rc = -ENOMEM;
		goto fail_nomem;
	}
	snprintf(adapter->name, sizeof(adapter->name), "PUV3-I2C at 0x%08x",
			mem->start);
	adapter->algo = &puv3_i2c_algorithm;
	adapter->class = I2C_CLASS_HWMON;
	adapter->dev.parent = &pdev->dev;

	platform_set_drvdata(pdev, adapter);

	adapter->nr = pdev->id;
	rc = i2c_add_numbered_adapter(adapter);
	if (rc)
		goto fail_add_adapter;

	dev_info(&pdev->dev, "PKUnity v3 i2c bus adapter.\n");
	return 0;

fail_add_adapter:
	kfree(adapter);
fail_nomem:
	release_mem_region(mem->start, resource_size(mem));

	return rc;
}