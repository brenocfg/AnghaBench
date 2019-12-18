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
struct omap_mbox_queue {int /*<<< orphan*/  work; int /*<<< orphan*/  fifo; int /*<<< orphan*/  lock; } ;
struct omap_mbox {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,void (*) (struct work_struct*)) ; 
 scalar_t__ kfifo_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct omap_mbox_queue*) ; 
 struct omap_mbox_queue* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox_kfifo_size ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct omap_mbox_queue *mbox_queue_alloc(struct omap_mbox *mbox,
					void (*work)(struct work_struct *))
{
	struct omap_mbox_queue *mq;

	if (!work)
		return NULL;

	mq = kzalloc(sizeof(*mq), GFP_KERNEL);
	if (!mq)
		return NULL;

	spin_lock_init(&mq->lock);

	if (kfifo_alloc(&mq->fifo, mbox_kfifo_size, GFP_KERNEL))
		goto error;

	INIT_WORK(&mq->work, work);
	return mq;

error:
	kfree(mq);
	return NULL;
}