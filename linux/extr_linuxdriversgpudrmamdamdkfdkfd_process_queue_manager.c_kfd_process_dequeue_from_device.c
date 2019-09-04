#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kfd_process_device {int already_dequeued; int /*<<< orphan*/  qpd; struct kfd_dev* dev; } ;
struct kfd_dev {TYPE_2__* dqm; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* process_termination ) (TYPE_2__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *) ; 

void kfd_process_dequeue_from_device(struct kfd_process_device *pdd)
{
	struct kfd_dev *dev = pdd->dev;

	if (pdd->already_dequeued)
		return;

	dev->dqm->ops.process_termination(dev->dqm, &pdd->qpd);
	pdd->already_dequeued = true;
}