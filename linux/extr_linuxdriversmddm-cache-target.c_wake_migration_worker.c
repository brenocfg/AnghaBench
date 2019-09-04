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
struct cache {int /*<<< orphan*/  migration_worker; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 scalar_t__ passthrough_mode (struct cache*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wake_migration_worker(struct cache *cache)
{
	if (passthrough_mode(cache))
		return;

	queue_work(cache->wq, &cache->migration_worker);
}