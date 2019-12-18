#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mtd_partition {int dummy; } ;
struct mtd_part_parser_data {int dummy; } ;
struct mtd_info {int dummy; } ;
struct bcm963xx_nvram {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ bcm63xx_detect_cfe (struct mtd_info*) ; 
 int bcm63xx_parse_cfe_nor_partitions (struct mtd_info*,struct mtd_partition const**,struct bcm963xx_nvram*) ; 
 int bcm63xx_read_nvram (struct mtd_info*,struct bcm963xx_nvram*) ; 
 int /*<<< orphan*/  mtd_type_is_nand (struct mtd_info*) ; 
 int /*<<< orphan*/  vfree (struct bcm963xx_nvram*) ; 
 struct bcm963xx_nvram* vzalloc (int) ; 

__attribute__((used)) static int bcm63xx_parse_cfe_partitions(struct mtd_info *master,
					const struct mtd_partition **pparts,
					struct mtd_part_parser_data *data)
{
	struct bcm963xx_nvram *nvram = NULL;
	int ret;

	if (bcm63xx_detect_cfe(master))
		return -EINVAL;

	nvram = vzalloc(sizeof(*nvram));
	if (!nvram)
		return -ENOMEM;

	ret = bcm63xx_read_nvram(master, nvram);
	if (ret)
		goto out;

	if (!mtd_type_is_nand(master))
		ret = bcm63xx_parse_cfe_nor_partitions(master, pparts, nvram);
	else
		ret = -EINVAL;

out:
	vfree(nvram);
	return ret;
}