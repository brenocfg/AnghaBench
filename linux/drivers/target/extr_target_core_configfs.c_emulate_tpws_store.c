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
struct se_dev_attrib {int emulate_tpws; int /*<<< orphan*/  da_dev; int /*<<< orphan*/  max_unmap_block_desc_count; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int strtobool (char const*,int*) ; 
 struct se_dev_attrib* to_attrib (struct config_item*) ; 

__attribute__((used)) static ssize_t emulate_tpws_store(struct config_item *item,
		const char *page, size_t count)
{
	struct se_dev_attrib *da = to_attrib(item);
	bool flag;
	int ret;

	ret = strtobool(page, &flag);
	if (ret < 0)
		return ret;

	/*
	 * We expect this value to be non-zero when generic Block Layer
	 * Discard supported is detected iblock_create_virtdevice().
	 */
	if (flag && !da->max_unmap_block_desc_count) {
		pr_err("Generic Block Discard not supported\n");
		return -ENOSYS;
	}

	da->emulate_tpws = flag;
	pr_debug("dev[%p]: SE Device Thin Provisioning WRITE_SAME: %d\n",
				da->da_dev, flag);
	return count;
}