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
struct bt_work {int dummy; } ;
struct background_tracker {int /*<<< orphan*/  work_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOWAIT ; 
 struct bt_work* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ max_work_reached (struct background_tracker*) ; 

__attribute__((used)) static struct bt_work *alloc_work(struct background_tracker *b)
{
	if (max_work_reached(b))
		return NULL;

	return kmem_cache_alloc(b->work_cache, GFP_NOWAIT);
}