#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct iov_iter {int dummy; } ;
struct bio_vec {int bv_len; scalar_t__ bv_offset; struct page* bv_page; } ;
struct TYPE_2__ {int bi_size; } ;
struct bio {unsigned short bi_max_vecs; unsigned short bi_vcnt; TYPE_1__ bi_iter; struct bio_vec* bi_io_vec; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  LONG_MAX ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  iov_iter_advance (struct iov_iter*,int) ; 
 int iov_iter_get_pages (struct iov_iter*,struct page**,int /*<<< orphan*/ ,unsigned short,size_t*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int __bio_iov_iter_get_pages(struct bio *bio, struct iov_iter *iter)
{
	unsigned short nr_pages = bio->bi_max_vecs - bio->bi_vcnt, idx;
	struct bio_vec *bv = bio->bi_io_vec + bio->bi_vcnt;
	struct page **pages = (struct page **)bv;
	size_t offset;
	ssize_t size;

	size = iov_iter_get_pages(iter, pages, LONG_MAX, nr_pages, &offset);
	if (unlikely(size <= 0))
		return size ? size : -EFAULT;
	idx = nr_pages = (size + offset + PAGE_SIZE - 1) / PAGE_SIZE;

	/*
	 * Deep magic below:  We need to walk the pinned pages backwards
	 * because we are abusing the space allocated for the bio_vecs
	 * for the page array.  Because the bio_vecs are larger than the
	 * page pointers by definition this will always work.  But it also
	 * means we can't use bio_add_page, so any changes to it's semantics
	 * need to be reflected here as well.
	 */
	bio->bi_iter.bi_size += size;
	bio->bi_vcnt += nr_pages;

	while (idx--) {
		bv[idx].bv_page = pages[idx];
		bv[idx].bv_len = PAGE_SIZE;
		bv[idx].bv_offset = 0;
	}

	bv[0].bv_offset += offset;
	bv[0].bv_len -= offset;
	bv[nr_pages - 1].bv_len -= nr_pages * PAGE_SIZE - offset - size;

	iov_iter_advance(iter, size);
	return 0;
}