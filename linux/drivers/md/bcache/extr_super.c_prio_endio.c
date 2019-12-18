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
struct cache {int /*<<< orphan*/  prio; int /*<<< orphan*/  set; } ;
struct bio {int /*<<< orphan*/  bi_status; struct cache* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  bch_bbio_free (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_set_err_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  closure_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void prio_endio(struct bio *bio)
{
	struct cache *ca = bio->bi_private;

	cache_set_err_on(bio->bi_status, ca->set, "accessing priorities");
	bch_bbio_free(bio, ca->set);
	closure_put(&ca->prio);
}