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
struct scatterlist {unsigned long length; scalar_t__ offset; } ;
struct rnd_state {int dummy; } ;
struct TYPE_3__ {unsigned long nents; struct scatterlist* sgl; } ;
struct pfn_table {unsigned long start; unsigned long end; TYPE_1__ st; } ;
typedef  unsigned long (* npages_fn_t ) (unsigned long,unsigned long,struct rnd_state*) ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int GFP_KERNEL ; 
 unsigned long PAGE_SIZE ; 
 unsigned long PFN_BIAS ; 
 int __GFP_NORETRY ; 
 int __GFP_NOWARN ; 
 int overflows_type (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  page_contiguous (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long page_to_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfn_to_page (unsigned long) ; 
 scalar_t__ sg_alloc_table (TYPE_1__*,unsigned long,int) ; 
 int /*<<< orphan*/  sg_free_table (TYPE_1__*) ; 
 int /*<<< orphan*/  sg_mark_end (struct scatterlist*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alloc_table(struct pfn_table *pt,
		       unsigned long count, unsigned long max,
		       npages_fn_t npages_fn,
		       struct rnd_state *rnd,
		       int alloc_error)
{
	struct scatterlist *sg;
	unsigned long n, pfn;

	if (sg_alloc_table(&pt->st, max,
			   GFP_KERNEL | __GFP_NORETRY | __GFP_NOWARN))
		return alloc_error;

	/* count should be less than 20 to prevent overflowing sg->length */
	GEM_BUG_ON(overflows_type(count * PAGE_SIZE, sg->length));

	/* Construct a table where each scatterlist contains different number
	 * of entries. The idea is to check that we can iterate the individual
	 * pages from inside the coalesced lists.
	 */
	pt->start = PFN_BIAS;
	pfn = pt->start;
	sg = pt->st.sgl;
	for (n = 0; n < count; n++) {
		unsigned long npages = npages_fn(n, count, rnd);

		/* Nobody expects the Sparse Memmap! */
		if (!page_contiguous(pfn_to_page(pfn),
				     pfn_to_page(pfn + npages),
				     npages)) {
			sg_free_table(&pt->st);
			return -ENOSPC;
		}

		if (n)
			sg = sg_next(sg);
		sg_set_page(sg, pfn_to_page(pfn), npages * PAGE_SIZE, 0);

		GEM_BUG_ON(page_to_pfn(sg_page(sg)) != pfn);
		GEM_BUG_ON(sg->length != npages * PAGE_SIZE);
		GEM_BUG_ON(sg->offset != 0);

		pfn += npages;
	}
	sg_mark_end(sg);
	pt->st.nents = n;
	pt->end = pfn;

	return 0;
}