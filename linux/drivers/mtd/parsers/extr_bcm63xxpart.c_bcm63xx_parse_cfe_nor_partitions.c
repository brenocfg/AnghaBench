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
struct mtd_partition {char* name; unsigned int offset; unsigned int size; int /*<<< orphan*/  types; } ;
struct mtd_info {unsigned int size; int /*<<< orphan*/  erasesize; } ;
struct bcm963xx_nvram {unsigned int psi_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM963XX_CFE_BLOCK_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int SZ_1K ; 
 int /*<<< orphan*/  bcm63xx_cfe_part_types ; 
 struct mtd_partition* kzalloc (int,int /*<<< orphan*/ ) ; 
 unsigned int max_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int,char*,unsigned int,unsigned int) ; 
 unsigned int roundup (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  uint32_t ; 

__attribute__((used)) static int bcm63xx_parse_cfe_nor_partitions(struct mtd_info *master,
	const struct mtd_partition **pparts, struct bcm963xx_nvram *nvram)
{
	struct mtd_partition *parts;
	int nrparts = 3, curpart = 0;
	unsigned int cfelen, nvramlen;
	unsigned int cfe_erasesize;
	int i;

	cfe_erasesize = max_t(uint32_t, master->erasesize,
			      BCM963XX_CFE_BLOCK_SIZE);

	cfelen = cfe_erasesize;
	nvramlen = nvram->psi_size * SZ_1K;
	nvramlen = roundup(nvramlen, cfe_erasesize);

	parts = kzalloc(sizeof(*parts) * nrparts + 10 * nrparts, GFP_KERNEL);
	if (!parts)
		return -ENOMEM;

	/* Start building partition list */
	parts[curpart].name = "CFE";
	parts[curpart].offset = 0;
	parts[curpart].size = cfelen;
	curpart++;

	parts[curpart].name = "nvram";
	parts[curpart].offset = master->size - nvramlen;
	parts[curpart].size = nvramlen;
	curpart++;

	/* Global partition "linux" to make easy firmware upgrade */
	parts[curpart].name = "linux";
	parts[curpart].offset = cfelen;
	parts[curpart].size = master->size - cfelen - nvramlen;
	parts[curpart].types = bcm63xx_cfe_part_types;

	for (i = 0; i < nrparts; i++)
		pr_info("Partition %d is %s offset %llx and length %llx\n", i,
			parts[i].name, parts[i].offset,	parts[i].size);

	*pparts = parts;

	return nrparts;
}