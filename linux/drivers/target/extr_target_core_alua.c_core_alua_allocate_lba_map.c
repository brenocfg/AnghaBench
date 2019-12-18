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
typedef  void* u64 ;
struct t10_alua_lba_map {int /*<<< orphan*/  lba_map_list; void* lba_map_last_lba; void* lba_map_first_lba; int /*<<< orphan*/  lba_map_mem_list; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct t10_alua_lba_map* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct t10_alua_lba_map* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  t10_alua_lba_map_cache ; 

struct t10_alua_lba_map *
core_alua_allocate_lba_map(struct list_head *list,
			   u64 first_lba, u64 last_lba)
{
	struct t10_alua_lba_map *lba_map;

	lba_map = kmem_cache_zalloc(t10_alua_lba_map_cache, GFP_KERNEL);
	if (!lba_map) {
		pr_err("Unable to allocate struct t10_alua_lba_map\n");
		return ERR_PTR(-ENOMEM);
	}
	INIT_LIST_HEAD(&lba_map->lba_map_mem_list);
	lba_map->lba_map_first_lba = first_lba;
	lba_map->lba_map_last_lba = last_lba;

	list_add_tail(&lba_map->lba_map_list, list);
	return lba_map;
}