#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  entry; } ;
struct vc4_seqno_cb {void (* func ) (struct vc4_seqno_cb*) ;TYPE_1__ work; scalar_t__ seqno; } ;
struct vc4_dev {scalar_t__ finished_seqno; int /*<<< orphan*/  job_lock; int /*<<< orphan*/  seqno_cb_list; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 
 int /*<<< orphan*/  vc4_seqno_cb_work ; 

int vc4_queue_seqno_cb(struct drm_device *dev,
		       struct vc4_seqno_cb *cb, uint64_t seqno,
		       void (*func)(struct vc4_seqno_cb *cb))
{
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	int ret = 0;
	unsigned long irqflags;

	cb->func = func;
	INIT_WORK(&cb->work, vc4_seqno_cb_work);

	spin_lock_irqsave(&vc4->job_lock, irqflags);
	if (seqno > vc4->finished_seqno) {
		cb->seqno = seqno;
		list_add_tail(&cb->work.entry, &vc4->seqno_cb_list);
	} else {
		schedule_work(&cb->work);
	}
	spin_unlock_irqrestore(&vc4->job_lock, irqflags);

	return ret;
}