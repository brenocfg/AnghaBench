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
struct closure {int dummy; } ;
struct cache_set {int dummy; } ;
struct bio {struct closure* bi_private; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  bch_bbio_count_io_errors (struct cache_set*,struct bio*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  closure_put (struct closure*) ; 

void bch_bbio_endio(struct cache_set *c, struct bio *bio,
		    blk_status_t error, const char *m)
{
	struct closure *cl = bio->bi_private;

	bch_bbio_count_io_errors(c, bio, error, m);
	bio_put(bio);
	closure_put(cl);
}