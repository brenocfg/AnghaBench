#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ttm_page_pool {unsigned int npages; int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct page {int /*<<< orphan*/  lru; } ;
typedef  enum ttm_caching_state { ____Placeholder_ttm_caching_state } ttm_caching_state ;
struct TYPE_3__ {unsigned int max_size; } ;
struct TYPE_4__ {TYPE_1__ options; } ;

/* Variables and functions */
 unsigned int HPAGE_PMD_NR ; 
 unsigned int HPAGE_PMD_ORDER ; 
 unsigned int NUM_PAGES_TO_ALLOC ; 
 int TTM_PAGE_FLAG_DMA32 ; 
 int /*<<< orphan*/  __free_pages (struct page*,unsigned int) ; 
 TYPE_2__* _manager ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int page_count (struct page*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct ttm_page_pool* ttm_get_pool (int,int,int) ; 
 int /*<<< orphan*/  ttm_page_pool_free (struct ttm_page_pool*,unsigned int,int) ; 

__attribute__((used)) static void ttm_put_pages(struct page **pages, unsigned npages, int flags,
			  enum ttm_caching_state cstate)
{
	struct ttm_page_pool *pool = ttm_get_pool(flags, false, cstate);
#ifdef CONFIG_TRANSPARENT_HUGEPAGE
	struct ttm_page_pool *huge = ttm_get_pool(flags, true, cstate);
#endif
	unsigned long irq_flags;
	unsigned i;

	if (pool == NULL) {
		/* No pool for this memory type so free the pages */
		i = 0;
		while (i < npages) {
#ifdef CONFIG_TRANSPARENT_HUGEPAGE
			struct page *p = pages[i];
#endif
			unsigned order = 0, j;

			if (!pages[i]) {
				++i;
				continue;
			}

#ifdef CONFIG_TRANSPARENT_HUGEPAGE
			if (!(flags & TTM_PAGE_FLAG_DMA32) &&
			    (npages - i) >= HPAGE_PMD_NR) {
				for (j = 1; j < HPAGE_PMD_NR; ++j)
					if (++p != pages[i + j])
					    break;

				if (j == HPAGE_PMD_NR)
					order = HPAGE_PMD_ORDER;
			}
#endif

			if (page_count(pages[i]) != 1)
				pr_err("Erroneous page count. Leaking pages.\n");
			__free_pages(pages[i], order);

			j = 1 << order;
			while (j) {
				pages[i++] = NULL;
				--j;
			}
		}
		return;
	}

	i = 0;
#ifdef CONFIG_TRANSPARENT_HUGEPAGE
	if (huge) {
		unsigned max_size, n2free;

		spin_lock_irqsave(&huge->lock, irq_flags);
		while ((npages - i) >= HPAGE_PMD_NR) {
			struct page *p = pages[i];
			unsigned j;

			if (!p)
				break;

			for (j = 1; j < HPAGE_PMD_NR; ++j)
				if (++p != pages[i + j])
				    break;

			if (j != HPAGE_PMD_NR)
				break;

			list_add_tail(&pages[i]->lru, &huge->list);

			for (j = 0; j < HPAGE_PMD_NR; ++j)
				pages[i++] = NULL;
			huge->npages++;
		}

		/* Check that we don't go over the pool limit */
		max_size = _manager->options.max_size;
		max_size /= HPAGE_PMD_NR;
		if (huge->npages > max_size)
			n2free = huge->npages - max_size;
		else
			n2free = 0;
		spin_unlock_irqrestore(&huge->lock, irq_flags);
		if (n2free)
			ttm_page_pool_free(huge, n2free, false);
	}
#endif

	spin_lock_irqsave(&pool->lock, irq_flags);
	while (i < npages) {
		if (pages[i]) {
			if (page_count(pages[i]) != 1)
				pr_err("Erroneous page count. Leaking pages.\n");
			list_add_tail(&pages[i]->lru, &pool->list);
			pages[i] = NULL;
			pool->npages++;
		}
		++i;
	}
	/* Check that we don't go over the pool limit */
	npages = 0;
	if (pool->npages > _manager->options.max_size) {
		npages = pool->npages - _manager->options.max_size;
		/* free at least NUM_PAGES_TO_ALLOC number of pages
		 * to reduce calls to set_memory_wb */
		if (npages < NUM_PAGES_TO_ALLOC)
			npages = NUM_PAGES_TO_ALLOC;
	}
	spin_unlock_irqrestore(&pool->lock, irq_flags);
	if (npages)
		ttm_page_pool_free(pool, npages, false);
}