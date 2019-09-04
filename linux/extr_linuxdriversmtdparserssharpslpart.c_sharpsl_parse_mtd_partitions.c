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
struct sharpsl_nand_partinfo {int /*<<< orphan*/  start; int /*<<< orphan*/  end; } ;
struct sharpsl_ftl {int dummy; } ;
struct mtd_partition {char* name; void* size; void* offset; } ;
struct mtd_part_parser_data {int dummy; } ;
struct mtd_info {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SHARPSL_NAND_PARTS ; 
 int /*<<< orphan*/  SHARPSL_PARTINFO1_LADDR ; 
 int /*<<< orphan*/  SHARPSL_PARTINFO2_LADDR ; 
 struct mtd_partition* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int sharpsl_nand_check_ooblayout (struct mtd_info*) ; 
 int /*<<< orphan*/  sharpsl_nand_cleanup_ftl (struct sharpsl_ftl*) ; 
 int sharpsl_nand_init_ftl (struct mtd_info*,struct sharpsl_ftl*) ; 
 int sharpsl_nand_read_partinfo (struct mtd_info*,int /*<<< orphan*/ ,int,struct sharpsl_nand_partinfo*,struct sharpsl_ftl*) ; 

__attribute__((used)) static int sharpsl_parse_mtd_partitions(struct mtd_info *master,
					const struct mtd_partition **pparts,
					struct mtd_part_parser_data *data)
{
	struct sharpsl_ftl ftl;
	struct sharpsl_nand_partinfo buf[SHARPSL_NAND_PARTS];
	struct mtd_partition *sharpsl_nand_parts;
	int err;

	/* check that OOB bytes 8 to 15 used by the FTL are actually free */
	err = sharpsl_nand_check_ooblayout(master);
	if (err)
		return err;

	/* init logical mgmt (FTL) */
	err = sharpsl_nand_init_ftl(master, &ftl);
	if (err)
		return err;

	/* read and validate first partition table */
	pr_info("sharpslpart: try reading first partition table\n");
	err = sharpsl_nand_read_partinfo(master,
					 SHARPSL_PARTINFO1_LADDR,
					 sizeof(buf), buf, &ftl);
	if (err) {
		/* fallback: read second partition table */
		pr_warn("sharpslpart: first partition table is invalid, retry using the second\n");
		err = sharpsl_nand_read_partinfo(master,
						 SHARPSL_PARTINFO2_LADDR,
						 sizeof(buf), buf, &ftl);
	}

	/* cleanup logical mgmt (FTL) */
	sharpsl_nand_cleanup_ftl(&ftl);

	if (err) {
		pr_err("sharpslpart: both partition tables are invalid\n");
		return err;
	}

	sharpsl_nand_parts = kcalloc(SHARPSL_NAND_PARTS,
				     sizeof(*sharpsl_nand_parts),
				     GFP_KERNEL);
	if (!sharpsl_nand_parts)
		return -ENOMEM;

	/* original names */
	sharpsl_nand_parts[0].name = "smf";
	sharpsl_nand_parts[0].offset = le32_to_cpu(buf[0].start);
	sharpsl_nand_parts[0].size = le32_to_cpu(buf[0].end) -
				     le32_to_cpu(buf[0].start);

	sharpsl_nand_parts[1].name = "root";
	sharpsl_nand_parts[1].offset = le32_to_cpu(buf[1].start);
	sharpsl_nand_parts[1].size = le32_to_cpu(buf[1].end) -
				     le32_to_cpu(buf[1].start);

	sharpsl_nand_parts[2].name = "home";
	sharpsl_nand_parts[2].offset = le32_to_cpu(buf[2].start);
	sharpsl_nand_parts[2].size = le32_to_cpu(buf[2].end) -
				     le32_to_cpu(buf[2].start);

	*pparts = sharpsl_nand_parts;
	return SHARPSL_NAND_PARTS;
}