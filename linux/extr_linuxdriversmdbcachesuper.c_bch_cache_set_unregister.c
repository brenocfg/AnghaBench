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
struct cache_set {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_SET_UNREGISTERING ; 
 int /*<<< orphan*/  bch_cache_set_stop (struct cache_set*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void bch_cache_set_unregister(struct cache_set *c)
{
	set_bit(CACHE_SET_UNREGISTERING, &c->flags);
	bch_cache_set_stop(c);
}