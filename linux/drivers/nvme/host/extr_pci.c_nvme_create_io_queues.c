#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int queue_count; } ;
struct nvme_dev {unsigned int max_qid; unsigned int* io_queues; unsigned int online_queues; int /*<<< orphan*/ * queues; TYPE_1__ ctrl; int /*<<< orphan*/  q_depth; } ;

/* Variables and functions */
 int ENOMEM ; 
 size_t HCTX_TYPE_DEFAULT ; 
 size_t HCTX_TYPE_POLL ; 
 size_t HCTX_TYPE_READ ; 
 unsigned int min (unsigned int,int) ; 
 scalar_t__ nvme_alloc_queue (struct nvme_dev*,unsigned int,int /*<<< orphan*/ ) ; 
 int nvme_create_queue (int /*<<< orphan*/ *,unsigned int,int) ; 

__attribute__((used)) static int nvme_create_io_queues(struct nvme_dev *dev)
{
	unsigned i, max, rw_queues;
	int ret = 0;

	for (i = dev->ctrl.queue_count; i <= dev->max_qid; i++) {
		if (nvme_alloc_queue(dev, i, dev->q_depth)) {
			ret = -ENOMEM;
			break;
		}
	}

	max = min(dev->max_qid, dev->ctrl.queue_count - 1);
	if (max != 1 && dev->io_queues[HCTX_TYPE_POLL]) {
		rw_queues = dev->io_queues[HCTX_TYPE_DEFAULT] +
				dev->io_queues[HCTX_TYPE_READ];
	} else {
		rw_queues = max;
	}

	for (i = dev->online_queues; i <= max; i++) {
		bool polled = i > rw_queues;

		ret = nvme_create_queue(&dev->queues[i], i, polled);
		if (ret)
			break;
	}

	/*
	 * Ignore failing Create SQ/CQ commands, we can continue with less
	 * than the desired amount of queues, and even a controller without
	 * I/O queues can still be used to issue admin commands.  This might
	 * be useful to upgrade a buggy firmware for example.
	 */
	return ret >= 0 ? 0 : ret;
}