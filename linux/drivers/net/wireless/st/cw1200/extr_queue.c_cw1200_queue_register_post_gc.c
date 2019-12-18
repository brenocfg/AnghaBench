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
struct list_head {int dummy; } ;
struct cw1200_queue_item {int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct cw1200_queue_item* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  memcpy (struct cw1200_queue_item*,struct cw1200_queue_item*,int) ; 

__attribute__((used)) static void cw1200_queue_register_post_gc(struct list_head *gc_list,
					  struct cw1200_queue_item *item)
{
	struct cw1200_queue_item *gc_item;
	gc_item = kmalloc(sizeof(struct cw1200_queue_item),
			GFP_ATOMIC);
	BUG_ON(!gc_item);
	memcpy(gc_item, item, sizeof(struct cw1200_queue_item));
	list_add_tail(&gc_item->head, gc_list);
}