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
struct bvec_iter {int dummy; } ;
struct bio {struct bvec_iter bi_iter; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_copy_data_iter (struct bio*,struct bvec_iter*,struct bio*,struct bvec_iter*) ; 

void bio_copy_data(struct bio *dst, struct bio *src)
{
	struct bvec_iter src_iter = src->bi_iter;
	struct bvec_iter dst_iter = dst->bi_iter;

	bio_copy_data_iter(dst, &dst_iter, src, &src_iter);
}