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
struct cmd_obj {int /*<<< orphan*/  list; } ;
struct __queue {int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; } ;
typedef  int /*<<< orphan*/  _irqL ;

/* Variables and functions */
 int _SUCCESS ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int _rtw_enqueue_cmd(struct __queue *queue, struct cmd_obj *obj)
{
	_irqL irqL;

	if (obj == NULL)
		goto exit;

	/* spin_lock_bh(&queue->lock); */
	spin_lock_irqsave(&queue->lock, irqL);

	list_add_tail(&obj->list, &queue->queue);

	/* spin_unlock_bh(&queue->lock); */
	spin_unlock_irqrestore(&queue->lock, irqL);

exit:
	return _SUCCESS;
}