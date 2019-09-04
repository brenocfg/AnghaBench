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
typedef  int /*<<< orphan*/  uint32_t ;
struct vmw_marker_queue {int /*<<< orphan*/  lock; int /*<<< orphan*/  head; } ;
struct vmw_marker {int /*<<< orphan*/  head; int /*<<< orphan*/  submitted; int /*<<< orphan*/  seqno; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct vmw_marker* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_raw_ns () ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int vmw_marker_push(struct vmw_marker_queue *queue,
		   uint32_t seqno)
{
	struct vmw_marker *marker = kmalloc(sizeof(*marker), GFP_KERNEL);

	if (unlikely(!marker))
		return -ENOMEM;

	marker->seqno = seqno;
	marker->submitted = ktime_get_raw_ns();
	spin_lock(&queue->lock);
	list_add_tail(&marker->head, &queue->head);
	spin_unlock(&queue->lock);

	return 0;
}