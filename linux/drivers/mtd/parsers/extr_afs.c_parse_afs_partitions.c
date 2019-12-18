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
typedef  scalar_t__ u_int ;
struct mtd_partition {struct mtd_partition* name; } ;
struct mtd_part_parser_data {int dummy; } ;
struct mtd_info {scalar_t__ size; scalar_t__ erasesize; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ afs_is_v1 (struct mtd_info*,scalar_t__) ; 
 scalar_t__ afs_is_v2 (struct mtd_info*,scalar_t__) ; 
 int afs_parse_v1_partition (struct mtd_info*,scalar_t__,struct mtd_partition*) ; 
 int afs_parse_v2_partition (struct mtd_info*,scalar_t__,struct mtd_partition*) ; 
 int /*<<< orphan*/  kfree (struct mtd_partition*) ; 
 struct mtd_partition* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_afs_partitions(struct mtd_info *mtd,
				const struct mtd_partition **pparts,
				struct mtd_part_parser_data *data)
{
	struct mtd_partition *parts;
	u_int off, sz;
	int ret = 0;
	int i;

	/* Count the partitions by looping over all erase blocks */
	for (i = off = sz = 0; off < mtd->size; off += mtd->erasesize) {
		if (afs_is_v1(mtd, off)) {
			sz += sizeof(struct mtd_partition);
			i += 1;
		}
		if (afs_is_v2(mtd, off)) {
			sz += sizeof(struct mtd_partition);
			i += 1;
		}
	}

	if (!i)
		return 0;

	parts = kzalloc(sz, GFP_KERNEL);
	if (!parts)
		return -ENOMEM;

	/*
	 * Identify the partitions
	 */
	for (i = off = 0; off < mtd->size; off += mtd->erasesize) {
		if (afs_is_v1(mtd, off)) {
			ret = afs_parse_v1_partition(mtd, off, &parts[i]);
			if (ret)
				goto out_free_parts;
			i++;
		}
		if (afs_is_v2(mtd, off)) {
			ret = afs_parse_v2_partition(mtd, off, &parts[i]);
			if (ret)
				goto out_free_parts;
			i++;
		}
	}

	*pparts = parts;
	return i;

out_free_parts:
	while (i >= 0) {
		kfree(parts[i].name);
		i--;
	}
	kfree(parts);
	*pparts = NULL;
	return ret;
}