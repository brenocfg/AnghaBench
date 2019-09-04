#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct powernv_flash* priv; } ;
struct powernv_flash {TYPE_1__ mtd; int /*<<< orphan*/  id; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct powernv_flash*) ; 
 struct powernv_flash* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int mtd_device_register (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int powernv_flash_set_driver_info (struct device*,TYPE_1__*) ; 

__attribute__((used)) static int powernv_flash_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct powernv_flash *data;
	int ret;

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->mtd.priv = data;

	ret = of_property_read_u32(dev->of_node, "ibm,opal-id", &(data->id));
	if (ret) {
		dev_err(dev, "no device property 'ibm,opal-id'\n");
		return ret;
	}

	ret = powernv_flash_set_driver_info(dev, &data->mtd);
	if (ret)
		return ret;

	dev_set_drvdata(dev, data);

	/*
	 * The current flash that skiboot exposes is one contiguous flash chip
	 * with an ffs partition at the start, it should prove easier for users
	 * to deal with partitions or not as they see fit
	 */
	return mtd_device_register(&data->mtd, NULL, 0);
}