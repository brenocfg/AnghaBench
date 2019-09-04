#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_8__ {unsigned long size; int /*<<< orphan*/  virt; int /*<<< orphan*/  phys; int /*<<< orphan*/  bankwidth; int /*<<< orphan*/  name; } ;
struct rbtx4939_flash_info {TYPE_4__* mtd; TYPE_2__ map; } ;
struct rbtx4939_flash_data {int /*<<< orphan*/  nr_parts; int /*<<< orphan*/  parts; int /*<<< orphan*/  (* map_init ) (TYPE_2__*) ;int /*<<< orphan*/  width; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_9__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct rbtx4939_flash_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 struct rbtx4939_flash_info* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_request_mem_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 TYPE_4__* do_map_probe (char const* const,TYPE_2__*) ; 
 int mtd_device_register (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rbtx4939_flash_info*) ; 
 int /*<<< orphan*/  pr_notice (char*,struct resource*) ; 
 int /*<<< orphan*/  rbtx4939_flash_remove (struct platform_device*) ; 
 unsigned long resource_size (struct resource*) ; 
 char** rom_probe_types ; 
 int /*<<< orphan*/  simple_map_init (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static int rbtx4939_flash_probe(struct platform_device *dev)
{
	struct rbtx4939_flash_data *pdata;
	struct rbtx4939_flash_info *info;
	struct resource *res;
	const char * const *probe_type;
	int err = 0;
	unsigned long size;

	pdata = dev_get_platdata(&dev->dev);
	if (!pdata)
		return -ENODEV;

	res = platform_get_resource(dev, IORESOURCE_MEM, 0);
	if (!res)
		return -ENODEV;
	info = devm_kzalloc(&dev->dev, sizeof(struct rbtx4939_flash_info),
			    GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	platform_set_drvdata(dev, info);

	size = resource_size(res);
	pr_notice("rbtx4939 platform flash device: %pR\n", res);

	if (!devm_request_mem_region(&dev->dev, res->start, size,
				     dev_name(&dev->dev)))
		return -EBUSY;

	info->map.name = dev_name(&dev->dev);
	info->map.phys = res->start;
	info->map.size = size;
	info->map.bankwidth = pdata->width;

	info->map.virt = devm_ioremap(&dev->dev, info->map.phys, size);
	if (!info->map.virt)
		return -EBUSY;

	if (pdata->map_init)
		(*pdata->map_init)(&info->map);
	else
		simple_map_init(&info->map);

	probe_type = rom_probe_types;
	for (; !info->mtd && *probe_type; probe_type++)
		info->mtd = do_map_probe(*probe_type, &info->map);
	if (!info->mtd) {
		dev_err(&dev->dev, "map_probe failed\n");
		err = -ENXIO;
		goto err_out;
	}
	info->mtd->dev.parent = &dev->dev;
	err = mtd_device_register(info->mtd, pdata->parts, pdata->nr_parts);

	if (err)
		goto err_out;
	return 0;

err_out:
	rbtx4939_flash_remove(dev);
	return err;
}