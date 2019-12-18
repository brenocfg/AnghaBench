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
struct rq_map_data {unsigned long offset; } ;
struct st_buffer {struct page** mapped_pages; struct rq_map_data map_data; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FOLL_WRITE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 int READ ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 int get_user_pages_fast (unsigned long,int const,int /*<<< orphan*/ ,struct page**) ; 
 int /*<<< orphan*/  kfree (struct page**) ; 
 struct page** kmalloc_array (unsigned int const,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

__attribute__((used)) static int sgl_map_user_pages(struct st_buffer *STbp,
			      const unsigned int max_pages, unsigned long uaddr,
			      size_t count, int rw)
{
	unsigned long end = (uaddr + count + PAGE_SIZE - 1) >> PAGE_SHIFT;
	unsigned long start = uaddr >> PAGE_SHIFT;
	const int nr_pages = end - start;
	int res, i, j;
	struct page **pages;
	struct rq_map_data *mdata = &STbp->map_data;

	/* User attempted Overflow! */
	if ((uaddr + count) < uaddr)
		return -EINVAL;

	/* Too big */
        if (nr_pages > max_pages)
		return -ENOMEM;

	/* Hmm? */
	if (count == 0)
		return 0;

	pages = kmalloc_array(max_pages, sizeof(*pages), GFP_KERNEL);
	if (pages == NULL)
		return -ENOMEM;

        /* Try to fault in all of the necessary pages */
        /* rw==READ means read from drive, write into memory area */
	res = get_user_pages_fast(uaddr, nr_pages, rw == READ ? FOLL_WRITE : 0,
				  pages);

	/* Errors and no page mapped should return here */
	if (res < nr_pages)
		goto out_unmap;

        for (i=0; i < nr_pages; i++) {
                /* FIXME: flush superflous for rw==READ,
                 * probably wrong function for rw==WRITE
                 */
		flush_dcache_page(pages[i]);
        }

	mdata->offset = uaddr & ~PAGE_MASK;
	STbp->mapped_pages = pages;

	return nr_pages;
 out_unmap:
	if (res > 0) {
		for (j=0; j < res; j++)
			put_page(pages[j]);
		res = 0;
	}
	kfree(pages);
	return res;
}