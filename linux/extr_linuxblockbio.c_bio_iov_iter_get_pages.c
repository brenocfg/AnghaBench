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
struct iov_iter {int dummy; } ;
struct bio {unsigned short bi_vcnt; } ;

/* Variables and functions */
 int __bio_iov_iter_get_pages (struct bio*,struct iov_iter*) ; 
 int /*<<< orphan*/  bio_full (struct bio*) ; 
 scalar_t__ iov_iter_count (struct iov_iter*) ; 
 scalar_t__ unlikely (int) ; 

int bio_iov_iter_get_pages(struct bio *bio, struct iov_iter *iter)
{
	unsigned short orig_vcnt = bio->bi_vcnt;

	do {
		int ret = __bio_iov_iter_get_pages(bio, iter);

		if (unlikely(ret))
			return bio->bi_vcnt > orig_vcnt ? 0 : ret;

	} while (iov_iter_count(iter) && !bio_full(bio));

	return 0;
}