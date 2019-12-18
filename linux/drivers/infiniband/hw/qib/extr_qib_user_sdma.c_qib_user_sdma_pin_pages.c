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
struct qib_user_sdma_queue {int dummy; } ;
struct qib_user_sdma_pkt {int dummy; } ;
struct qib_devdata {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FOLL_LONGTERM ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SIZE ; 
 int get_user_pages_fast (unsigned long,int,int /*<<< orphan*/ ,struct page**) ; 
 int /*<<< orphan*/  put_user_page (struct page*) ; 
 int qib_user_sdma_page_to_frags (struct qib_devdata const*,struct qib_user_sdma_queue*,struct qib_user_sdma_pkt*,struct page*,int,unsigned long,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qib_user_sdma_pin_pages(const struct qib_devdata *dd,
				   struct qib_user_sdma_queue *pq,
				   struct qib_user_sdma_pkt *pkt,
				   unsigned long addr, int tlen, int npages)
{
	struct page *pages[8];
	int i, j;
	int ret = 0;

	while (npages) {
		if (npages > 8)
			j = 8;
		else
			j = npages;

		ret = get_user_pages_fast(addr, j, FOLL_LONGTERM, pages);
		if (ret != j) {
			i = 0;
			j = ret;
			ret = -ENOMEM;
			goto free_pages;
		}

		for (i = 0; i < j; i++) {
			/* map the pages... */
			unsigned long fofs = addr & ~PAGE_MASK;
			int flen = ((fofs + tlen) > PAGE_SIZE) ?
				(PAGE_SIZE - fofs) : tlen;

			ret = qib_user_sdma_page_to_frags(dd, pq, pkt,
				pages[i], 1, fofs, flen, NULL);
			if (ret < 0) {
				/* current page has beed taken
				 * care of inside above call.
				 */
				i++;
				goto free_pages;
			}

			addr += flen;
			tlen -= flen;
		}

		npages -= j;
	}

	goto done;

	/* if error, return all pages not managed by pkt */
free_pages:
	while (i < j)
		put_user_page(pages[i++]);

done:
	return ret;
}