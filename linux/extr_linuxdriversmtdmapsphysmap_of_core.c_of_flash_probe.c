#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_18__ {struct device_node* of_node; } ;
struct platform_device {TYPE_4__ dev; } ;
struct of_flash_list {int dummy; } ;
struct of_flash {int list_size; struct mtd_info* cmtd; TYPE_2__* list; } ;
struct of_device_id {char* data; } ;
struct TYPE_15__ {TYPE_4__* parent; } ;
struct mtd_info {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  resource_size_t ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_17__ {int /*<<< orphan*/  phys; int /*<<< orphan*/  virt; int /*<<< orphan*/  size; int /*<<< orphan*/  swap; struct device_node* device_node; int /*<<< orphan*/  bankwidth; int /*<<< orphan*/  name; } ;
struct TYPE_16__ {struct mtd_info* mtd; TYPE_3__ map; int /*<<< orphan*/  res; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFI_BIG_ENDIAN ; 
 int /*<<< orphan*/  CFI_LITTLE_ENDIAN ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NO_XIP ; 
 int /*<<< orphan*/  be32_to_cpup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_4__*,char*,struct resource*) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  dev_name (TYPE_4__*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_4__*,struct of_flash*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_4__*,char*,char const*) ; 
 struct of_flash* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 void* do_map_probe (char const*,TYPE_3__*) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mtd_info** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mtd_info**) ; 
 struct mtd_info* mtd_concat_create (struct mtd_info**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtd_device_parse_register (struct mtd_info*,char const* const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtd_set_of_node (struct mtd_info*,struct device_node*) ; 
 struct mtd_info* obsolete_probe (struct platform_device*,TYPE_3__*) ; 
 scalar_t__ of_address_to_resource (struct device_node*,int,struct resource*) ; 
 int /*<<< orphan*/  of_flash_match ; 
 int of_flash_probe_gemini (struct platform_device*,struct device_node*,TYPE_3__*) ; 
 int of_flash_probe_versatile (struct platform_device*,struct device_node*,TYPE_3__*) ; 
 int /*<<< orphan*/  of_flash_remove (struct platform_device*) ; 
 int /*<<< orphan*/  of_free_probes (char const* const*) ; 
 char** of_get_probes (struct device_node*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int of_n_addr_cells (struct device_node*) ; 
 int of_n_size_cells (struct device_node*) ; 
 int of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_property_read_string (struct device_node*,char*,char const**) ; 
 int /*<<< orphan*/  request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  simple_map_init (TYPE_3__*) ; 

__attribute__((used)) static int of_flash_probe(struct platform_device *dev)
{
	const char * const *part_probe_types;
	const struct of_device_id *match;
	struct device_node *dp = dev->dev.of_node;
	struct resource res;
	struct of_flash *info;
	const char *probe_type;
	const __be32 *width;
	int err;
	int i;
	int count;
	const __be32 *p;
	int reg_tuple_size;
	struct mtd_info **mtd_list = NULL;
	resource_size_t res_size;
	bool map_indirect;
	const char *mtd_name = NULL;

	match = of_match_device(of_flash_match, &dev->dev);
	if (!match)
		return -EINVAL;
	probe_type = match->data;

	reg_tuple_size = (of_n_addr_cells(dp) + of_n_size_cells(dp)) * sizeof(u32);

	of_property_read_string(dp, "linux,mtd-name", &mtd_name);

	/*
	 * Get number of "reg" tuples. Scan for MTD devices on area's
	 * described by each "reg" region. This makes it possible (including
	 * the concat support) to support the Intel P30 48F4400 chips which
	 * consists internally of 2 non-identical NOR chips on one die.
	 */
	p = of_get_property(dp, "reg", &count);
	if (!p || count % reg_tuple_size != 0) {
		dev_err(&dev->dev, "Malformed reg property on %pOF\n",
				dev->dev.of_node);
		err = -EINVAL;
		goto err_flash_remove;
	}
	count /= reg_tuple_size;

	map_indirect = of_property_read_bool(dp, "no-unaligned-direct-access");

	err = -ENOMEM;
	info = devm_kzalloc(&dev->dev,
			    sizeof(struct of_flash) +
			    sizeof(struct of_flash_list) * count, GFP_KERNEL);
	if (!info)
		goto err_flash_remove;

	dev_set_drvdata(&dev->dev, info);

	mtd_list = kcalloc(count, sizeof(*mtd_list), GFP_KERNEL);
	if (!mtd_list)
		goto err_flash_remove;

	for (i = 0; i < count; i++) {
		err = -ENXIO;
		if (of_address_to_resource(dp, i, &res)) {
			/*
			 * Continue with next register tuple if this
			 * one is not mappable
			 */
			continue;
		}

		dev_dbg(&dev->dev, "of_flash device: %pR\n", &res);

		err = -EBUSY;
		res_size = resource_size(&res);
		info->list[i].res = request_mem_region(res.start, res_size,
						       dev_name(&dev->dev));
		if (!info->list[i].res)
			goto err_out;

		err = -ENXIO;
		width = of_get_property(dp, "bank-width", NULL);
		if (!width) {
			dev_err(&dev->dev, "Can't get bank width from device"
				" tree\n");
			goto err_out;
		}

		info->list[i].map.name = mtd_name ?: dev_name(&dev->dev);
		info->list[i].map.phys = res.start;
		info->list[i].map.size = res_size;
		info->list[i].map.bankwidth = be32_to_cpup(width);
		info->list[i].map.device_node = dp;

		if (of_property_read_bool(dp, "big-endian"))
			info->list[i].map.swap = CFI_BIG_ENDIAN;
		else if (of_property_read_bool(dp, "little-endian"))
			info->list[i].map.swap = CFI_LITTLE_ENDIAN;

		err = of_flash_probe_gemini(dev, dp, &info->list[i].map);
		if (err)
			goto err_out;
		err = of_flash_probe_versatile(dev, dp, &info->list[i].map);
		if (err)
			goto err_out;

		err = -ENOMEM;
		info->list[i].map.virt = ioremap(info->list[i].map.phys,
						 info->list[i].map.size);
		if (!info->list[i].map.virt) {
			dev_err(&dev->dev, "Failed to ioremap() flash"
				" region\n");
			goto err_out;
		}

		simple_map_init(&info->list[i].map);

		/*
		 * On some platforms (e.g. MPC5200) a direct 1:1 mapping
		 * may cause problems with JFFS2 usage, as the local bus (LPB)
		 * doesn't support unaligned accesses as implemented in the
		 * JFFS2 code via memcpy(). By setting NO_XIP, the
		 * flash will not be exposed directly to the MTD users
		 * (e.g. JFFS2) any more.
		 */
		if (map_indirect)
			info->list[i].map.phys = NO_XIP;

		if (probe_type) {
			info->list[i].mtd = do_map_probe(probe_type,
							 &info->list[i].map);
		} else {
			info->list[i].mtd = obsolete_probe(dev,
							   &info->list[i].map);
		}

		/* Fall back to mapping region as ROM */
		if (!info->list[i].mtd) {
			dev_warn(&dev->dev,
				"do_map_probe() failed for type %s\n",
				 probe_type);

			info->list[i].mtd = do_map_probe("map_rom",
							 &info->list[i].map);
		}
		mtd_list[i] = info->list[i].mtd;

		err = -ENXIO;
		if (!info->list[i].mtd) {
			dev_err(&dev->dev, "do_map_probe() failed\n");
			goto err_out;
		} else {
			info->list_size++;
		}
		info->list[i].mtd->dev.parent = &dev->dev;
	}

	err = 0;
	info->cmtd = NULL;
	if (info->list_size == 1) {
		info->cmtd = info->list[0].mtd;
	} else if (info->list_size > 1) {
		/*
		 * We detected multiple devices. Concatenate them together.
		 */
		info->cmtd = mtd_concat_create(mtd_list, info->list_size,
					       dev_name(&dev->dev));
	}
	if (info->cmtd == NULL)
		err = -ENXIO;

	if (err)
		goto err_out;

	info->cmtd->dev.parent = &dev->dev;
	mtd_set_of_node(info->cmtd, dp);
	part_probe_types = of_get_probes(dp);
	if (!part_probe_types) {
		err = -ENOMEM;
		goto err_out;
	}
	mtd_device_parse_register(info->cmtd, part_probe_types, NULL,
			NULL, 0);
	of_free_probes(part_probe_types);

	kfree(mtd_list);

	return 0;

err_out:
	kfree(mtd_list);
err_flash_remove:
	of_flash_remove(dev);

	return err;
}