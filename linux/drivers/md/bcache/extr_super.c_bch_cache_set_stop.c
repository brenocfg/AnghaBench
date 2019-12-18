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
struct cache_set {int /*<<< orphan*/  caching; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_SET_STOPPING ; 
 int /*<<< orphan*/  closure_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void bch_cache_set_stop(struct cache_set *c)
{
	if (!test_and_set_bit(CACHE_SET_STOPPING, &c->flags))
		/* closure_fn set to __cache_set_unregister() */
		closure_queue(&c->caching);
}