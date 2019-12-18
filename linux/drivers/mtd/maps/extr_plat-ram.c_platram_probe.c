#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct resource {scalar_t__ start; } ;
struct TYPE_7__ {char* name; int /*<<< orphan*/  size; int /*<<< orphan*/  virt; int /*<<< orphan*/  bankwidth; scalar_t__ phys; } ;
struct platram_info {TYPE_3__* mtd; TYPE_2__ map; struct platdata_mtd_ram* pdata; int /*<<< orphan*/ * dev; } ;
struct platform_device {int /*<<< orphan*/  dev; scalar_t__ name; } ;
struct platdata_mtd_ram {char** map_probes; scalar_t__ nr_partitions; int /*<<< orphan*/  partitions; int /*<<< orphan*/  probes; int /*<<< orphan*/  bankwidth; int /*<<< orphan*/ * mapname; } ;
struct TYPE_6__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_8__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLATRAM_RW ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct platdata_mtd_ram* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 void* do_map_probe (char const* const,TYPE_2__*) ; 
 struct platram_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mtd_device_parse_register (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int mtd_device_register (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct platram_info*) ; 
 int /*<<< orphan*/  platram_remove (struct platform_device*) ; 
 int /*<<< orphan*/  platram_setrw (struct platram_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  simple_map_init (TYPE_2__*) ; 

__attribute__((used)) static int platram_probe(struct platform_device *pdev)
{
	struct platdata_mtd_ram	*pdata;
	struct platram_info *info;
	struct resource *res;
	int err = 0;

	dev_dbg(&pdev->dev, "probe entered\n");

	if (dev_get_platdata(&pdev->dev) == NULL) {
		dev_err(&pdev->dev, "no platform data supplied\n");
		err = -ENOENT;
		goto exit_error;
	}

	pdata = dev_get_platdata(&pdev->dev);

	info = kzalloc(sizeof(*info), GFP_KERNEL);
	if (info == NULL) {
		err = -ENOMEM;
		goto exit_error;
	}

	platform_set_drvdata(pdev, info);

	info->dev = &pdev->dev;
	info->pdata = pdata;

	/* get the resource for the memory mapping */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	info->map.virt = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(info->map.virt)) {
		err = PTR_ERR(info->map.virt);
		dev_err(&pdev->dev, "failed to ioremap() region\n");
		goto exit_free;
	}

	dev_dbg(&pdev->dev, "got platform resource %p (0x%llx)\n", res,
		(unsigned long long)res->start);

	/* setup map parameters */

	info->map.phys = res->start;
	info->map.size = resource_size(res);
	info->map.name = pdata->mapname != NULL ?
			(char *)pdata->mapname : (char *)pdev->name;
	info->map.bankwidth = pdata->bankwidth;

	dev_dbg(&pdev->dev, "virt %p, %lu bytes\n", info->map.virt, info->map.size);

	simple_map_init(&info->map);

	dev_dbg(&pdev->dev, "initialised map, probing for mtd\n");

	/* probe for the right mtd map driver
	 * supplied by the platform_data struct */

	if (pdata->map_probes) {
		const char * const *map_probes = pdata->map_probes;

		for ( ; !info->mtd && *map_probes; map_probes++)
			info->mtd = do_map_probe(*map_probes , &info->map);
	}
	/* fallback to map_ram */
	else
		info->mtd = do_map_probe("map_ram", &info->map);

	if (info->mtd == NULL) {
		dev_err(&pdev->dev, "failed to probe for map_ram\n");
		err = -ENOMEM;
		goto exit_free;
	}

	info->mtd->dev.parent = &pdev->dev;

	platram_setrw(info, PLATRAM_RW);

	/* check to see if there are any available partitions, or whether
	 * to add this device whole */

	err = mtd_device_parse_register(info->mtd, pdata->probes, NULL,
					pdata->partitions,
					pdata->nr_partitions);
	if (!err)
		dev_info(&pdev->dev, "registered mtd device\n");

	if (pdata->nr_partitions) {
		/* add the whole device. */
		err = mtd_device_register(info->mtd, NULL, 0);
		if (err) {
			dev_err(&pdev->dev,
				"failed to register the entire device\n");
		}
	}

	return err;

 exit_free:
	platram_remove(pdev);
 exit_error:
	return err;
}