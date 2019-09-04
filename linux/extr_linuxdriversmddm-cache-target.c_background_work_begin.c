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
struct cache {int /*<<< orphan*/  background_work_lock; } ;

/* Variables and functions */
 int down_read_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_off () ; 
 int /*<<< orphan*/  lockdep_on () ; 

__attribute__((used)) static bool background_work_begin(struct cache *cache)
{
	bool r;

	lockdep_off();
	r = down_read_trylock(&cache->background_work_lock);
	lockdep_on();

	return r;
}