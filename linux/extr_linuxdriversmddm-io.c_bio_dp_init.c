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
struct dpages {int /*<<< orphan*/  context_bi; int /*<<< orphan*/  context_ptr; int /*<<< orphan*/  next_page; int /*<<< orphan*/  get_page; } ;
struct bio {int /*<<< orphan*/  bi_iter; int /*<<< orphan*/  bi_io_vec; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_get_page ; 
 int /*<<< orphan*/  bio_next_page ; 

__attribute__((used)) static void bio_dp_init(struct dpages *dp, struct bio *bio)
{
	dp->get_page = bio_get_page;
	dp->next_page = bio_next_page;

	/*
	 * We just use bvec iterator to retrieve pages, so it is ok to
	 * access the bvec table directly here
	 */
	dp->context_ptr = bio->bi_io_vec;
	dp->context_bi = bio->bi_iter;
}