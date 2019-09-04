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
struct TYPE_2__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mtd_info {int dummy; } ;
struct map_info {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (char**) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*,...) ; 
 struct mtd_info* do_map_probe (char*,struct map_info*) ; 
 char* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 char** rom_probe_types ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static struct mtd_info *obsolete_probe(struct platform_device *dev,
				       struct map_info *map)
{
	struct device_node *dp = dev->dev.of_node;
	const char *of_probe;
	struct mtd_info *mtd;
	int i;

	dev_warn(&dev->dev, "Device tree uses obsolete \"direct-mapped\" "
		 "flash binding\n");

	of_probe = of_get_property(dp, "probe-type", NULL);
	if (!of_probe) {
		for (i = 0; i < ARRAY_SIZE(rom_probe_types); i++) {
			mtd = do_map_probe(rom_probe_types[i], map);
			if (mtd)
				return mtd;
		}
		return NULL;
	} else if (strcmp(of_probe, "CFI") == 0) {
		return do_map_probe("cfi_probe", map);
	} else if (strcmp(of_probe, "JEDEC") == 0) {
		return do_map_probe("jedec_probe", map);
	} else {
		if (strcmp(of_probe, "ROM") != 0)
			dev_warn(&dev->dev, "obsolete_probe: don't know probe "
				 "type '%s', mapping as rom\n", of_probe);
		return do_map_probe("map_rom", map);
	}
}