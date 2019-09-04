#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mtd_partition {int dummy; } ;
struct mtd_part_parser_data {int dummy; } ;
struct mtd_info {char* name; scalar_t__ size; } ;
struct cmdline_mtd_partition {int num_parts; TYPE_1__* parts; int /*<<< orphan*/  mtd_id; struct cmdline_mtd_partition* next; } ;
struct TYPE_4__ {unsigned long long offset; scalar_t__ size; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long long OFFSET_CONTINUOUS ; 
 scalar_t__ SIZE_REMAINING ; 
 int /*<<< orphan*/  cmdline ; 
 int /*<<< orphan*/  cmdline_parsed ; 
 struct mtd_partition* kmemdup (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (TYPE_1__*,TYPE_1__*,int) ; 
 int mtdpart_setup_real (int /*<<< orphan*/ ) ; 
 struct cmdline_mtd_partition* partitions ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int parse_cmdline_partitions(struct mtd_info *master,
				    const struct mtd_partition **pparts,
				    struct mtd_part_parser_data *data)
{
	unsigned long long offset;
	int i, err;
	struct cmdline_mtd_partition *part;
	const char *mtd_id = master->name;

	/* parse command line */
	if (!cmdline_parsed) {
		err = mtdpart_setup_real(cmdline);
		if (err)
			return err;
	}

	/*
	 * Search for the partition definition matching master->name.
	 * If master->name is not set, stop at first partition definition.
	 */
	for (part = partitions; part; part = part->next) {
		if ((!mtd_id) || (!strcmp(part->mtd_id, mtd_id)))
			break;
	}

	if (!part)
		return 0;

	for (i = 0, offset = 0; i < part->num_parts; i++) {
		if (part->parts[i].offset == OFFSET_CONTINUOUS)
			part->parts[i].offset = offset;
		else
			offset = part->parts[i].offset;

		if (part->parts[i].size == SIZE_REMAINING)
			part->parts[i].size = master->size - offset;

		if (offset + part->parts[i].size > master->size) {
			pr_warn("%s: partitioning exceeds flash size, truncating\n",
				part->mtd_id);
			part->parts[i].size = master->size - offset;
		}
		offset += part->parts[i].size;

		if (part->parts[i].size == 0) {
			pr_warn("%s: skipping zero sized partition\n",
				part->mtd_id);
			part->num_parts--;
			memmove(&part->parts[i], &part->parts[i + 1],
				sizeof(*part->parts) * (part->num_parts - i));
			i--;
		}
	}

	*pparts = kmemdup(part->parts, sizeof(*part->parts) * part->num_parts,
			  GFP_KERNEL);
	if (!*pparts)
		return -ENOMEM;

	return part->num_parts;
}