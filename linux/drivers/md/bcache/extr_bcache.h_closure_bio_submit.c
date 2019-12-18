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
struct cache_set {int /*<<< orphan*/  flags; } ;
struct bio {int /*<<< orphan*/  bi_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  CACHE_SET_IO_DISABLE ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 int /*<<< orphan*/  closure_get (struct closure*) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void closure_bio_submit(struct cache_set *c,
				      struct bio *bio,
				      struct closure *cl)
{
	closure_get(cl);
	if (unlikely(test_bit(CACHE_SET_IO_DISABLE, &c->flags))) {
		bio->bi_status = BLK_STS_IOERR;
		bio_endio(bio);
		return;
	}
	generic_make_request(bio);
}