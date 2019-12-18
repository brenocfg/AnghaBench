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
struct mtd_part_parser_data {int dummy; } ;
struct mtd_info {unsigned int size; int /*<<< orphan*/  erasesize; } ;
struct bcm_tag {int /*<<< orphan*/  total_length; int /*<<< orphan*/  kernel_length; int /*<<< orphan*/  kernel_address; int /*<<< orphan*/  flash_image_start; } ;

/* Variables and functions */
 unsigned int BCM963XX_EXTENDED_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  STR_NULL_TERMINATE (int /*<<< orphan*/ ) ; 
 int bcm963xx_read_imagetag (struct mtd_info*,char*,int /*<<< orphan*/ ,struct bcm_tag*) ; 
 scalar_t__ kstrtouint (int /*<<< orphan*/ ,int,unsigned int*) ; 
 struct mtd_partition* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int,...) ; 
 unsigned int roundup (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (struct bcm_tag*) ; 
 struct bcm_tag* vmalloc (int) ; 

__attribute__((used)) static int bcm963xx_parse_imagetag_partitions(struct mtd_info *master,
					const struct mtd_partition **pparts,
					struct mtd_part_parser_data *data)
{
	/* CFE, NVRAM and global Linux are always present */
	int nrparts = 0, curpart = 0;
	struct bcm_tag *buf = NULL;
	struct mtd_partition *parts;
	int ret;
	unsigned int rootfsaddr, kerneladdr, spareaddr, offset;
	unsigned int rootfslen, kernellen, sparelen, totallen;
	int i;
	bool rootfs_first = false;

	buf = vmalloc(sizeof(struct bcm_tag));
	if (!buf)
		return -ENOMEM;

	/* Get the tag */
	ret = bcm963xx_read_imagetag(master, "rootfs", 0, buf);
	if (!ret) {
		STR_NULL_TERMINATE(buf->flash_image_start);
		if (kstrtouint(buf->flash_image_start, 10, &rootfsaddr) ||
				rootfsaddr < BCM963XX_EXTENDED_SIZE) {
			pr_err("invalid rootfs address: %*ph\n",
				(int)sizeof(buf->flash_image_start),
				buf->flash_image_start);
			goto out;
		}

		STR_NULL_TERMINATE(buf->kernel_address);
		if (kstrtouint(buf->kernel_address, 10, &kerneladdr) ||
				kerneladdr < BCM963XX_EXTENDED_SIZE) {
			pr_err("invalid kernel address: %*ph\n",
				(int)sizeof(buf->kernel_address),
				buf->kernel_address);
			goto out;
		}

		STR_NULL_TERMINATE(buf->kernel_length);
		if (kstrtouint(buf->kernel_length, 10, &kernellen)) {
			pr_err("invalid kernel length: %*ph\n",
				(int)sizeof(buf->kernel_length),
				buf->kernel_length);
			goto out;
		}

		STR_NULL_TERMINATE(buf->total_length);
		if (kstrtouint(buf->total_length, 10, &totallen)) {
			pr_err("invalid total length: %*ph\n",
				(int)sizeof(buf->total_length),
				buf->total_length);
			goto out;
		}

		/*
		 * Addresses are flash absolute, so convert to partition
		 * relative addresses. Assume either kernel or rootfs will
		 * directly follow the image tag.
		 */
		if (rootfsaddr < kerneladdr)
			offset = rootfsaddr - sizeof(struct bcm_tag);
		else
			offset = kerneladdr - sizeof(struct bcm_tag);

		kerneladdr = kerneladdr - offset;
		rootfsaddr = rootfsaddr - offset;
		spareaddr = roundup(totallen, master->erasesize);

		if (rootfsaddr < kerneladdr) {
			/* default Broadcom layout */
			rootfslen = kerneladdr - rootfsaddr;
			rootfs_first = true;
		} else {
			/* OpenWrt layout */
			rootfsaddr = kerneladdr + kernellen;
			rootfslen = spareaddr - rootfsaddr;
		}
	} else {
		goto out;
	}
	sparelen = master->size - spareaddr;

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