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
struct TYPE_2__ {scalar_t__ bi_sector; } ;
struct dpages {TYPE_1__ context_bi; scalar_t__ context_ptr; } ;
struct bio_vec {unsigned long bv_len; unsigned int bv_offset; struct page* bv_page; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 struct bio_vec bvec_iter_bvec (struct bio_vec*,TYPE_1__) ; 

__attribute__((used)) static void bio_get_page(struct dpages *dp, struct page **p,
			 unsigned long *len, unsigned *offset)
{
	struct bio_vec bvec = bvec_iter_bvec((struct bio_vec *)dp->context_ptr,
					     dp->context_bi);

	*p = bvec.bv_page;
	*len = bvec.bv_len;
	*offset = bvec.bv_offset;

	/* avoid figuring it out again in bio_next_page() */
	dp->context_bi.bi_sector = (sector_t)bvec.bv_len;
}