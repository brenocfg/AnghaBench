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
struct sharpsl_nand_partinfo {int /*<<< orphan*/  start; int /*<<< orphan*/  end; int /*<<< orphan*/  magic; } ;
struct sharpsl_ftl {int dummy; } ;
struct mtd_info {int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 scalar_t__ BOOT_MAGIC ; 
 int EINVAL ; 
 scalar_t__ FSRO_MAGIC ; 
 scalar_t__ FSRW_MAGIC ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int sharpsl_nand_read_laddr (struct mtd_info*,int /*<<< orphan*/ ,size_t,struct sharpsl_nand_partinfo*,struct sharpsl_ftl*) ; 

__attribute__((used)) static int sharpsl_nand_read_partinfo(struct mtd_info *master,
				      loff_t from,
				      size_t len,
				      struct sharpsl_nand_partinfo *buf,
				      struct sharpsl_ftl *ftl)
{
	int ret;

	ret = sharpsl_nand_read_laddr(master, from, len, buf, ftl);
	if (ret)
		return ret;

	/* check for magics */
	if (be32_to_cpu(buf[0].magic) != BOOT_MAGIC ||
	    be32_to_cpu(buf[1].magic) != FSRO_MAGIC ||
	    be32_to_cpu(buf[2].magic) != FSRW_MAGIC) {
		pr_err("sharpslpart: magic values mismatch\n");
		return -EINVAL;
	}

	/* fixup for hardcoded value 64 MiB (for older models) */
	buf[2].end = cpu_to_le32(master->size);

	/* extra sanity check */
	if (le32_to_cpu(buf[0].end) <= le32_to_cpu(buf[0].start) ||
	    le32_to_cpu(buf[1].start) < le32_to_cpu(buf[0].end) ||
	    le32_to_cpu(buf[1].end) <= le32_to_cpu(buf[1].start) ||
	    le32_to_cpu(buf[2].start) < le32_to_cpu(buf[1].end) ||
	    le32_to_cpu(buf[2].end) <= le32_to_cpu(buf[2].start)) {
		pr_err("sharpslpart: partition sizes mismatch\n");
		return -EINVAL;
	}

	return 0;
}