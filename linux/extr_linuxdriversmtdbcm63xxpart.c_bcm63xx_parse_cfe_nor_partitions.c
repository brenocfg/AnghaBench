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
struct mtd_partition {char* name; unsigned int offset; unsigned int size; } ;
struct mtd_info {unsigned int erasesize; unsigned int size; } ;
struct bcm_tag {int /*<<< orphan*/  total_length; int /*<<< orphan*/  kernel_length; int /*<<< orphan*/  kernel_address; int /*<<< orphan*/  flash_image_start; } ;
struct bcm963xx_nvram {unsigned int psi_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM963XX_CFE_BLOCK_SIZE ; 
 unsigned int BCM963XX_EXTENDED_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  STR_NULL_TERMINATE (int /*<<< orphan*/ ) ; 
 unsigned int SZ_1K ; 
 int bcm63xx_read_image_tag (struct mtd_info*,char*,unsigned int,struct bcm_tag*) ; 
 scalar_t__ kstrtouint (int /*<<< orphan*/ ,int,unsigned int*) ; 
 struct mtd_partition* kzalloc (int,int /*<<< orphan*/ ) ; 
 unsigned int max_t (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int,...) ; 
 unsigned int roundup (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  uint32_t ; 
 int /*<<< orphan*/  vfree (struct bcm_tag*) ; 
 struct bcm_tag* vmalloc (int) ; 

__attribute__((used)) static int bcm63xx_parse_cfe_nor_partitions(struct mtd_info *master,
	const struct mtd_partition **pparts, struct bcm963xx_nvram *nvram)
{
	/* CFE, NVRAM and global Linux are always present */
	int nrparts = 3, curpart = 0;
	struct bcm_tag *buf = NULL;
	struct mtd_partition *parts;
	int ret;
	unsigned int rootfsaddr, kerneladdr, spareaddr;
	unsigned int rootfslen, kernellen, sparelen, totallen;
	unsigned int cfelen, nvramlen;
	unsigned int cfe_erasesize;
	int i;
	bool rootfs_first = false;

	cfe_erasesize = max_t(uint32_t, master->erasesize,
			      BCM963XX_CFE_BLOCK_SIZE);

	cfelen = cfe_erasesize;
	nvramlen = nvram->psi_size * SZ_1K;
	nvramlen = roundup(nvramlen, cfe_erasesize);

	buf = vmalloc(sizeof(struct bcm_tag));
	if (!buf)
		return -ENOMEM;

	/* Get the tag */
	ret = bcm63xx_read_image_tag(master, "rootfs", cfelen, buf);
	if (!ret) {
		STR_NULL_TERMINATE(buf->flash_image_start);
		if (kstrtouint(buf->flash_image_start, 10, &rootfsaddr) ||
				rootfsaddr < BCM963XX_EXTENDED_SIZE) {
			pr_err("invalid rootfs address: %*ph\n",
				(int)sizeof(buf->flash_image_start),
				buf->flash_image_start);
			goto invalid_tag;
		}

		STR_NULL_TERMINATE(buf->kernel_address);
		if (kstrtouint(buf->kernel_address, 10, &kerneladdr) ||
				kerneladdr < BCM963XX_EXTENDED_SIZE) {
			pr_err("invalid kernel address: %*ph\n",
				(int)sizeof(buf->kernel_address),
				buf->kernel_address);
			goto invalid_tag;
		}

		STR_NULL_TERMINATE(buf->kernel_length);
		if (kstrtouint(buf->kernel_length, 10, &kernellen)) {
			pr_err("invalid kernel length: %*ph\n",
				(int)sizeof(buf->kernel_length),
				buf->kernel_length);
			goto invalid_tag;
		}

		STR_NULL_TERMINATE(buf->total_length);
		if (kstrtouint(buf->total_length, 10, &totallen)) {
			pr_err("invalid total length: %*ph\n",
				(int)sizeof(buf->total_length),
				buf->total_length);
			goto invalid_tag;
		}

		kerneladdr = kerneladdr - BCM963XX_EXTENDED_SIZE;
		rootfsaddr = rootfsaddr - BCM963XX_EXTENDED_SIZE;
		spareaddr = roundup(totallen, master->erasesize) + cfelen;

		if (rootfsaddr < kerneladdr) {
			/* default Broadcom layout */
			rootfslen = kerneladdr - rootfsaddr;
			rootfs_first = true;
		} else {
			/* OpenWrt layout */
			rootfsaddr = kerneladdr + kernellen;
			rootfslen = spareaddr - rootfsaddr;
		}
	} else if (ret > 0) {
invalid_tag:
		kernellen = 0;
		rootfslen = 0;
		rootfsaddr = 0;
		spareaddr = cfelen;
	} else {
		goto out;
	}
	sparelen = master->size - spareaddr - nvramlen;

	/* Determine number of partitions */
	if (rootfslen > 0)
		nrparts++;

	if (kernellen > 0)
		nrparts++;

	parts = kzalloc(sizeof(*parts) * nrparts + 10 * nrparts, GFP_KERNEL);
	if (!parts) {
		ret = -ENOMEM;
		goto out;
	}

	/* Start building partition list */
	parts[curpart].name = "CFE";
	parts[curpart].offset = 0;
	parts[curpart].size = cfelen;
	curpart++;

	if (kernellen > 0) {
		int kernelpart = curpart;

		if (rootfslen > 0 && rootfs_first)
			kernelpart++;
		parts[kernelpart].name = "kernel";
		parts[kernelpart].offset = kerneladdr;
		parts[kernelpart].size = kernellen;
		curpart++;
	}

	if (rootfslen > 0) {
		int rootfspart = curpart;

		if (kernellen > 0 && rootfs_first)
			rootfspart--;
		parts[rootfspart].name = "rootfs";
		parts[rootfspart].offset = rootfsaddr;
		parts[rootfspart].size = rootfslen;
		if (sparelen > 0  && !rootfs_first)
			parts[rootfspart].size += sparelen;
		curpart++;
	}

	parts[curpart].name = "nvram";
	parts[curpart].offset = master->size - nvramlen;
	parts[curpart].size = nvramlen;
	curpart++;

	/* Global partition "linux" to make easy firmware upgrade */
	parts[curpart].name = "linux";
	parts[curpart].offset = cfelen;
	parts[curpart].size = master->size - cfelen - nvramlen;

	for (i = 0; i < nrparts; i++)
		pr_info("Partition %d is %s offset %llx and length %llx\n", i,
			parts[i].name, parts[i].offset,	parts[i].size);

	pr_info("Spare partition is offset %x and length %x\n",	spareaddr,
		sparelen);

	*pparts = parts;
	ret = 0;

out:
	vfree(buf);

	if (ret)
		return ret;

	return nrparts;
}