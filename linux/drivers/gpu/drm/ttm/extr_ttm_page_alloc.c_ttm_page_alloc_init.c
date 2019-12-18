#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ttm_mem_global {int /*<<< orphan*/  kobj; } ;
struct TYPE_6__ {unsigned int max_size; int /*<<< orphan*/  alloc_size; int /*<<< orphan*/  small; } ;
struct TYPE_7__ {int /*<<< orphan*/  kobj; TYPE_1__ options; int /*<<< orphan*/  uc_pool_huge; int /*<<< orphan*/  wc_pool_huge; int /*<<< orphan*/  uc_pool_dma32; int /*<<< orphan*/  wc_pool_dma32; int /*<<< orphan*/  uc_pool; int /*<<< orphan*/  wc_pool; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_DMA32 ; 
 int GFP_HIGHUSER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GFP_TRANSHUGE_LIGHT ; 
 int GFP_USER ; 
 unsigned int HPAGE_PMD_ORDER ; 
 int /*<<< orphan*/  NUM_PAGES_TO_ALLOC ; 
 int /*<<< orphan*/  SMALL_ALLOCATION ; 
 int /*<<< orphan*/  WARN_ON (TYPE_2__*) ; 
 int __GFP_COMP ; 
 int __GFP_KSWAPD_RECLAIM ; 
 int __GFP_MOVABLE ; 
 int __GFP_NORETRY ; 
 TYPE_2__* _manager ; 
 int kobject_init_and_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 TYPE_2__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  ttm_page_pool_init_locked (int /*<<< orphan*/ *,int,char*,unsigned int) ; 
 int /*<<< orphan*/  ttm_pool_kobj_type ; 
 int ttm_pool_mm_shrink_init (TYPE_2__*) ; 
 scalar_t__ unlikely (int) ; 

int ttm_page_alloc_init(struct ttm_mem_global *glob, unsigned max_pages)
{
	int ret;
#ifdef CONFIG_TRANSPARENT_HUGEPAGE
	unsigned order = HPAGE_PMD_ORDER;
#else
	unsigned order = 0;
#endif

	WARN_ON(_manager);

	pr_info("Initializing pool allocator\n");

	_manager = kzalloc(sizeof(*_manager), GFP_KERNEL);
	if (!_manager)
		return -ENOMEM;

	ttm_page_pool_init_locked(&_manager->wc_pool, GFP_HIGHUSER, "wc", 0);

	ttm_page_pool_init_locked(&_manager->uc_pool, GFP_HIGHUSER, "uc", 0);

	ttm_page_pool_init_locked(&_manager->wc_pool_dma32,
				  GFP_USER | GFP_DMA32, "wc dma", 0);

	ttm_page_pool_init_locked(&_manager->uc_pool_dma32,
				  GFP_USER | GFP_DMA32, "uc dma", 0);

	ttm_page_pool_init_locked(&_manager->wc_pool_huge,
				  (GFP_TRANSHUGE_LIGHT | __GFP_NORETRY |
				   __GFP_KSWAPD_RECLAIM) &
				  ~(__GFP_MOVABLE | __GFP_COMP),
				  "wc huge", order);

	ttm_page_pool_init_locked(&_manager->uc_pool_huge,
				  (GFP_TRANSHUGE_LIGHT | __GFP_NORETRY |
				   __GFP_KSWAPD_RECLAIM) &
				  ~(__GFP_MOVABLE | __GFP_COMP)
				  , "uc huge", order);

	_manager->options.max_size = max_pages;
	_manager->options.small = SMALL_ALLOCATION;
	_manager->options.alloc_size = NUM_PAGES_TO_ALLOC;

	ret = kobject_init_and_add(&_manager->kobj, &ttm_pool_kobj_type,
				   &glob->kobj, "pool");
	if (unlikely(ret != 0))
		goto error;

	ret = ttm_pool_mm_shrink_init(_manager);
	if (unlikely(ret != 0))
		goto error;
	return 0;

error:
	kobject_put(&_manager->kobj);
	_manager = NULL;
	return ret;
}