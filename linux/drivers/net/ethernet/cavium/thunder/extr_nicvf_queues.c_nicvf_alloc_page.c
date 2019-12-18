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
struct rbdr {size_t pgidx; int pgalloc; int pgcnt; struct pgcache* pgcache; scalar_t__ is_xdp; } ;
struct pgcache {int ref_count; struct page* page; scalar_t__ dma_addr; } ;
struct page {int /*<<< orphan*/  _refcount; } ;
struct nicvf {struct page* rb_page; TYPE_2__* pnicvf; } ;
typedef  int gfp_t ;
struct TYPE_4__ {TYPE_1__* drv_stats; } ;
struct TYPE_3__ {int /*<<< orphan*/  page_alloc; } ;

/* Variables and functions */
 int XDP_PAGE_REFCNT_REFILL ; 
 int __GFP_COMP ; 
 int __GFP_NOWARN ; 
 struct page* alloc_pages (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_ref_add (struct page*,int) ; 
 int page_ref_count (struct page*) ; 
 int /*<<< orphan*/  prefetch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct pgcache *nicvf_alloc_page(struct nicvf *nic,
					       struct rbdr *rbdr, gfp_t gfp)
{
	int ref_count;
	struct page *page = NULL;
	struct pgcache *pgcache, *next;

	/* Check if page is already allocated */
	pgcache = &rbdr->pgcache[rbdr->pgidx];
	page = pgcache->page;
	/* Check if page can be recycled */
	if (page) {
		ref_count = page_ref_count(page);
		/* This page can be recycled if internal ref_count and page's
		 * ref_count are equal, indicating that the page has been used
		 * once for packet transmission. For non-XDP mode, internal
		 * ref_count is always '1'.
		 */
		if (rbdr->is_xdp) {
			if (ref_count == pgcache->ref_count)
				pgcache->ref_count--;
			else
				page = NULL;
		} else if (ref_count != 1) {
			page = NULL;
		}
	}

	if (!page) {
		page = alloc_pages(gfp | __GFP_COMP | __GFP_NOWARN, 0);
		if (!page)
			return NULL;

		this_cpu_inc(nic->pnicvf->drv_stats->page_alloc);

		/* Check for space */
		if (rbdr->pgalloc >= rbdr->pgcnt) {
			/* Page can still be used */
			nic->rb_page = page;
			return NULL;
		}

		/* Save the page in page cache */
		pgcache->page = page;
		pgcache->dma_addr = 0;
		pgcache->ref_count = 0;
		rbdr->pgalloc++;
	}

	/* Take additional page references for recycling */
	if (rbdr->is_xdp) {
		/* Since there is single RBDR (i.e single core doing
		 * page recycling) per 8 Rx queues, in XDP mode adjusting
		 * page references atomically is the biggest bottleneck, so
		 * take bunch of references at a time.
		 *
		 * So here, below reference counts defer by '1'.
		 */
		if (!pgcache->ref_count) {
			pgcache->ref_count = XDP_PAGE_REFCNT_REFILL;
			page_ref_add(page, XDP_PAGE_REFCNT_REFILL);
		}
	} else {
		/* In non-XDP case, single 64K page is divided across multiple
		 * receive buffers, so cost of recycling is less anyway.
		 * So we can do with just one extra reference.
		 */
		page_ref_add(page, 1);
	}

	rbdr->pgidx++;
	rbdr->pgidx &= (rbdr->pgcnt - 1);

	/* Prefetch refcount of next page in page cache */
	next = &rbdr->pgcache[rbdr->pgidx];
	page = next->page;
	if (page)
		prefetch(&page->_refcount);

	return pgcache;
}