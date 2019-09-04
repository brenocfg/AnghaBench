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
struct mtd_partition {int dummy; } ;
struct mtd_part_parser_data {int dummy; } ;
struct TYPE_2__ {scalar_t__ notifier_call; } ;
struct mtd_info {int /*<<< orphan*/  dev; TYPE_1__ reboot_notifier; scalar_t__ _reboot; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_MTD_PARTITIONED_MASTER ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int add_mtd_device (struct mtd_info*) ; 
 int add_mtd_partitions (struct mtd_info*,struct mtd_partition const*,int) ; 
 int /*<<< orphan*/  del_mtd_device (struct mtd_info*) ; 
 scalar_t__ device_is_registered (int /*<<< orphan*/ *) ; 
 scalar_t__ mtd_reboot_notifier ; 
 int /*<<< orphan*/  mtd_set_dev_defaults (struct mtd_info*) ; 
 int parse_mtd_partitions (struct mtd_info*,char const* const*,struct mtd_part_parser_data*) ; 
 int /*<<< orphan*/  register_reboot_notifier (TYPE_1__*) ; 

int mtd_device_parse_register(struct mtd_info *mtd, const char * const *types,
			      struct mtd_part_parser_data *parser_data,
			      const struct mtd_partition *parts,
			      int nr_parts)
{
	int ret;

	mtd_set_dev_defaults(mtd);

	if (IS_ENABLED(CONFIG_MTD_PARTITIONED_MASTER)) {
		ret = add_mtd_device(mtd);
		if (ret)
			return ret;
	}

	/* Prefer parsed partitions over driver-provided fallback */
	ret = parse_mtd_partitions(mtd, types, parser_data);
	if (ret > 0)
		ret = 0;
	else if (nr_parts)
		ret = add_mtd_partitions(mtd, parts, nr_parts);
	else if (!device_is_registered(&mtd->dev))
		ret = add_mtd_device(mtd);
	else
		ret = 0;

	if (ret)
		goto out;

	/*
	 * FIXME: some drivers unfortunately call this function more than once.
	 * So we have to check if we've already assigned the reboot notifier.
	 *
	 * Generally, we can make multiple calls work for most cases, but it
	 * does cause problems with parse_mtd_partitions() above (e.g.,
	 * cmdlineparts will register partitions more than once).
	 */
	WARN_ONCE(mtd->_reboot && mtd->reboot_notifier.notifier_call,
		  "MTD already registered\n");
	if (mtd->_reboot && !mtd->reboot_notifier.notifier_call) {
		mtd->reboot_notifier.notifier_call = mtd_reboot_notifier;
		register_reboot_notifier(&mtd->reboot_notifier);
	}

out:
	if (ret && device_is_registered(&mtd->dev))
		del_mtd_device(mtd);

	return ret;
}