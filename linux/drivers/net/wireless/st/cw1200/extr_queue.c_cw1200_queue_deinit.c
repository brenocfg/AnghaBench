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
struct cw1200_queue {scalar_t__ capacity; int /*<<< orphan*/ * link_map_cache; int /*<<< orphan*/ * pool; int /*<<< orphan*/  free_pool; int /*<<< orphan*/  gc; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cw1200_queue_clear (struct cw1200_queue*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void cw1200_queue_deinit(struct cw1200_queue *queue)
{
	cw1200_queue_clear(queue);
	del_timer_sync(&queue->gc);
	INIT_LIST_HEAD(&queue->free_pool);
	kfree(queue->pool);
	kfree(queue->link_map_cache);
	queue->pool = NULL;
	queue->link_map_cache = NULL;
	queue->capacity = 0;
}