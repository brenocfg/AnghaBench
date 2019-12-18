#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ttm_bo_global {int /*<<< orphan*/  kobj; int /*<<< orphan*/  bo_count; int /*<<< orphan*/  device_list; int /*<<< orphan*/ * swap_lru; int /*<<< orphan*/ * dummy_read_page; TYPE_1__* mem_glob; int /*<<< orphan*/  lru_lock; } ;
struct TYPE_3__ {struct ttm_bo_global* bo_glob; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_DMA32 ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 unsigned int TTM_MAX_BO_PRIORITY ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/ * alloc_page (int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int kobject_init_and_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct ttm_bo_global ttm_bo_glob ; 
 int /*<<< orphan*/  ttm_bo_glob_kobj_type ; 
 int ttm_bo_glob_use_count ; 
 int /*<<< orphan*/  ttm_get_kobj () ; 
 int /*<<< orphan*/  ttm_global_mutex ; 
 TYPE_1__ ttm_mem_glob ; 
 int ttm_mem_global_init (TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ttm_bo_global_init(void)
{
	struct ttm_bo_global *glob = &ttm_bo_glob;
	int ret = 0;
	unsigned i;

	mutex_lock(&ttm_global_mutex);
	if (++ttm_bo_glob_use_count > 1)
		goto out;

	ret = ttm_mem_global_init(&ttm_mem_glob);
	if (ret)
		goto out;

	spin_lock_init(&glob->lru_lock);
	glob->mem_glob = &ttm_mem_glob;
	glob->mem_glob->bo_glob = glob;
	glob->dummy_read_page = alloc_page(__GFP_ZERO | GFP_DMA32);

	if (unlikely(glob->dummy_read_page == NULL)) {
		ret = -ENOMEM;
		goto out;
	}

	for (i = 0; i < TTM_MAX_BO_PRIORITY; ++i)
		INIT_LIST_HEAD(&glob->swap_lru[i]);
	INIT_LIST_HEAD(&glob->device_list);
	atomic_set(&glob->bo_count, 0);

	ret = kobject_init_and_add(
		&glob->kobj, &ttm_bo_glob_kobj_type, ttm_get_kobj(), "buffer_objects");
	if (unlikely(ret != 0))
		kobject_put(&glob->kobj);
out:
	mutex_unlock(&ttm_global_mutex);
	return ret;
}