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
struct t10_alua_lba_map {int dummy; } ;
struct se_device {int dummy; } ;
struct list_head {int dummy; } ;
struct config_item {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int ALUA_ACCESS_STATE_ACTIVE_NON_OPTIMIZED ; 
 int ALUA_ACCESS_STATE_ACTIVE_OPTIMIZED ; 
 int ALUA_ACCESS_STATE_STANDBY ; 
 int ALUA_ACCESS_STATE_UNAVAILABLE ; 
 int EINVAL ; 
 size_t ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 scalar_t__ IS_ERR (struct t10_alua_lba_map*) ; 
 int PTR_ERR (struct t10_alua_lba_map*) ; 
 struct t10_alua_lba_map* core_alua_allocate_lba_map (struct list_head*,unsigned long,unsigned long) ; 
 int core_alua_allocate_lba_map_mem (struct t10_alua_lba_map*,int,int) ; 
 int /*<<< orphan*/  core_alua_free_lba_map (struct list_head*) ; 
 int /*<<< orphan*/  core_alua_set_lba_map (struct se_device*,struct list_head*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 
 int sscanf (char*,char*,...) ; 
 char* strchr (char*,char) ; 
 char* strsep (char**,char*) ; 
 struct se_device* to_device (struct config_item*) ; 

__attribute__((used)) static ssize_t target_dev_lba_map_store(struct config_item *item,
		const char *page, size_t count)
{
	struct se_device *dev = to_device(item);
	struct t10_alua_lba_map *lba_map = NULL;
	struct list_head lba_list;
	char *map_entries, *orig, *ptr;
	char state;
	int pg_num = -1, pg;
	int ret = 0, num = 0, pg_id, alua_state;
	unsigned long start_lba = -1, end_lba = -1;
	unsigned long segment_size = -1, segment_mult = -1;

	orig = map_entries = kstrdup(page, GFP_KERNEL);
	if (!map_entries)
		return -ENOMEM;

	INIT_LIST_HEAD(&lba_list);
	while ((ptr = strsep(&map_entries, "\n")) != NULL) {
		if (!*ptr)
			continue;

		if (num == 0) {
			if (sscanf(ptr, "%lu %lu\n",
				   &segment_size, &segment_mult) != 2) {
				pr_err("Invalid line %d\n", num);
				ret = -EINVAL;
				break;
			}
			num++;
			continue;
		}
		if (sscanf(ptr, "%lu %lu", &start_lba, &end_lba) != 2) {
			pr_err("Invalid line %d\n", num);
			ret = -EINVAL;
			break;
		}
		ptr = strchr(ptr, ' ');
		if (!ptr) {
			pr_err("Invalid line %d, missing end lba\n", num);
			ret = -EINVAL;
			break;
		}
		ptr++;
		ptr = strchr(ptr, ' ');
		if (!ptr) {
			pr_err("Invalid line %d, missing state definitions\n",
			       num);
			ret = -EINVAL;
			break;
		}
		ptr++;
		lba_map = core_alua_allocate_lba_map(&lba_list,
						     start_lba, end_lba);
		if (IS_ERR(lba_map)) {
			ret = PTR_ERR(lba_map);
			break;
		}
		pg = 0;
		while (sscanf(ptr, "%d:%c", &pg_id, &state) == 2) {
			switch (state) {
			case 'O':
				alua_state = ALUA_ACCESS_STATE_ACTIVE_OPTIMIZED;
				break;
			case 'A':
				alua_state = ALUA_ACCESS_STATE_ACTIVE_NON_OPTIMIZED;
				break;
			case 'S':
				alua_state = ALUA_ACCESS_STATE_STANDBY;
				break;
			case 'U':
				alua_state = ALUA_ACCESS_STATE_UNAVAILABLE;
				break;
			default:
				pr_err("Invalid ALUA state '%c'\n", state);
				ret = -EINVAL;
				goto out;
			}

			ret = core_alua_allocate_lba_map_mem(lba_map,
							     pg_id, alua_state);
			if (ret) {
				pr_err("Invalid target descriptor %d:%c "
				       "at line %d\n",
				       pg_id, state, num);
				break;
			}
			pg++;
			ptr = strchr(ptr, ' ');
			if (ptr)
				ptr++;
			else
				break;
		}
		if (pg_num == -1)
		    pg_num = pg;
		else if (pg != pg_num) {
			pr_err("Only %d from %d port groups definitions "
			       "at line %d\n", pg, pg_num, num);
			ret = -EINVAL;
			break;
		}
		num++;
	}
out:
	if (ret) {
		core_alua_free_lba_map(&lba_list);
		count = ret;
	} else
		core_alua_set_lba_map(dev, &lba_list,
				      segment_size, segment_mult);
	kfree(orig);
	return count;
}